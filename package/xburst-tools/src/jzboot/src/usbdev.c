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

#include <errno.h>
#include <libusb.h>

#include "usbdev.h"
#include "debug.h"
#include "devmgr.h"

#define CONTROL_TIMEOUT 5000

static libusb_context *ctx = NULL;

static int translate_libusb(int code);

int usbdev_enumerate() {
	libusb_device **list;
	ssize_t devices_count = libusb_get_device_list(ctx, &list);

	if(devices_count < 0)
		return translate_libusb(devices_count);

	for(int i = 0; i < devices_count; i++) {
		struct libusb_device_descriptor descr;

		int ret = libusb_get_device_descriptor(list[i], &descr);

		if(ret != LIBUSB_SUCCESS) {
			libusb_free_device_list(list, 1);

			return translate_libusb(ret);
		}

		if(is_ingenic(descr.idVendor, descr.idProduct)) {
			add_device(descr.idVendor, descr.idProduct, libusb_ref_device(list[i]));
		}
	}

	libusb_free_device_list(list, 1);

	return 0;
}

int usbdev_init() {
	if(translate_libusb(libusb_init(&ctx)) == -1)
		return -1;

	libusb_set_debug(ctx, get_debug_level());

	return 0;
}

void usbdev_fini() {
	libusb_exit(ctx);
	ctx = NULL;
}

void *usbdev_open(void *dev) {
	libusb_device_handle *hndl;

	if(translate_libusb(libusb_open(dev, &hndl)) == -1)
		return NULL;

	int ret = libusb_kernel_driver_active(hndl, INTERFACE_BOOT);

	if(ret < 0) {
		libusb_close(hndl);

		translate_libusb(ret);

		return NULL;

	} else if(ret == 1) {
		debug(LEVEL_INFO, "Deactivating kernel driver\n");

		if(translate_libusb(libusb_detach_kernel_driver(hndl, INTERFACE_BOOT)) == -1) {
			libusb_close(hndl);

			return NULL;
		}
	}

	if(translate_libusb(libusb_claim_interface(hndl, INTERFACE_BOOT)) == -1) {
		libusb_close(hndl);

		return NULL;
	}

	debug(LEVEL_DEBUG, "Device open\n");

	return hndl;
}

void usbdev_close(void *_hndl) {
	libusb_device_handle *hndl = _hndl;

	libusb_release_interface(hndl, INTERFACE_BOOT);

	libusb_close(hndl);

	debug(LEVEL_DEBUG, "Device closed\n");
}

int usbdev_vendor(void *_hndl, int direction, uint8_t req, uint16_t value, uint16_t index, void *data, uint16_t size) {
	libusb_device_handle *hndl = _hndl;

	uint8_t type =  LIBUSB_REQUEST_TYPE_VENDOR;

	if(direction == USBDEV_FROMDEV)
		type |= LIBUSB_ENDPOINT_IN;

	debug(LEVEL_DEBUG, "Control: type %02hhX, request %hhu, value %hu, index %hu, data %p, size %hu\n", type, req, value, index, data, size);

	int ret = libusb_control_transfer(hndl, type, req, value, index, data, size, CONTROL_TIMEOUT);

	if(ret >= 0)
		return ret;
	else
		return translate_libusb(ret);
}

int usbdev_sendbulk(void *hndl, void *data, int size) {
	int trans;

	debug(LEVEL_DEBUG, "Bulk: writing data %p, size %d\n", data, size);

	if(translate_libusb(libusb_bulk_transfer(hndl, ENDPOINT_OUT, data, size, &trans, CONTROL_TIMEOUT)) == -1) {
		return -1;
	}

	if(trans != size) {
		debug(LEVEL_WARNING, "Bulk data truncated: requested %d, sent %d\n", size, trans);

		errno = EIO;

		return -1;
	}

	return 0;
}

int usbdev_recvbulk(void *hndl, void *data, int size) {
	int trans;

	debug(LEVEL_DEBUG, "Bulk: reading data %p, size %d\n", data, size);

	int ret =  translate_libusb(libusb_bulk_transfer(hndl, ENDPOINT_IN, data, size, &trans, CONTROL_TIMEOUT));

	return ret == -1 ? -1 : trans;
}

static int translate_libusb(int code) {
	switch(code) {
	case LIBUSB_SUCCESS:
		return 0;

	case LIBUSB_ERROR_IO:
		errno = EIO;

		break;

	case LIBUSB_ERROR_INVALID_PARAM:
		errno = EINVAL;

		break;

	case LIBUSB_ERROR_ACCESS:
		errno = EACCES;

		break;

	case LIBUSB_ERROR_NO_DEVICE:
	case LIBUSB_ERROR_NOT_FOUND:
		errno = ENOENT;

		break;

	case LIBUSB_ERROR_BUSY:
		errno = EBUSY;

		break;

	case LIBUSB_ERROR_TIMEOUT:
		errno = ETIMEDOUT;

		break;

	case LIBUSB_ERROR_OVERFLOW:
		errno = EOVERFLOW;

		break;

	case LIBUSB_ERROR_PIPE:
		errno = EPIPE;

		break;

	case LIBUSB_ERROR_INTERRUPTED:
		errno = EINTR;

		break;

	case LIBUSB_ERROR_NO_MEM:
		errno = ENOMEM;

		break;

	case LIBUSB_ERROR_NOT_SUPPORTED:
		errno = ENOTSUP;

		break;


	case LIBUSB_ERROR_OTHER:
	default:
		errno = EFAULT;
	}

	debug(LEVEL_DEBUG, "Translated libusb return %d to %d\n", code, errno);

	return -1;
}
