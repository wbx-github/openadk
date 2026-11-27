/*
 * JzBoot: an USB bootloader for JZ series of Ingenic(R) microprocessors.
 * Copyright (C) 2010  Sergey Gridassov <grindars@gmail.com>,
 *                     Peter Zotov <whitequark@whitequark.org>
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

#ifndef __USBDEV__H__
#define __USBDEV__H__

#include <stdint.h>

int usbdev_init();
void usbdev_fini();

#define USBDEV_FROMDEV	0
#define USBDEV_TODEV	1

int usbdev_enumerate();
void *usbdev_open(void *dev);
void usbdev_close(void *hndl);
int usbdev_vendor(void *hndl, int direction, uint8_t req, uint16_t value, uint16_t index, void *data, uint16_t size);
int usbdev_sendbulk(void *hndl, void *data, int size);
int usbdev_recvbulk(void *hndl, void *data, int size);

#endif
