/*
 * USB_BOOT Handle routines
 *
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

#include "target/jz4740.h"
#include "target/error.h"
#include "target/usb_boot.h"
#include "usb_boot_defines.h"
#include "target/nandflash.h"
#include "usb/udc.h"
#include "usb/usb.h" 

#define dprintf(x) serial_puts(x)

unsigned int (*nand_query)(u8 *);
int (*nand_init)(int bus_width, int row_cycle, int page_size, int page_per_block,
		 int,int,int,int);
int (*nand_fini)(void);
u32 (*nand_program)(void *context, int spage, int pages,int option);
u32 (*nand_erase)(int blk_num, int sblk, int force);
u32 (*nand_read)(void *buf, u32 startpage, u32 pagenum,int option);
u32 (*nand_read_oob)(void *buf, u32 startpage, u32 pagenum);
u32 (*nand_read_raw)(void *buf, u32 startpage, u32 pagenum,int);
u32 (*nand_mark_bad) (int bad);
void (*nand_enable) (unsigned int csn);
void (*nand_disable) (unsigned int csn);

struct hand Hand;
extern u32 Bulk_out_buf[BULK_OUT_BUF_SIZE];
extern u32 Bulk_in_buf[BULK_IN_BUF_SIZE];
extern u16 handshake_PKT[4];
extern udc_state;
extern void *memset(void *s, int c, size_t count);
extern void *memcpy(void *dest, const void *src, size_t count);

u32 ret_dat;
u32 start_addr;  /* program operation start address or sector */
u32 ops_length;  /* number of operation unit ,in byte or sector */
u32 ram_addr;

void dump_data(unsigned int *p, int size)
{
	int i;
	for(i = 0; i < size; i ++)
		serial_put_hex(*p++);
}

void config_flash_info()
{
}

void config_hand()
{
	memcpy(&Hand, (unsigned char *)Bulk_out_buf, sizeof(struct hand));
}

int GET_CPU_INFO_Handle()
{
	dprintf("\n GET_CPU_INFO:\t");
	serial_put_hex(Hand.fw_args.cpu_id);
	switch (Hand.fw_args.cpu_id) {
	case 0x4760:
		HW_SendPKT(0, "Boot4760", 8);
		break;
	case 0x4740:
		HW_SendPKT(0, "Boot4740", 8);
		break;
	default:
		HW_SendPKT(0, " UNKNOW ", 8);
		break;
	}
	udc_state = IDLE;
	return ERR_OK; 
}
	       
int SET_DATA_ADDERSS_Handle(u8 *buf)
{
	USB_DeviceRequest *dreq = (USB_DeviceRequest *)buf;
	start_addr=(((u32)dreq->wValue)<<16)+(u32)dreq->wIndex;
	dprintf("\n SET ADDRESS:\t");
	serial_put_hex(start_addr);
	return ERR_OK;
}
		
int SET_DATA_LENGTH_Handle(u8 *buf)
{
	USB_DeviceRequest *dreq = (USB_DeviceRequest *)buf;
	ops_length=(((u32)dreq->wValue)<<16)+(u32)dreq->wIndex;
	dprintf("\n DATA_LENGTH:\t");
	serial_put_hex(ops_length);
	return ERR_OK;
}

int FLUSH_CACHES_Handle()
{
	return ERR_OK;
}
    
int PROGRAM_START1_Handle(u8 *buf)
{
	USB_DeviceRequest *dreq = (USB_DeviceRequest *)buf;
	ram_addr=(((u32)dreq->wValue)<<16)+(u32)dreq->wIndex;
	return ERR_OK;
}

int PROGRAM_START2_Handle(u8 *buf)
{
	void (*f)(void);
	USB_DeviceRequest *dreq = (USB_DeviceRequest *)buf;
	f=(void *) ((((u32)dreq->wValue)<<16)+(u32)dreq->wIndex);
	__dcache_writeback_all();
	/* stop udc connet before execute program! */
	jz_writeb(USB_REG_POWER,0x0);   /* High speed */

	f();
	return ERR_OK;
}
	      
int NOR_OPS_Handle(u8 *buf)
{
	USB_DeviceRequest *dreq = (USB_DeviceRequest *)buf;
	return ERR_OK;
}

int NAND_OPS_Handle(u8 *buf)
{
	USB_DeviceRequest *dreq = (USB_DeviceRequest *)buf;
	u32 temp;
	int option;
	u8 CSn;

	CSn = (dreq->wValue>>4) & 0xff;
	option = (dreq->wValue>>12) & 0xff;
	nand_enable(CSn);
	switch ((dreq->wValue)&0xf)
	{
	case NAND_QUERY:
		dprintf("\n Request : NAND_QUERY!");
		nand_query((u8 *)Bulk_in_buf);
		HW_SendPKT(1, Bulk_in_buf, 8);
		handshake_PKT[3]=(u16)ERR_OK;
		udc_state = BULK_IN;
		break;
	case NAND_INIT:
		dprintf("\n Request : NAND_INIT!");

		break;
	case NAND_MARK_BAD:
		dprintf("\n Request : NAND_MARK_BAD!");
		ret_dat = nand_mark_bad(start_addr);
		handshake_PKT[0] = (u16) ret_dat;
		handshake_PKT[1] = (u16) (ret_dat>>16);
		HW_SendPKT(1,handshake_PKT,sizeof(handshake_PKT));
		udc_state = IDLE;		

		break;
	case NAND_READ_OOB:
		dprintf("\n Request : NAND_READ_OOB!");
		memset(Bulk_in_buf,0,ops_length*Hand.nand_ps);
		ret_dat = nand_read_oob(Bulk_in_buf,start_addr,ops_length);
		handshake_PKT[0] = (u16) ret_dat;
		handshake_PKT[1] = (u16) (ret_dat>>16);
		HW_SendPKT(1,(u8 *)Bulk_in_buf,ops_length*Hand.nand_ps);
		udc_state = BULK_IN;		
		break;
	case NAND_READ_RAW:
		dprintf("\n Request : NAND_READ_RAW!");
		switch (option)
		{
		case OOB_ECC:
			nand_read_raw(Bulk_in_buf,start_addr,ops_length,option);
			HW_SendPKT(1,(u8 *)Bulk_in_buf,ops_length*(Hand.nand_ps + Hand.nand_os));
			handshake_PKT[0] = (u16) ret_dat;
			handshake_PKT[1] = (u16) (ret_dat>>16);
			udc_state = BULK_IN;
			break;
		default:
			nand_read_raw(Bulk_in_buf,start_addr,ops_length,option);
			HW_SendPKT(1,(u8 *)Bulk_in_buf,ops_length*Hand.nand_ps);
			handshake_PKT[0] = (u16) ret_dat;
			handshake_PKT[1] = (u16) (ret_dat>>16);
			udc_state = BULK_IN;
			break;
		}
		break;
	case NAND_ERASE:
		dprintf("\n Request : NAND_ERASE");
		ret_dat = nand_erase(ops_length,start_addr,
			   Hand.nand_force_erase);
		handshake_PKT[0] = (u16) ret_dat;
		handshake_PKT[1] = (u16) (ret_dat>>16);
		HW_SendPKT(1,handshake_PKT,sizeof(handshake_PKT));
		udc_state = IDLE;
		dprintf(" ... finished.");
		break;
	case NAND_READ:
		dprintf("\n Request : NAND_READ!");
		switch (option) {
		case 	OOB_ECC:
			ret_dat = nand_read(Bulk_in_buf,start_addr,ops_length,OOB_ECC);
			handshake_PKT[0] = (u16) ret_dat;
			handshake_PKT[1] = (u16) (ret_dat>>16);
			HW_SendPKT(1,(u8 *)Bulk_in_buf,ops_length*(Hand.nand_ps + Hand.nand_os ));
			udc_state = BULK_IN;
			break;
		case 	OOB_NO_ECC:
			ret_dat = nand_read(Bulk_in_buf,start_addr,ops_length,OOB_NO_ECC);
			handshake_PKT[0] = (u16) ret_dat;
			handshake_PKT[1] = (u16) (ret_dat>>16);
			HW_SendPKT(1,(u8 *)Bulk_in_buf,ops_length*(Hand.nand_ps + Hand.nand_os));
			udc_state = BULK_IN;
			break;
		case 	NO_OOB:
			ret_dat = nand_read(Bulk_in_buf,start_addr,ops_length,NO_OOB);
			handshake_PKT[0] = (u16) ret_dat;
			handshake_PKT[1] = (u16) (ret_dat>>16);
			HW_SendPKT(1,(u8 *)Bulk_in_buf,ops_length*Hand.nand_ps);
			udc_state = BULK_IN;
			break;
		}
		dprintf(" ... finished.");
		break;
	case NAND_PROGRAM:
		dprintf("\n Request : NAND_PROGRAM!");
		ret_dat = nand_program((void *)Bulk_out_buf,
			     start_addr,ops_length,option);
		handshake_PKT[0] = (u16) ret_dat;
		handshake_PKT[1] = (u16) (ret_dat>>16);
		HW_SendPKT(1,handshake_PKT,sizeof(handshake_PKT));
		udc_state = IDLE;
		dprintf(" ... finished.");
		break;
	case NAND_READ_TO_RAM:
		dprintf("\n Request : NAND_READ_TO_RAM!");
		nand_read((u8 *)ram_addr,start_addr,ops_length,NO_OOB);
		__dcache_writeback_all();
		handshake_PKT[3]=(u16)ERR_OK;
		HW_SendPKT(1,handshake_PKT,sizeof(handshake_PKT));
		udc_state = IDLE;
		break;
	default:
		nand_disable(CSn);
		return ERR_OPS_NOTSUPPORT;
	}

	return ERR_OK;
}

int SDRAM_OPS_Handle(u8 *buf)
{
	USB_DeviceRequest *dreq = (USB_DeviceRequest *)buf;
	u32 temp,i;
	u8 *obj;

	switch ((dreq->wValue)&0xf)
	{
	case 	SDRAM_LOAD:
		ret_dat = (u32)memcpy((u8 *)start_addr,Bulk_out_buf,ops_length);
		handshake_PKT[0] = (u16) ret_dat;
		handshake_PKT[1] = (u16) (ret_dat>>16);
		HW_SendPKT(1,handshake_PKT,sizeof(handshake_PKT));
		udc_state = IDLE;
		break;
	}
	return ERR_OK;
}

void Board_Init()
{
	dprintf("\n Board_init! ");
	serial_put_hex(Hand.fw_args.cpu_id);
	switch (Hand.fw_args.cpu_id)
	{
	case 0x4740:
		nand_init_4740(Hand.nand_bw, Hand.nand_rc, Hand.nand_ps, 
			       Hand.nand_ppb, Hand.nand_bbpage, Hand.nand_bbpos,
			       Hand.nand_force_erase, Hand.nand_eccpos);
	
		nand_program = nand_program_4740;
		nand_erase = nand_erase_4740;
		nand_read = nand_read_4740;
		nand_read_oob = nand_read_oob_4740;
		nand_read_raw = nand_read_raw_4740;
		nand_query = nand_query_4740;
		nand_enable = nand_enable_4740;
		nand_disable = nand_disable_4740;
		nand_mark_bad = nand_mark_bad_4740;
		break;
	case 0x4760:
		nand_init_4760(Hand.nand_bw, Hand.nand_rc, Hand.nand_ps,
			       Hand.nand_ppb, Hand.nand_bchbit, Hand.nand_eccpos,
			       Hand.nand_bbpos, Hand.nand_bbpage, Hand.nand_force_erase);

		nand_program=nand_program_4760;
		nand_erase  =nand_erase_4760;
		nand_read   =nand_read_4760;
		nand_read_oob=nand_read_oob_4760;
		nand_read_raw=nand_read_raw_4760;
		nand_query  = nand_query_4760;
		nand_enable = nand_enable_4760;
		nand_disable= nand_disable_4760;
		nand_mark_bad = nand_mark_bad_4760;
		break;
	default:
		serial_puts("\n Not support CPU ID!");
	}
}

int CONFIGRATION_Handle(u8 *buf)
{
	dprintf("\n Configuration:\t");

	USB_DeviceRequest *dreq = (USB_DeviceRequest *)buf;
	switch ((dreq->wValue)&0xf) {
	case DS_flash_info:
		dprintf("DS_flash_info_t!");
		config_flash_info();
		break;

	case DS_hand:
		dprintf("DS_hand_t!");
		config_hand();
		break;
	default:
		;
	}

	Board_Init();
	return ERR_OK;
}


int RESET_Handle(u8 *buf)
{
	dprintf("\n RESET Device");
	__wdt_select_extalclk();
	__wdt_select_clk_div64();
	__wdt_set_data(100);
	__wdt_set_count(0);
	__tcu_start_wdt_clock();
	__wdt_start();
	while(1);
}
