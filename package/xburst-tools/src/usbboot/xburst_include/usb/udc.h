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
#ifndef __UDC_H__
#define __UDC_H__

#include "usb.h"
#define MAX_EP0_SIZE	64
#define MAX_EP1_SIZE	512

#define USB_HS      0
#define USB_FS      1
#define USB_LS      2

//definitions of EP0
#define USB_EP0_IDLE	0
#define USB_EP0_RX	1
#define USB_EP0_TX	2
/* Define maximum packet size for endpoint 0 */
#define M_EP0_MAXP	64
/* Endpoint 0 status structure */



static __inline__ void usb_setb(u32 port, u8 val)
{
	volatile u8 *ioport = (volatile u8 *)(port);
	*ioport = (*ioport) | val;
}

static __inline__ void usb_clearb(u32 port, u8 val)
{
	volatile u8 *ioport = (volatile u8 *)(port);
	*ioport = (*ioport) & ~val;
}

static __inline__ void usb_setw(u32 port, u16 val)
{
	volatile u16 *ioport = (volatile u16 *)(port);
	*ioport = (*ioport) | val;
}

static __inline__ void usb_clearw(u32 port, u16 val)
{
	volatile u16 *ioport = (volatile u16 *)(port);
	*ioport = (*ioport) & ~val;
}

#endif //__UDC_H__
