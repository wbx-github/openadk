/*
 * device board 
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
#ifndef _CONFIGS_H
#define _CONFIGS_H

/* Here are these common definitions */
/* Once your system configration change, just modify the file */

#include "target/xburst_types.h"

#define CONFIG_NR_DRAM_BANKS	1	/* SDRAM BANK Number: 1, 2*/
#define SDRAM_CASL		3	/* CAS latency: 2 or 3 */
/* SDRAM Timings, unit: ns */
#define SDRAM_TRAS		45	/* RAS# Active Time */
#define SDRAM_RCD		20	/* RAS# to CAS# Delay */
#define SDRAM_TPC		20	/* RAS# Precharge Time */
#define SDRAM_TRWL		7	/* Write Latency Time */
#define SDRAM_TREF	        15625	/* Refresh period: 4096 refresh cycles/64ms */

extern volatile u32 CPU_ID;
extern volatile u8 SDRAM_BW16;
extern volatile u8 SDRAM_BANK4;
extern volatile u8 SDRAM_ROW;
extern volatile u8 SDRAM_COL;
extern volatile u8 CONFIG_MOBILE_SDRAM;
extern volatile u32 CFG_CPU_SPEED;
extern volatile u8 PHM_DIV;
extern volatile u32 CFG_EXTAL;
extern volatile u32 CONFIG_BAUDRATE;
extern volatile u32 UART_BASE;
extern volatile u8 CONFIG_MOBILE_SDRAM;
extern volatile u8 IS_SHARE;
#endif 
