/*
 * Authors: Xiangfu Liu <xiangfu@sharism.cc>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 3 of the License, or (at your option) any later version.
 */

#ifndef __XBURST_TYPES_H__
#define __XBURST_TYPES_H__

typedef unsigned int size_t;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define REG8(addr)	*((volatile u8 *)(addr))
#define REG16(addr)	*((volatile u16 *)(addr))
#define REG32(addr)	*((volatile u32 *)(addr))

#endif /* __XBURST_TYPES_H__ */
