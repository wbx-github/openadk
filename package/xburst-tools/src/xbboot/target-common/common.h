/*
 * Authors: Xiangfu Liu <xiangfu@sharism.cc>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 3 of the License, or (at your option) any later version.
 */

#ifndef __COMMON_H__
#define __COMMON_H__

typedef unsigned int size_t;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define REG8(addr)	*((volatile u8 *)(addr))
#define REG16(addr)	*((volatile u16 *)(addr))
#define REG32(addr)	*((volatile u32 *)(addr))

u32 UART_BASE;

// tbd: do they have to be copied into globals? or just reference STAGE1_ARGS_ADDR?
volatile u32	ARG_EXTAL;
volatile u32	ARG_CPU_SPEED;
volatile u8	ARG_PHM_DIV;
volatile u32	ARG_UART_BAUD;
volatile u8	ARG_BUS_WIDTH_16;
volatile u8	ARG_BANK_ADDR_2BIT;
volatile u8	ARG_ROW_ADDR;
volatile u8	ARG_COL_ADDR;
volatile u32	ARG_CPU_ID;

#endif // __COMMON_H__
