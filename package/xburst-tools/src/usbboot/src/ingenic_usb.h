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

#ifndef __INGENIC_USB_H__
#define __INGENIC_USB_H__

#include <stdint.h>
#include "cmd.h"

#define INGENIC_OUT_ENDPOINT	0x01
#define INGENIC_IN_ENDPOINT	0x81

#define JZ4740V1	1
#define JZ4750V1	2
#define JZ4760V1	3
#define BOOT4740	4
#define BOOT4750	5
#define BOOT4760	6

#define STAGE_ADDR_MSB(addr) ((addr) >> 16)
#define STAGE_ADDR_LSB(addr) ((addr) & 0xffff)

#define USB_PACKET_SIZE	512
#define USB_TIMEOUT	30000

#define VENDOR_ID	0x601a
#define PRODUCT_ID_4740	0x4740
#define PRODUCT_ID_4750	0x4750
#define PRODUCT_ID_4760	0x4760

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

struct ingenic_dev {
	struct usb_device *usb_dev;
	struct usb_dev_handle *usb_handle;
	uint8_t interface;
	char cpu_info_buff[9];
	unsigned char *file_buff;
	unsigned int file_len;
};

int usb_ingenic_init(struct ingenic_dev *id);
int usb_get_ingenic_cpu(struct ingenic_dev *id);
int usb_ingenic_upload(struct ingenic_dev *id, int stage);
void usb_ingenic_cleanup(struct ingenic_dev *id);
int usb_send_data_address_to_ingenic(struct ingenic_dev *id,
				     unsigned int stage_addr);
int usb_send_data_to_ingenic(struct ingenic_dev *id);
int usb_send_data_length_to_ingenic(struct ingenic_dev *id,
				    int len);
int usb_ingenic_nand_ops(struct ingenic_dev *id, int ops);
int usb_ingenic_sdram_ops(struct ingenic_dev *id, int ops);
int usb_read_data_from_ingenic(struct ingenic_dev *id, unsigned char *buff, unsigned int len);
int usb_ingenic_reset(struct ingenic_dev *id, int ops);
int usb_ingenic_start(struct ingenic_dev *id, int rqst, unsigned int stage_addr);
int usb_ingenic_configration(struct ingenic_dev *id, int ops);

#endif	/* __INGENIC_USB_H__ */
