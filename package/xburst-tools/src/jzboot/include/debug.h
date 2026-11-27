/*
 * JzBoot: an USB bootloader for JZ series of Ingenic(R) microprocessors.
 * Copyright (C) 2010  Sergey Gridassov <grindars@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __DEBUG__H__
#define __DEBUG__H__

void set_debug_level(int level);
int get_debug_level();
void hexdump(const void *data, size_t size);

void debug(int level, const char *fmt, ...);

#define LEVEL_SILENT	0
#define LEVEL_ERROR	1
#define LEVEL_WARNING	2
#define LEVEL_INFO	3
#define LEVEL_DEBUG	4

#endif
