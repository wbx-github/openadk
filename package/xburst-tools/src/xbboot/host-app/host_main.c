//
// Authors: Wolfgang Spraul <wolfgang@sharism.cc>
// Authors: Xiangfu Liu <xiangfu@sharism.cc>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version
// 3 of the License, or (at your option) any later version.
//

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <usb.h>
#include <time.h>
#include "xburst-tools-config.h"

#define HIWORD(dw)	(((dw) >> 16) & 0xFFFF)
#define LOWORD(dw)	((dw) & 0xFFFF)

#define INGENIC_VENDOR_ID	0x601A
#define INGENIC_XBURST_JZ4740	0x4740
#define INGENIC_XBURST_JZ4760	0x4760

// REQ_ values are negative so they can be mixed together with the VR_ types in a signed integer.
#define REQ_BULK_READ		-1
#define REQ_BULK_WRITE		-2

#define VR_GET_CPU_INFO		0x00
#define VR_SET_DATA_ADDRESS	0x01
#define VR_SET_DATA_LENGTH	0x02
#define VR_FLUSH_CACHES		0x03
#define VR_PROGRAM_START1	0x04
#define VR_PROGRAM_START2	0x05
#define VR_NOR_OPS		0x06
#define VR_NAND_OPS		0x07
#define VR_SDRAM_OPS		0x08
#define VR_CONFIGRATION		0x09
#define VR_GET_NUM		0x0a

#define USB_TIMEOUT		3000
#define VR_GET_CPU_INFO_LEN	8
#define INGENIC_IN_ENDPOINT	0x81
#define INGENIC_OUT_ENDPOINT	0x01

#define STAGE1_FILE_PATH	(DATADIR "stage1.bin")
#define STAGE1_ADDRESS		("0x80002000")

uint8_t xburst_interface = 0;
uint8_t option_upload = 0;
uint16_t xburst_cpu = INGENIC_XBURST_JZ4760;

struct usb_dev_handle* open_xburst_device();
void close_xburst_device(struct usb_dev_handle* xburst_h);
int send_request(struct usb_dev_handle* xburst_h, char* request, char* str_param);
void show_help();

int main(int argc, char** argv)
{
	struct usb_dev_handle* xburst_h;

	if (argc < 2
	    || !strcmp(argv[1], "-h")
	    || !strcmp(argv[1], "--help")) {
		show_help();
		return EXIT_SUCCESS;
	}
	if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version")) {
		printf("xbboot version %s\n", PACKAGE_VERSION);
		return EXIT_SUCCESS;
	}

	xburst_h = NULL;
	if (!strcmp(argv[1], "-u") || !strcmp(argv[1], "--upload")) {
		if (argc != 4) {
			show_help();
			goto xquit;
		}

		option_upload = 1;
		struct timespec timx,tim1;

		tim1.tv_sec = 1;
		tim1.tv_nsec = 0;
		while(1) {
			nanosleep(&tim1,&timx);

			xburst_h = open_xburst_device();
			if (xburst_h) {
				printf("\nInfo - found XBurst boot device.\n");
				if (send_request(xburst_h, "set_addr", STAGE1_ADDRESS)) {
					close_xburst_device(xburst_h);
					continue;
				}
				if (send_request(xburst_h, "bulk_write", STAGE1_FILE_PATH)) {
					close_xburst_device(xburst_h);
					continue;
				}
				if (send_request(xburst_h, "start1", STAGE1_ADDRESS)) {
					close_xburst_device(xburst_h);
					continue;
				}
				if (send_request(xburst_h, "get_info", "NULL")) {
					close_xburst_device(xburst_h);
					continue;
				}
				if (send_request(xburst_h, "set_addr", argv[2])) {
					close_xburst_device(xburst_h);
					continue;
				}
				if (send_request(xburst_h, "bulk_write", argv[3])) {
					close_xburst_device(xburst_h);
					continue;
				}
				if (send_request(xburst_h, "flush_cache","NULL")) {
					close_xburst_device(xburst_h);
					continue;
				}
				if (send_request(xburst_h, "start2", argv[2])) {
					close_xburst_device(xburst_h);
					continue;
				}

				goto xquit;
			}
		}
	}

	xburst_h = open_xburst_device();
	if (xburst_h)
		if (send_request(xburst_h, argv[1], (argc == 2 ? NULL : argv[2]))) {
			close_xburst_device(xburst_h);
			return EXIT_FAILURE;
		}
xquit:
	close_xburst_device(xburst_h);
	return EXIT_SUCCESS;
}


void close_xburst_device(struct usb_dev_handle* xburst_h)
{
        if (xburst_h && xburst_interface)
		usb_release_interface(xburst_h, xburst_interface);

        if (xburst_h)
		usb_close(xburst_h);
}

struct usb_dev_handle* open_xburst_device()
{
	struct usb_device* xburst_dev = 0;
	struct usb_dev_handle* xburst_h = 0;

	usb_init();
	/* usb_set_debug(255); */
	usb_find_busses();
	usb_find_devices();

	// look for Ingenic XBurst USB boot device & interface
	{
		{
			struct usb_bus* usb_bus;
			struct usb_device* usb_dev;

			for (usb_bus = usb_get_busses(); usb_bus != 0; usb_bus = usb_bus->next) {
				for (usb_dev = usb_bus->devices; usb_dev != 0; usb_dev = usb_dev->next) {
					if (usb_dev->descriptor.idVendor == INGENIC_VENDOR_ID) {
						if (usb_dev->descriptor.idProduct == INGENIC_XBURST_JZ4740 || 
						    usb_dev->descriptor.idProduct == INGENIC_XBURST_JZ4760) {
							if (xburst_dev) {
								fprintf(stderr, "Error - more than one XBurst boot device found.\n");
								goto xout;
							}
							xburst_dev = usb_dev;
							xburst_cpu = usb_dev->descriptor.idProduct;
							// keep searching to make sure there is only 1 XBurst device
						}
					}
				}
			}
			if (!xburst_dev) {
				fprintf(stderr, "Info - no XBurst boot device found.\n");
				goto xout;
			}
		}
		{
			struct usb_config_descriptor* usb_config_desc;
			struct usb_interface_descriptor* usb_if_desc;
			struct usb_interface* usb_if;
			int cfg_index, if_index, alt_index;

			for (cfg_index = 0; cfg_index < xburst_dev->descriptor.bNumConfigurations; cfg_index++) {
				usb_config_desc = &xburst_dev->config[cfg_index];
				if (!usb_config_desc) {
					fprintf(stderr, "Error - usb_config_desc NULL\n");
					goto xout;
				}
				for (if_index = 0; if_index < usb_config_desc->bNumInterfaces; if_index++) {
					usb_if = &usb_config_desc->interface[if_index];
					if (!usb_if) {
						fprintf(stderr, "Error - usb_if NULL\n");
						goto xout;
					}
					for (alt_index = 0; alt_index < usb_if->num_altsetting; alt_index++) {
						usb_if_desc = &usb_if->altsetting[alt_index];
						if (!usb_if_desc) {
							fprintf(stderr, "Error - usb_if_desc NULL\n");
							goto xout;
						}
						if (usb_if_desc->bInterfaceClass == 0xFF
						    && usb_if_desc->bInterfaceSubClass == 0) {
							xburst_interface = usb_if_desc->bInterfaceNumber;
							goto interface_found;
						}
					}
				}
			}
		interface_found: ;
		}
	}
	xburst_h = usb_open(xburst_dev);
	if (!xburst_h) {
		fprintf(stderr, "Error - can't open XBurst device: %s\n", usb_strerror());
		goto xout;
	}
	if (usb_claim_interface(xburst_h, xburst_interface) < 0) {
		fprintf(stderr, "Error - can't claim XBurst interface: %s\n", usb_strerror());
		goto xout_xburst_h;
	}

	return xburst_h;

xout_xburst_h:
	usb_close(xburst_h);
xout:
	return NULL;
}

int send_request(struct usb_dev_handle* xburst_h, char* request, char* str_param)
{
	int request_type;
	int usb_status;
	uint32_t u32_param;

	if (!strcmp(request, "bulk_read"))
		request_type = REQ_BULK_READ;
	else if (!strcmp(request, "bulk_write"))
		request_type = REQ_BULK_WRITE;
	else if (!strcmp(request, "VR_GET_CPU_INFO") || !strcmp(request, "get_info"))
		request_type = VR_GET_CPU_INFO;
	else if (!strcmp(request, "VR_SET_DATA_ADDRESS") || !strcmp(request, "set_addr"))
		request_type = VR_SET_DATA_ADDRESS;
	else if (!strcmp(request, "VR_SET_DATA_LENGTH") || !strcmp(request, "set_len"))
		request_type = VR_SET_DATA_LENGTH;
	else if (!strcmp(request, "VR_FLUSH_CACHES") || !strcmp(request, "flush_cache"))
		request_type = VR_FLUSH_CACHES;
	else if (!strcmp(request, "VR_PROGRAM_START1") || !strcmp(request, "start1"))
		request_type = VR_PROGRAM_START1;
	else if (!strcmp(request, "VR_PROGRAM_START2") || !strcmp(request, "start2"))
		request_type = VR_PROGRAM_START2;
	else {
		fprintf(stderr, "Error - unknown vendor request %s - run with --help to see all requests\n", request);
		return 1;
	}

	switch (request_type) {
		case VR_GET_CPU_INFO: {
			char cpu_info_buf[VR_GET_CPU_INFO_LEN+1] = {0};
			usb_status = usb_control_msg(xburst_h,
				/* requesttype */ USB_ENDPOINT_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				/* request     */ VR_GET_CPU_INFO,
				/* value       */ 0,
				/* index       */ 0,
				/* bytes       */ cpu_info_buf,
				/* size        */ VR_GET_CPU_INFO_LEN,
				/* timeout     */ USB_TIMEOUT);

			if (usb_status != VR_GET_CPU_INFO_LEN) {
				fprintf(stderr, "Error - %s() returned %i\n", request, usb_status);
				goto xout_xburst_interface;
			}
			printf("VR_GET_CPU_INFO %s\n", cpu_info_buf);
			break;
		}
		case VR_SET_DATA_ADDRESS:
		case VR_SET_DATA_LENGTH:
		case VR_PROGRAM_START1:
		case VR_PROGRAM_START2: {
			if (str_param == NULL) {
				fprintf(stderr, "Error - number of parameters %s\n", request);
				goto xout_xburst_interface;
			}

			u32_param = strtoul(str_param, 0, 0);
			usb_status = usb_control_msg(xburst_h,
				/* requesttype */ USB_ENDPOINT_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				/* request     */ request_type,
				/* value       */ HIWORD(u32_param),
				/* index       */ LOWORD(u32_param),
				/* bytes       */ 0,
				/* size        */ 0,
				/* timeout     */ USB_TIMEOUT);
			if (usb_status) {
				fprintf(stderr, "Error - %s() returned %i\n", request, usb_status);
				goto xout_xburst_interface;
			}
			printf("%s %lxh\n", request, (unsigned long) u32_param);
			break;
		}
		case VR_FLUSH_CACHES: {
			usb_status = usb_control_msg(xburst_h,
				/* requesttype */ USB_ENDPOINT_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				/* request     */ VR_FLUSH_CACHES,
				/* value       */ 0,
				/* index       */ 0,
				/* bytes       */ 0,
				/* size        */ 0,
				/* timeout     */ USB_TIMEOUT);
			if (usb_status) {
				fprintf(stderr, "Error - %s() returned %i\n", request, usb_status);
				goto xout_xburst_interface;
			}
			printf("VR_FLUSH_CACHES\n");
			break;
		}
		case REQ_BULK_READ: {
			int read_len;
			char* read_buf;

			if (str_param == NULL) {
				fprintf(stderr, "Error - number of parameters %s\n", request);
				goto xout_xburst_interface;
			}

			if (str_param[0] == '0' && str_param[1] == 'x')
				read_len = strtol(&str_param[2], 0, 16);
			else
				read_len = strtol(str_param, 0, 10);

			read_buf = (char*) malloc(read_len);
			if (!read_buf) {
				fprintf(stderr, "Error - cannot allocate %i bytes read buffer.\n", read_len);
				goto xout_xburst_interface;
			}
			usb_status = usb_bulk_read(xburst_h,
				/* endpoint */	INGENIC_IN_ENDPOINT,
				/* bytes */	read_buf,
				/* size */	read_len,
				/* timeout */	USB_TIMEOUT);
			if (usb_status > 0)
				fwrite(read_buf, 1 /* size */, usb_status, stdout);
			free(read_buf);
			if (usb_status < read_len) {
				fprintf(stderr, "Error reading %d bytes (result %i).\n", read_len, usb_status);
				goto xout_xburst_interface;
			}
			break;
		}
		case REQ_BULK_WRITE: {
			char* file_data;
			int file_len;
			FILE* file_h;
			size_t num_read;

			if (str_param == NULL) {
				fprintf(stderr, "Error - number of parameters %s\n", request);
				goto xout_xburst_interface;
			}
			file_h = fopen(str_param, "rb");
			if (!file_h) {
				fprintf(stderr, "Error opening %s.\n", str_param);
				goto xout_xburst_interface;
			}
			if (fseek(file_h, 0, SEEK_END)) {
				fprintf(stderr, "Error seeking to end of %s.\n", str_param);
				fclose(file_h);
				goto xout_xburst_interface;
			}
			file_len = ftell(file_h);
			if (fseek(file_h, 0, SEEK_SET)) {
				fprintf(stderr, "Error seeking to beginning of %s.\n", str_param);
				fclose(file_h);
				goto xout_xburst_interface;
			}
			file_data = (char*) malloc(file_len);
			if (!file_data) {
				fprintf(stderr, "Error allocating %d bytes data.\n", file_len);
				fclose(file_h);
				goto xout_xburst_interface;
			}
			num_read = fread(file_data, 1, file_len, file_h);
			fclose(file_h);
			if (num_read != (size_t) file_len) {
				fprintf(stderr, "Error reading %d bytes (got %d).\n", file_len, num_read);
				free(file_data);
				goto xout_xburst_interface;
			}
			{
				if(option_upload) {
					memcpy(file_data + 8, &xburst_cpu, sizeof(unsigned int));
					option_upload = 0;
				}
			}
			usb_status = usb_bulk_write(xburst_h,
				/* endpoint */	INGENIC_OUT_ENDPOINT,
				/* bytes */	file_data,
				/* size */	file_len,
				/* timeout */	USB_TIMEOUT);
			free(file_data);
			if (usb_status < file_len) {
				fprintf(stderr, "Error writing %d bytes (result %i).\n", file_len, usb_status);
				goto xout_xburst_interface;
			}
			printf("bulk_write successfully wrote %i bytes.\n", usb_status);
			break;
		}
	}

	usleep(100);
	return 0;

xout_xburst_interface:
	return 1;
}

void show_help()
{
	printf("\n"
	       "xbboot version %s - Ingenic XBurst USB Boot Vendor Requests\n"
	       "(c) 2009 Wolfgang Spraul\n"
	       "Report bugs to <wolfgang@sharism.cc>, <xiangfu@sharism.cc>.\n"
	       "\n"
	       "xbboot [vendor_request] ...\n"
	       "  -h --help                                 print this help message\n"
	       "  -v --version                              print the version number\n"
	       "  [-u | --upload] <address> <path>          upload file at <path> to <address> then jump to <address>\n"
	       "\n"
	       "  bulk_read <len>                           read len bulk bytes from USB, write to stdout\n"
	       "  bulk_write <path>                         write file at <path> to USB\n"
	       "  [get_info | VR_GET_CPU_INFO]              read 8-byte CPU info and write to stdout\n"
	       "  [set_addr | VR_SET_DATA_ADDRESS] <addr>   send memory address\n"
	       "  [set_len | VR_SET_DATA_LENGTH] <len>      send data length\n"
	       "  [flush_cache | VR_FLUSH_CACHES]           flush I-Cache and D-Cache\n"
	       "  [start1 | VR_PROGRAM_START1] <addr>       transfer data from D-Cache to I-Cache and branch to I-Cache\n"
	       "  [start2 | VR_PROGRAM_START2] <addr>       branch to <addr> directly\n"
	       "\n"
	       "- all numbers can be prefixed 0x for hex otherwise decimal\n"
	       "\n", PACKAGE_VERSION);
}
