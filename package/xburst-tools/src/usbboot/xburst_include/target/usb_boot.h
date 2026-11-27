/*
 * "Ingenic flash tool" - flash the Ingenic CPU via USB
 *
 * Copyright 2009 (C) Qi Hardware Inc.,
 * Author: Xiangfu Liu <xiangfu@sharism.cc>
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

#ifndef __USB_BOOT_H__
#define __USB_BOOT_H__

#define BULK_OUT_BUF_SIZE (2048 * 128)
#define BULK_IN_BUF_SIZE (2048 * 128)

enum UDC_STATE
{
	IDLE,
	BULK_IN,
	BULK_OUT
};

#endif	/* __USB_BOOT_H__ */
