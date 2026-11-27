/*
 * Copyright (C) 2009 Qi Hardware Inc.,
 * Author:  Xiangfu Liu <xiangfu@sharism.cc>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 3 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA
 */
#include "usb/usb.h"
#include "usb/udc.h"
#include "target/usb_boot.h"
#include "target/xburst_types.h"
#include "ingenic_request.h"

#if defined(NANONOTE)
#include "target/jz4740.h"
#elif defined(LEPUS)
#include "target/jz4760.h"
#else
	#error "Please Define [NANONOTE] or [LEPUS]"
#endif

#define dprintf(x...)		/* serial_puts(x) */
#define TXFIFOEP0 USB_FIFO_EP0

extern void serial_put_hex(int );

u32 Bulk_in_buf[BULK_IN_BUF_SIZE];
u32 Bulk_out_buf[BULK_OUT_BUF_SIZE];
u32 Bulk_in_size, Bulk_in_finish, Bulk_out_size;
u16 handshake_PKT[4] = {0, 0, 0, 0};
u8 udc_state;

static u32 rx_buf[32];
static u32 tx_buf[32];
static u32 tx_size, rx_size, finished, fifo;
static u8 ep0state, USB_Version;

static u32 fifoaddr[] = 
{
	TXFIFOEP0, TXFIFOEP0+4 ,TXFIFOEP0+8
};

static u32 fifosize[] = {
	MAX_EP0_SIZE, MAX_EP1_SIZE
};

/* keep gcc from turning these loops into calls to themselves */
__attribute__((optimize("no-tree-loop-distribute-patterns")))
void *memset(void *s, int c, size_t count)
{
	char *xs = s;

	while (count--)
		*xs++ = c;
	return s;
}

__attribute__((optimize("no-tree-loop-distribute-patterns")))
void *memcpy(void *dest, const void *src, size_t count)
{
	char *tmp = dest;
	const char *s = src;

	while (count--)
		*tmp++ = *s++;

	return dest;
}

static void udcReadFifo(u8 *ptr, int size)
{
	u32 *d = (u32 *)ptr;
	int s;
	s = (size + 3) >> 2;
	while (s--)
		*d++ = REG32(fifo);
}

static void udcWriteFifo(u8 *ptr, int size)
{
	u32 *d = (u32 *)ptr;
	u8 *c;
	int s, q;

	if (size > 0) {
		s = size >> 2;
		while (s--)
			REG32(fifo) = *d++;
		q = size & 3;
		if (q) {
			c = (u8 *)d;
			while (q--)
				REG8(fifo) = *c++;
		}
	} 
}

void HW_SendPKT(int ep, const u8 *buf, int size)
{
	fifo = fifoaddr[ep];

	if (ep!=0) {
		Bulk_in_size = size;
		Bulk_in_finish = 0;
		jz_writeb(USB_REG_INDEX, ep);
		if (Bulk_in_size - Bulk_in_finish <= fifosize[ep])  {
			udcWriteFifo((u8 *)((u32)buf+Bulk_in_finish),
				     Bulk_in_size - Bulk_in_finish);
			usb_setb(USB_REG_INCSR, USB_INCSR_INPKTRDY);
			Bulk_in_finish = Bulk_in_size;
		} else {
			udcWriteFifo((u8 *)((u32)buf+Bulk_in_finish),
				     fifosize[ep]);
			usb_setb(USB_REG_INCSR, USB_INCSR_INPKTRDY);
			Bulk_in_finish += fifosize[ep];
		}
	} else {
		tx_size = size;
		finished = 0;
		memcpy((void *)tx_buf, buf, size);
		ep0state = USB_EP0_TX;		
	}
}

void HW_GetPKT(int ep, const u8 *buf, int size)
{
	memcpy((void *)buf, (u8 *)rx_buf, size);
	fifo = fifoaddr[ep];
	if (rx_size > size)
		rx_size -= size;
	else {
		size = rx_size;
		rx_size = 0;
	}
	memcpy((u8 *)rx_buf, (u8 *)((u32)rx_buf+size), rx_size);
}

static USB_DeviceDescriptor devDesc = 
{
	sizeof(USB_DeviceDescriptor),
	DEVICE_DESCRIPTOR,	//1
	0x0200,     //Version 2.0
	0xff,    //Vendor spec class
	0xff,
	0xff,
	64,	/* Ep0 FIFO size */
	0x601a,  //vendor ID
	0x4740,  //Product ID
	0xffff,
	0x00,
	0x00,
	0x00,
	0x01
};

#define	CONFIG_DESCRIPTOR_LEN	(sizeof(USB_ConfigDescriptor) + \
				 sizeof(USB_InterfaceDescriptor) + \
				 sizeof(USB_EndPointDescriptor) * 2)

static struct {
	USB_ConfigDescriptor    configuration_descriptor;
	USB_InterfaceDescriptor interface_descritor;
	USB_EndPointDescriptor  endpoint_descriptor[2];
} __attribute__ ((packed)) confDesc = {
	{
		sizeof(USB_ConfigDescriptor),
		CONFIGURATION_DESCRIPTOR,
		CONFIG_DESCRIPTOR_LEN,
		0x01,
		0x01,
		0x00,
		0xc0,	// Self Powered, no remote wakeup
		0x64	// Maximum power consumption 2000 mA
	},
	{
		sizeof(USB_InterfaceDescriptor),
		INTERFACE_DESCRIPTOR,
		0x00,
		0x00,
		0x02,	/* ep number */
		0xff,
		0xff,
		0xff,
		0x00
	},
	{
		{
			sizeof(USB_EndPointDescriptor),
			ENDPOINT_DESCRIPTOR,
			(1 << 7) | 1,// endpoint 2 is IN endpoint
			2, /* bulk */
			512,
			16
		},
		{
			sizeof(USB_EndPointDescriptor),
			ENDPOINT_DESCRIPTOR,
			(0 << 7) | 1,// endpoint 5 is OUT endpoint
			2, /* bulk */
			512, /* OUT EP FIFO size */
			16
		}
	}
};

void sendDevDescString(int size)
{
	u16 str_ret[13] = {
		0x031a,//0x1a=26 byte
		0x0041,
		0x0030,
		0x0030,
		0x0041,
		0x0030,
		0x0030,
		0x0041,
		0x0030,
		0x0030,
		0x0041,
		0x0030,
		0x0030
	};
	if(size >= 26)
		size = 26;
	str_ret[0] = (0x0300 | size);
	HW_SendPKT(0, (u8 *)str_ret,size);
	
}

void sendDevDesc(int size)
{
       switch (size) {
	case 18:
		HW_SendPKT(0, (u8 *)&devDesc, sizeof(devDesc));
		break;
	default:
		HW_SendPKT(0, (u8 *)&devDesc, 8);
		break;
	}
}

void sendConfDesc(int size)
{
	switch (size) {
	case 9:
		HW_SendPKT(0, (u8 *)&confDesc, 9);
		break;
	case 8:
		HW_SendPKT(0, (u8 *)&confDesc, 8);
		break;
	default:
		HW_SendPKT(0, (u8 *)&confDesc, sizeof(confDesc));
		break;
	}
}

void EP0_init(u32 out, u32 out_size, u32 in, u32 in_size)
{
	confDesc.endpoint_descriptor[0].bEndpointAddress = (1<<7) | in;
	confDesc.endpoint_descriptor[0].wMaxPacketSize = in_size;
	confDesc.endpoint_descriptor[1].bEndpointAddress = (0<<7) | out;
	confDesc.endpoint_descriptor[1].wMaxPacketSize = out_size;
}

static void udc_reset(void)
{
	u8 byte;
	ep0state = USB_EP0_IDLE;
	Bulk_in_size = 0;
	Bulk_in_finish = 0;
	Bulk_out_size = 0;
	udc_state = IDLE;
	tx_size = 0;
	rx_size = 0;
	finished = 0;
	/* Enable the USB PHY */
//	REG_CPM_SCR |= CPM_SCR_USBPHY_ENABLE;
	/* Disable interrupts */
	byte=jz_readb(USB_REG_POWER);
	jz_writew(USB_REG_INTRINE, 0);
	jz_writew(USB_REG_INTROUTE, 0);
	jz_writeb(USB_REG_INTRUSBE, 0);
	jz_writeb(USB_REG_FADDR, 0);
	jz_writeb(USB_REG_POWER, 0x60);   //High speed
	jz_writeb(USB_REG_INDEX, 0);
	jz_writeb(USB_REG_CSR0, 0xc0);
	jz_writeb(USB_REG_INDEX, 1);
	jz_writew(USB_REG_INMAXP, 512);
	jz_writew(USB_REG_INCSR, 0x2048);
	jz_writeb(USB_REG_INDEX, 1);
	jz_writew(USB_REG_OUTMAXP, 512);
	jz_writew(USB_REG_OUTCSR, 0x0090);
	jz_writew(USB_REG_INTRINE, 0x3);   //enable intr
	jz_writew(USB_REG_INTROUTE, 0x2);
	jz_writeb(USB_REG_INTRUSBE, 0x4);

	byte = jz_readb(USB_REG_POWER);
	if ((byte&0x10) == 0) {
		jz_writeb(USB_REG_INDEX, 1);
		jz_writew(USB_REG_INMAXP, 64);
		jz_writew(USB_REG_INCSR, 0x2048);
		jz_writeb(USB_REG_INDEX, 1);
		jz_writew(USB_REG_OUTMAXP, 64);
		jz_writew(USB_REG_OUTCSR, 0x0090);
		USB_Version = USB_FS;
		fifosize[1] = 64;
		EP0_init(1, 64, 1, 64);
	} else {
		jz_writeb(USB_REG_INDEX, 1);
		jz_writew(USB_REG_INMAXP, 512);
		jz_writew(USB_REG_INCSR, 0x2048);
		jz_writeb(USB_REG_INDEX, 1);
		jz_writew(USB_REG_OUTMAXP, 512);
		jz_writew(USB_REG_OUTCSR, 0x0090);
		USB_Version = USB_HS;
		fifosize[1] = 512;
		EP0_init(1, 512, 1, 512);
	}

}


void usbHandleStandDevReq(u8 *buf)
{
	USB_DeviceRequest *dreq = (USB_DeviceRequest *)buf;
	switch (dreq->bRequest) {
	case GET_DESCRIPTOR:
		if (dreq->bmRequestType == 0x80)	/* Dev2Host */
			switch(dreq->wValue >> 8) {
			case DEVICE_DESCRIPTOR:
				dprintf("get device\n");
				sendDevDesc(dreq->wLength);
				break;
			case CONFIGURATION_DESCRIPTOR:
				dprintf("get config\n");
				sendConfDesc(dreq->wLength);
				break;
			case STRING_DESCRIPTOR:
				if (dreq->wLength == 0x02)
					HW_SendPKT(0, "\x04\x03", 2);
				else
					sendDevDescString(dreq->wLength);
				break;
			}
		dprintf("\nSet ep0state=TX!");
		ep0state = USB_EP0_TX;
		
		break;
	case SET_ADDRESS:
		dprintf("\nSET_ADDRESS!");
		jz_writeb(USB_REG_FADDR,dreq->wValue);
		break;
	case GET_STATUS:
		switch (dreq->bmRequestType) {
		case 80:	/* device */
			HW_SendPKT(0, "\x01\x00", 2);
			break;
		case 81:	/* interface */
		case 82:	/* ep */
			HW_SendPKT(0, "\x00\x00", 2);
			break;
		}
		ep0state=USB_EP0_TX;
		break;
	case CLEAR_FEATURE:
	case SET_CONFIGURATION:
	case SET_INTERFACE:
	case SET_FEATURE:
		break;
	}
}

void usbHandleVendorReq(u8 *buf)
{
	int ret_state;
	USB_DeviceRequest *dreq = (USB_DeviceRequest *)buf;
	switch (dreq->bRequest) {
	case VR_GET_CPU_INFO:
		ret_state = GET_CPU_INFO_Handle();
		break;
	case VR_SET_DATA_ADDRESS:
		ret_state = SET_DATA_ADDERSS_Handle(buf);
		break;
	case VR_SET_DATA_LENGTH:
		ret_state = SET_DATA_LENGTH_Handle(buf);
		break;
	case VR_FLUSH_CACHES:
		ret_state = FLUSH_CACHES_Handle();
		break;
	case VR_PROGRAM_START1:
		ret_state = PROGRAM_START1_Handle(buf);
		break;
	case VR_PROGRAM_START2:
		ret_state = PROGRAM_START2_Handle(buf);
		break;
	case VR_NOR_OPS:
		ret_state = NOR_OPS_Handle(buf);
		Bulk_out_size = 0;
		break;
	case VR_NAND_OPS:
		NAND_OPS_Handle(buf);
		Bulk_out_size = 0;
		break;
	case VR_CONFIGRATION:
		ret_state = CONFIGRATION_Handle(buf);
		handshake_PKT[3] = (u16)ret_state;
		HW_SendPKT(1, (u8 *)handshake_PKT, sizeof(handshake_PKT));
		Bulk_out_size = 0;
		break;
	case VR_SDRAM_OPS:
		SDRAM_OPS_Handle(buf);
		Bulk_out_size = 0;
		break;
	case VR_RESET:
		ret_state = RESET_Handle(buf);
		break;
	}
}

void Handshake_PKT()
{
	if (udc_state!=IDLE)
	{
		HW_SendPKT(1, (u8 *)handshake_PKT, sizeof(handshake_PKT));
		udc_state = IDLE;
		dprintf("\n Send handshake PKT!");
	}
}

void usbHandleDevReq(u8 *buf)
{
	switch ((buf[0] & (3 << 5)) >> 5) {
	case 0: /* Standard request */
		usbHandleStandDevReq(buf);
		break;
	case 1: /* Class request */
		break;
	case 2: /* Vendor request */
		usbHandleVendorReq(buf);
		break;
	}
}

void EP0_Handler ()
{
	u8 byCSR0;

/* Read CSR0 */
	jz_writeb(USB_REG_INDEX, 0);
	byCSR0 = jz_readb(USB_REG_CSR0);

/* Check for SentStall
 * if sendtall is set ,clear the sendstall bit */
	if (byCSR0 & USB_CSR0_SENTSTALL) {
		jz_writeb(USB_REG_CSR0, (byCSR0 & ~USB_CSR0_SENDSTALL));
		ep0state = USB_EP0_IDLE;
		dprintf("\nSentstall!");
		return;
	}

/* Check for SetupEnd */
	if (byCSR0 & USB_CSR0_SETUPEND) {
		jz_writeb(USB_REG_CSR0, (byCSR0 | USB_CSR0_SVDSETUPEND));
		ep0state = USB_EP0_IDLE;
		dprintf("\nSetupend!");
		return;
	}
/* Call relevant routines for endpoint 0 state */
	if (ep0state == USB_EP0_IDLE) {
		if (byCSR0 & USB_CSR0_OUTPKTRDY) {  //There are datas in fifo
			USB_DeviceRequest *dreq;
			fifo = fifoaddr[0];
			udcReadFifo((u8 *)rx_buf, sizeof(USB_DeviceRequest));
			usb_setb(USB_REG_CSR0, 0x48);//clear OUTRD bit
			dreq = (USB_DeviceRequest *)rx_buf;
			usbHandleDevReq((u8 *)rx_buf);
		} else
			dprintf("0:R DATA\n");

		rx_size = 0;
	}
	
	if (ep0state == USB_EP0_TX) {
		fifo=fifoaddr[0];
		if (tx_size - finished <= 64) {
			udcWriteFifo((u8 *)((u32)tx_buf+finished),
				     tx_size - finished);
			finished = tx_size;
			usb_setb(USB_REG_CSR0, USB_CSR0_INPKTRDY);
			usb_setb(USB_REG_CSR0, USB_CSR0_DATAEND); //Set dataend!
			ep0state = USB_EP0_IDLE;
		} else {
			udcWriteFifo((u8 *)((u32)tx_buf+finished), 64);
			usb_setb(USB_REG_CSR0, USB_CSR0_INPKTRDY);
			finished += 64;
		}
	}
	return;
}

void EPIN_Handler(u8 EP)
{
	jz_writeb(USB_REG_INDEX, EP);
	fifo = fifoaddr[EP];

	if (Bulk_in_size-Bulk_in_finish==0) {
		Handshake_PKT();
		return;
	}

	if (Bulk_in_size - Bulk_in_finish <= fifosize[EP]) {
		udcWriteFifo((u8 *)((u32)Bulk_in_buf+Bulk_in_finish),
			     Bulk_in_size - Bulk_in_finish);
		usb_setw(USB_REG_INCSR, USB_INCSR_INPKTRDY);
		Bulk_in_finish = Bulk_in_size;
	} else {
		udcWriteFifo((u8 *)((u32)Bulk_in_buf+Bulk_in_finish),
			    fifosize[EP]);
		usb_setw(USB_REG_INCSR, USB_INCSR_INPKTRDY);
		Bulk_in_finish += fifosize[EP];
	}
}

void EPOUT_Handler(u8 EP)
{
	u32 size;
	jz_writeb(USB_REG_INDEX, EP);
	size = jz_readw(USB_REG_OUTCOUNT);
	fifo = fifoaddr[EP];
	udcReadFifo((u8 *)((u32)Bulk_out_buf+Bulk_out_size), size);
	usb_clearb(USB_REG_OUTCSR,USB_OUTCSR_OUTPKTRDY);
	Bulk_out_size += size;
	dprintf("\nEPOUT_handle return!");
}

void udc4740Proc ()
{
	volatile u8	IntrUSB;
	volatile u16	IntrIn;
	volatile u16	IntrOut;
	/* Read interrupt registers */
	IntrUSB = jz_readb(USB_REG_INTRUSB);
	IntrIn  = jz_readw(USB_REG_INTRIN);
	IntrOut = jz_readw(USB_REG_INTROUT);
		
	if (IntrUSB == 0 && IntrIn == 0 && IntrOut == 0)
		return;
		
	if (IntrIn & 2) {
		dprintf("\nUDC EP1 IN operation!");
		EPIN_Handler(1);	     
	}

	if (IntrOut & 2) {
		dprintf("\nUDC EP1 OUT operation!");
		EPOUT_Handler(1);
	}

	if (IntrUSB & USB_INTR_RESET) {
		dprintf("\nUDC reset intrupt!");  
		udc_reset();
	}
		
	/* Check for endpoint 0 interrupt */
	if (IntrIn & USB_INTR_EP0) {
		dprintf("\nUDC EP0 operations!");
		EP0_Handler();
	}

	if (USB_Version == USB_FS)
		IntrIn  = jz_readw(USB_REG_INTRIN);
	return;
}

void usb_main()
{
	u8 byte;

	__dcache_writeback_all();
	__icache_invalidate_all();

	ep0state = USB_EP0_IDLE;
	Bulk_in_size = 0;
	Bulk_in_finish = 0;
	Bulk_out_size = 0;
	udc_state = IDLE;
	tx_size = 0;
	rx_size = 0;
	finished = 0;

	byte = jz_readb(USB_REG_POWER);
	if ((byte&0x10) == 0) {
		USB_Version = USB_FS;
		fifosize[1] = 64;
		EP0_init(1, 64, 1, 64);
	} else {
		USB_Version = USB_HS;
		fifosize[1] = 512;
		EP0_init(1, 512, 1, 512);
	}

	serial_puts("\n Init UDC");
	USB_Version = USB_HS;

	while (1)
		udc4740Proc();
}
