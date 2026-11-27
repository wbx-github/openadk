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

#ifndef __DEVMGR__H__
#define __DEVMGR__H__

#include <stdint.h>

#define INTERFACE_BOOT	0
#define ENDPOINT_OUT	0x01
#define ENDPOINT_IN	0x81

int is_ingenic(uint16_t vid, uint16_t pid);

void add_device(uint16_t vid, uint16_t pid, void *data);
void enum_devices(void (*handler)(int idx, uint16_t vid, uint16_t pid, void *data));
void *get_device(int idx);

#endif
