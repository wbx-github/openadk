/*
 * Copyright(C) 2009  Qi Hardware Inc.,
 * Authors: Xiangfu Liu <xiangfu@sharism.cc>
 *          Marek Lindner <lindner_marek@yahoo.de>
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

#include <stdio.h>
#include <string.h>
#include <usb.h>
#include "usb_boot_defines.h"
#include "ingenic_usb.h"
#include "ingenic_request.h"

extern unsigned int total_size;

static int get_ingenic_device(struct ingenic_dev *id)
{
	struct usb_bus *ub, *usb_bus;
	struct usb_device *usb_dev;
	int count = 0;

	ub = usb_get_busses();

	for (usb_bus = ub; usb_bus != NULL; usb_bus = usb_bus->next) {
		for (usb_dev = usb_bus->devices; usb_dev != NULL;
		     usb_dev = usb_dev->next) {

			if ((usb_dev->descriptor.idVendor == VENDOR_ID) &&
				(usb_dev->descriptor.idProduct == PRODUCT_ID_4740 ||
				usb_dev->descriptor.idProduct == PRODUCT_ID_4760)) {
				id->usb_dev = usb_dev;
				count++;
			}

		}
	}

	return count;
}

static int get_ingenic_interface(struct ingenic_dev *id)
{
	struct usb_config_descriptor *usb_config_desc;
	struct usb_interface_descriptor *usb_if_desc;
	struct usb_interface *usb_if;
	int config_index, if_index, alt_index;

	for (config_index = 0;
	     config_index < id->usb_dev->descriptor.bNumConfigurations;
	     config_index++) {
		usb_config_desc = &id->usb_dev->config[config_index];

		if (!usb_config_desc)
			return 0;

		for (if_index = 0; if_index < usb_config_desc->bNumInterfaces;
		     if_index++) {
			usb_if = &usb_config_desc->interface[if_index];

			if (!usb_if)
				return 0;

			for (alt_index = 0; alt_index < usb_if->num_altsetting;
			     alt_index++) {
				usb_if_desc = &usb_if->altsetting[alt_index];

				if (!usb_if_desc)
					return 0;

				if ((usb_if_desc->bInterfaceClass == 0xff) &&
					(usb_if_desc->bInterfaceSubClass == 0)) {
					id->interface =
						usb_if_desc->bInterfaceNumber;
					return 1;
				}
			}
		}
	}

	return 0;
}

int usb_ingenic_init(struct ingenic_dev *id)
{
	int num_ingenic, status = -1;

	memset(id, 0, sizeof(struct ingenic_dev));

	usb_init();
 	/* usb_set_debug(255); */
	usb_find_busses();
	usb_find_devices();

	num_ingenic = get_ingenic_device(id);

	if (num_ingenic == 0) {
		fprintf(stderr, "Error - no XBurst device found\n");
		goto out;
	}

	if (num_ingenic > 1) {
		fprintf(stderr, "Error - too many XBurst devices found: %i\n",
			num_ingenic);
		goto out;
	}

	id->usb_handle = usb_open(id->usb_dev);
	if (!id->usb_handle) {
		fprintf(stderr, "Error - can't open XBurst device: %s\n",
			usb_strerror());
		goto out;
	}

	if (get_ingenic_interface(id) < 1) {
		fprintf(stderr, "Error - can't find XBurst interface\n");
		goto out;
	}

	if (usb_claim_interface(id->usb_handle, id->interface)
	    < 0) {
		fprintf(stderr, "Error - can't claim XBurst interface: %s\n",
			usb_strerror());
		goto out;
	}

	status = 1;

out:
	return status;
}

int usb_get_ingenic_cpu(struct ingenic_dev *id)
{
	int status;

	memset(&id->cpu_info_buff, 0,
	       ARRAY_SIZE(id->cpu_info_buff));

	sleep(1);
	status = usb_control_msg(id->usb_handle,
	  /* bmRequestType */ USB_ENDPOINT_IN | USB_TYPE_VENDOR |USB_RECIP_DEVICE,
	  /* bRequest      */ VR_GET_CPU_INFO,
	  /* wValue        */ 0,
	  /* wIndex        */ 0,
	  /* Data          */ id->cpu_info_buff,
	  /* wLength       */ 8,
			      USB_TIMEOUT);

	if (status != sizeof(id->cpu_info_buff) - 1 ) {
		fprintf(stderr, "Error - "
			"can't retrieve XBurst CPU information: %i\n", status);
		return status;
	}

	id->cpu_info_buff[8] = '\0';
	printf(" CPU data: %s\n", id->cpu_info_buff);

	if (!strcmp(id->cpu_info_buff,"JZ4740V1")) return JZ4740V1;
	if (!strcmp(id->cpu_info_buff,"JZ4750V1")) return JZ4750V1;
	if (!strcmp(id->cpu_info_buff,"JZ4760V1")) return JZ4760V1;
	if (!strcmp(id->cpu_info_buff,"Boot4740")) return BOOT4740;
	if (!strcmp(id->cpu_info_buff,"Boot4750")) return BOOT4750;
	if (!strcmp(id->cpu_info_buff,"Boot4760")) return BOOT4760;

	return -1;
}

int usb_ingenic_flush_cache(struct ingenic_dev *id)
{
	int status;

	status = usb_control_msg(id->usb_handle,
	  /* bmRequestType */ USB_ENDPOINT_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
	  /* bRequest      */ VR_FLUSH_CACHES,
	  /* wValue        */ 0,
	  /* wIndex        */ 0,
	  /* Data          */ 0,
	  /* wLength       */ 0,
			      USB_TIMEOUT);

	if (status != 0) {
		fprintf(stderr, "Error - can't flush cache: %i\n", status);
		return status;
	}

	return 1;
}

int usb_send_data_length_to_ingenic(struct ingenic_dev *id, int len)
{
	int status;
	/* tell the device the length of the file to be uploaded */
	status = usb_control_msg(id->usb_handle,
	  /* bmRequestType */ USB_ENDPOINT_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
	  /* bRequest      */ VR_SET_DATA_LENGTH,
	  /* wValue        */ STAGE_ADDR_MSB(len),
	  /* wIndex        */ STAGE_ADDR_LSB(len),
	  /* Data          */ 0,
	  /* wLength       */ 0,
			      USB_TIMEOUT);

	if (status != 0) {
		fprintf(stderr, "Error - "
			"can't set data length on Ingenic device: %i\n", status);
		return -1;
	}

	return 1;
}

int usb_send_data_address_to_ingenic(struct ingenic_dev *id,
				     unsigned int stage_addr)
{
	int status;
	/* tell the device the RAM address to store the file */
	status = usb_control_msg(id->usb_handle,
	  /* bmRequestType */ USB_ENDPOINT_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
	  /* bRequest      */ VR_SET_DATA_ADDRESS,
	  /* wValue        */ STAGE_ADDR_MSB(stage_addr),
	  /* wIndex        */ STAGE_ADDR_LSB(stage_addr),
	  /* Data          */ 0,
	  /* wLength       */ 0,
			      USB_TIMEOUT);

	if (status != 0) {
		fprintf(stderr, "Error - "
			"can't set the address on Ingenic device: %i\n", status);
		return -1;
	}

	return 1;
}

int usb_send_data_to_ingenic(struct ingenic_dev *id)
{
	int status;
	status = usb_bulk_write(id->usb_handle,
	/* endpoint         */ INGENIC_OUT_ENDPOINT,
	/* bulk data        */ (char *)id->file_buff,
	/* bulk data length */ id->file_len,
			       USB_TIMEOUT);
	if (status < (int)id->file_len) {
		fprintf(stderr, "Error - "
			"can't send bulk data to Ingenic CPU: %i %s\n", status, usb_strerror());
		return -1;
	}

	return 1;
}

int usb_read_data_from_ingenic(struct ingenic_dev *id,
			       unsigned char *buff, unsigned int len)
{
	int status;
	status = usb_bulk_read(id->usb_handle,
	/* endpoint         */ INGENIC_IN_ENDPOINT,
	/* bulk data        */ (char *)buff,
	/* bulk data length */ len,
			       USB_TIMEOUT);

	if (status < (int)len) {
		fprintf(stderr, "Error - "
			"can't read bulk data from Ingenic device:%i\n", status);
		return -1;
	}

	return 1;
}

int usb_ingenic_start(struct ingenic_dev *id, int rqst, unsigned int stage_addr)
{
	int status;

	/* tell the device to start the uploaded device */
	status = usb_control_msg(id->usb_handle,
	  /* bmRequestType */ USB_ENDPOINT_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
	  /* bRequest      */ rqst,
	  /* wValue        */ STAGE_ADDR_MSB(stage_addr),
	  /* wIndex        */ STAGE_ADDR_LSB(stage_addr),
	  /* Data          */ 0,
	  /* wLength       */ 0,
			      USB_TIMEOUT);

	if (status != 0) {
		fprintf(stderr, "Error - can't start the uploaded binary "
			"on the Ingenic device: %i\n", status);
		return status;
	}
	return 1;
}

int usb_ingenic_upload(struct ingenic_dev *id, int stage)
{
	unsigned int stage_addr;
	unsigned int stage2_addr;
	int rqst = VR_PROGRAM_START1;

	stage2_addr = 0x80000000 + total_size - CODE_SIZE;
	stage_addr = (stage == 1 ? 0x80002000 : stage2_addr);

	usb_send_data_address_to_ingenic(id, stage_addr);
	printf(" Download stage %d program and execute at 0x%08x\n",
	       stage, (stage_addr));
	usb_send_data_to_ingenic(id);

	if (stage == 2) {
		if (usb_get_ingenic_cpu(id) < 1)
			return -1;
		usb_ingenic_flush_cache(id);
		rqst = VR_PROGRAM_START2;
	}

	usleep(100);
	if (usb_ingenic_start(id, rqst, stage_addr) < 1)
		return -1;
	usleep(100);
	if (usb_get_ingenic_cpu(id) < 1)
		return -1;

	return 1;
}

void usb_ingenic_cleanup(struct ingenic_dev *id)
{
	if ((id->usb_handle) && (id->interface))
		usb_release_interface(id->usb_handle,
				      id->interface);

	if (id->usb_handle)
		usb_close(id->usb_handle);
}

int usb_ingenic_nand_ops(struct ingenic_dev *id, int ops)
{
	int status;
	status = usb_control_msg(id->usb_handle,
	  /* bmRequestType */ USB_ENDPOINT_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
	  /* bRequest      */ VR_NAND_OPS,
	  /* wValue        */ ops & 0xffff,
	  /* wIndex        */ 0,
	  /* Data          */ 0,
	  /* wLength       */ 0,
			      USB_TIMEOUT);

	if (status != 0) {
		fprintf(stderr, "Error - "
			"can't set Ingenic device nand ops: %i\n", status);
		return -1;
	}

	return 1;
}

int usb_ingenic_configration(struct ingenic_dev *id, int ops)
{
	int status;
	status = usb_control_msg(id->usb_handle,
	  /* bmRequestType */ USB_ENDPOINT_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
	  /* bRequest      */ VR_CONFIGRATION,
	  /* wValue        */ ops,
	  /* wIndex        */ 0,
	  /* Data          */ 0,
	  /* wLength       */ 0,
			      USB_TIMEOUT);

	if (status != 0) {
		fprintf(stderr, "Error - "
			"can't init Ingenic configration: %i\n", status);
		return -1;
	}

	return 1;
}

int usb_ingenic_sdram_ops(struct ingenic_dev *id, int ops)
{
	int status;
	status = usb_control_msg(id->usb_handle,
	  /* bmRequestType */ USB_ENDPOINT_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
	  /* bRequest      */ VR_SDRAM_OPS,
	  /* wValue        */ ops,
	  /* wIndex        */ 0,
	  /* Data          */ 0,
	  /* wLength       */ 0,
			      USB_TIMEOUT);

	if (status != 0) {
		fprintf(stderr, "Error - "
			"Device can't load file to sdram: %i\n", status);
		return -1;
	}

	return 1;
}

int usb_ingenic_reset(struct ingenic_dev *id, int ops)
{
	int status;
	status = usb_control_msg(id->usb_handle,
	  /* bmRequestType */ USB_ENDPOINT_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
	  /* bRequest      */ VR_RESET,
	  /* wValue        */ ops,
	  /* wIndex        */ 0,
	  /* Data          */ 0,
	  /* wLength       */ 0,
			      USB_TIMEOUT);

	if (status != 0) {
		fprintf(stderr, "Error - "
			"reset XBurst device: %i\n", status);
		return -1;
	}

	return 1;
}
