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

#include <stdlib.h>

#include "devmgr.h"
#include "debug.h"

typedef struct device {
	struct device *next;
	uint16_t	vid;
	uint16_t	pid;
	void *data;
} usb_device_t;

static const struct {
	uint16_t vid;
	uint16_t pid;
} devices[] = {
	{ 0x601a, 0x4740 },
	{ 0x601a, 0x4750 },
	{ 0x601a, 0x4760 },
	{ 0, 0 }
};

static usb_device_t *list = NULL;

int is_ingenic(uint16_t vid, uint16_t pid) {
	for(int i = 0; devices[i].vid != 0; i++)
		if(devices[i].vid == vid && devices[i].pid == pid)
			return 1;

	return 0;
}

void add_device(uint16_t vid, uint16_t pid, void *data) {
	usb_device_t *newdev = malloc(sizeof(usb_device_t));

	newdev->next = list;
	newdev->vid = vid;
	newdev->pid = pid;
	newdev->data = data;

	list = newdev;

	debug(LEVEL_DEBUG, "Device manager: registered %04hX:%04hX with data %p\n", vid, pid, data);
}

void enum_devices(void (*handler)(int idx, uint16_t vid, uint16_t pid, void *data)) {
	int idx = 0;

	for(usb_device_t *dev = list; dev; dev = dev->next)
		handler(idx++, dev->vid, dev->pid, dev->data);
}

void *get_device(int idx) {
	for(usb_device_t *dev = list; dev; dev = dev->next)
		if(idx-- == 0)
			return dev->data;

	return NULL;
}
