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

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

#include "ingenic.h"
#include "usbdev.h"
#include "debug.h"
#include "app_config.h"

#define HANDLE ingenic_handle_t *handle = hndl
#define BUILDTYPE(cmdset, id) (((cmdset) << 16) | (0x##id & 0xFFFF))
#define CPUID(id) ((id) & 0xFFFF)
#define CMDSET(id) (((id) & 0xFFFF0000) >> 16)

#define CFGOPT(name, var, exp) { \
	char *str = cfg_getenv(name); \
	if(str == NULL) { \
		debug(LEVEL_ERROR, "%s is not set\n", name); errno = EINVAL; return -1; }; \
		int v = atoi(str); \
		if(!(exp)) { debug(LEVEL_ERROR, "%s must be in %s\n", name, #exp); return -1; }; \
		var = v; \
	}

#define NOPT(name, var, exp) { \
	char *str = cfg_getenv("NAND_" name); \
	if(str == NULL) { debug(LEVEL_ERROR, "%s is not set\n", "NAND_" name); errno = EINVAL; return -1; }; \
	int v = atoi(str); \
	if(!(exp)) { debug(LEVEL_ERROR, "%s must be in %s\n", "NAND_" name, #exp); return -1; }; \
	var = v; \
}

#define CALLBACK(function, ...) if(handle->callbacks && handle->callbacks->function) handle->callbacks->function(__VA_ARGS__, handle->callbacks_data)

typedef struct {
	void *usb;
	uint32_t type;
	uint32_t total_sdram_size;

	const ingenic_callbacks_t *callbacks;
	void *callbacks_data;

	firmware_config_t cfg;
	nand_config_t nand;
} ingenic_handle_t;

static const struct {
	const char * const magic;
	uint32_t id;
} magic_list[] = {
	{ "JZ4740V1", BUILDTYPE(CMDSET_SPL, 4740) },
	{ "JZ4750V1", BUILDTYPE(CMDSET_SPL, 4750) },
	{ "JZ4760V1", BUILDTYPE(CMDSET_SPL, 4760) },

	{ "Boot4740", BUILDTYPE(CMDSET_USBBOOT, 4740) },
	{ "Boot4750", BUILDTYPE(CMDSET_USBBOOT, 4750) },
	{ "Boot4760", BUILDTYPE(CMDSET_USBBOOT, 4760) },

	{ NULL, 0 }
};

static uint32_t ingenic_probe(void *usb_hndl) {
	char magic[9];

	if(usbdev_vendor(usb_hndl, USBDEV_FROMDEV, VR_GET_CPU_INFO, 0, 0, magic, 8) == -1)
			return 0;

	magic[8] = 0;

	for(int i = 0; magic_list[i].magic != NULL; i++)
		if(strcmp(magic_list[i].magic, magic) == 0)
			return magic_list[i].id;

	debug(LEVEL_ERROR, "Unknown CPU: '%s'\n", magic);
	errno = EINVAL;
	return 0;
}

void *ingenic_open(void *usb_hndl) {
	uint32_t type = ingenic_probe(usb_hndl);

	if(type == 0)
		return NULL;

	ingenic_handle_t *ret  = malloc(sizeof(ingenic_handle_t));
	ret->usb = usb_hndl;
	ret->type = type;
	ret->callbacks = NULL;

	return ret;
}

int ingenic_redetect(void *hndl) {
	HANDLE;

	uint32_t type = ingenic_probe(handle->usb);

	if(type == 0)
		return -1;

	uint32_t prev = handle->type;

	handle->type = type;

	if(CMDSET(prev) != CMDSET(type)) {
		CALLBACK(cmdset_change, CMDSET(type));
	}

	return 0;
}

void ingenic_set_callbacks(void *hndl, const ingenic_callbacks_t *callbacks, void *arg) {
	HANDLE;

	handle->callbacks = callbacks;
	handle->callbacks_data = arg;
}

int ingenic_cmdset(void *hndl) {
	HANDLE;

	return CMDSET(handle->type);
}

int ingenic_type(void *hndl) {
	HANDLE;

	return CPUID(handle->type);
}

void ingenic_close(void *hndl) {
	HANDLE;

	free(handle);
}

int ingenic_rebuild(void *hndl) {
	HANDLE;
	unsigned int cpu_speed;	/* the uint8_t in handle structure won't do for values > 255 */

	handle->cfg.cpu_id = CPUID(handle->type);

	CFGOPT("EXTCLK", handle->cfg.ext_clk, v <= 27 && v >= 12);
	CFGOPT("CPUSPEED", cpu_speed, (v % 12) == 0);
	handle->cfg.cpu_speed = cpu_speed / handle->cfg.ext_clk;
	CFGOPT("PHMDIV", handle->cfg.phm_div, v <= 32 && v >= 2);
	CFGOPT("USEUART", handle->cfg.use_uart, 1);
	CFGOPT("BAUDRATE", handle->cfg.baudrate, 1);

	CFGOPT("SDRAM_BUSWIDTH", handle->cfg.bus_width, (v == 16) || (v == 32));
	handle->cfg.bus_width = handle->cfg.bus_width == 16 ? 1 : 0;
	CFGOPT("SDRAM_BANKS", handle->cfg.bank_num, (v >= 4) && ((v % 4) == 0));
	handle->cfg.bank_num /= 4;
	CFGOPT("SDRAM_ROWADDR", handle->cfg.row_addr, 1);
	CFGOPT("SDRAM_COLADDR", handle->cfg.col_addr, 1);
	CFGOPT("SDRAM_ISMOBILE", handle->cfg.is_mobile, v == 0 || v == 1);
	CFGOPT("SDRAM_ISBUSSHARE", handle->cfg.is_busshare, v == 0 || v == 1);

	memset(&handle->cfg.debug, 0, sizeof(ingenic_stage1_debug_t));

	handle->total_sdram_size = (uint32_t)
		(2 << (handle->cfg.row_addr + handle->cfg.col_addr - 1)) * 2
		* (handle->cfg.bank_num + 1) * 2
		* (2 - handle->cfg.bus_width);

	handle->nand.cpuid = CPUID(handle->type);

	NOPT("BUSWIDTH", handle->nand.nand_bw, 1);
	NOPT("ROWCYCLES", handle->nand.nand_rc, 1);
	NOPT("PAGESIZE", handle->nand.nand_ps, 1);
	NOPT("PAGEPERBLOCK", handle->nand.nand_ppb, 1);
	NOPT("FORCEERASE", handle->nand.nand_force_erase, 1);
// FIXME: pn is not set by xburst-tools usbboot. Is this intended?
	NOPT("OOBSIZE", handle->nand.nand_os, 1);
	NOPT("ECCPOS", handle->nand.nand_eccpos, 1);
	NOPT("BADBLOCKPOS", handle->nand.nand_bbpos, 1);
	NOPT("BADBLOCKPAGE", handle->nand.nand_bbpage, 1);
	NOPT("PLANENUM", handle->nand.nand_plane, 1);
	NOPT("BCHBIT", handle->nand.nand_bchbit, 1);
	NOPT("WPPIN", handle->nand.nand_wppin, 1);
	NOPT("BLOCKPERCHIP", handle->nand.nand_bpc, 1);

	return 0;
}

uint32_t ingenic_sdram_size(void *hndl) {
	HANDLE;

	return handle->total_sdram_size;
}

static int ingenic_wordop(void *usb, int op, uint32_t base) {
	return usbdev_vendor(usb, USBDEV_TODEV, op, (base >> 16), base & 0xFFFF, 0, 0);
}

int ingenic_stage1_debugop(void *hndl, const char *filename, uint32_t op, uint32_t pin, uint32_t base, uint32_t size) {
	HANDLE;

	handle->cfg.debug.debug_ops = op;
	handle->cfg.debug.pin_num = pin;
	handle->cfg.debug.start = base;
	handle->cfg.debug.size = size;

	int ret = ingenic_loadstage(handle, INGENIC_STAGE1, filename);

	memset(&handle->cfg.debug, 0, sizeof(ingenic_stage1_debug_t));

	return ret;
}

int ingenic_loadstage(void *hndl, int id, const char *file) {
	HANDLE;

	if(file == NULL) {
		errno = EINVAL;

		return -1;
	}

	uint32_t base;
	int cmd;

	switch(id) {
	case INGENIC_STAGE1:
		base = SDRAM_BASE + STAGE1_BASE;
		cmd = VR_PROGRAM_START1;

		break;

	case INGENIC_STAGE2:
		base = SDRAM_BASE + handle->total_sdram_size - STAGE2_CODESIZE;
		cmd = VR_PROGRAM_START2;

		break;

	default:
		errno = EINVAL;

		return -1;
	}

	FILE *fd = fopen(file, "rb");

	if(fd == NULL) 
		return -1;

	fseek(fd, 0, SEEK_END);
	int size = ftell(fd);
	fseek(fd, 0, SEEK_SET);

	void *data = malloc(size);
	size_t read_bytes = fread(data, 1, size, fd);

	fclose(fd);

	if(read_bytes != size) {
		free(data);

		errno = EIO;

		return -1;
	}

	memcpy(data + 8, &handle->cfg, sizeof(firmware_config_t));

	if(ingenic_wordop(handle->usb, VR_SET_DATA_ADDRESS, base) == -1) {
		free(data);

		return -1;
	}

	int ret = usbdev_sendbulk(handle->usb, data, size);

	free(data);

	if(ret == -1)
		return -1;

	if(id == INGENIC_STAGE2) {
		ret = usbdev_vendor(handle->usb, USBDEV_TODEV, VR_FLUSH_CACHES, 0, 0, 0, 0);

		if(ret == -1)
			return -1;
	}

	ret = usbdev_vendor(handle->usb, USBDEV_TODEV, cmd, (base >> 16), base & 0xFFFF, 0, 0);

	if(ret == -1)
		return -1;

	usleep(250);

	if(id == INGENIC_STAGE2)
		return ingenic_redetect(hndl);
	else
		return 0;
}

int ingenic_memtest(void *hndl, const char *filename, uint32_t base, uint32_t size, uint32_t *fail) {
	HANDLE;

	int ret = ingenic_stage1_debugop(handle, filename, STAGE1_DEBUG_MEMTEST, 0, base, size);

	if(ret == -1)
		return -1;

	uint32_t data[2];

	ret = usbdev_recvbulk(handle->usb, &data, sizeof(data));

	if(ret == -1)
		return -1;

	hexdump(data, ret);

	if(ret < 4) {
		errno = EIO;

		return -1;
	}

	if(data[0] != 0) {
		errno = EFAULT;

		*fail = data[0];

		return -1;
	}

	return 0;
}

int ingenic_configure_stage2(void *hndl) {
	HANDLE;

// DS_flash_info (nand_config_t only) is not implemented in stage2, so using DS_hand (nand_config_t + firmware_config_t)
	uint8_t *hand = malloc(sizeof(nand_config_t) + sizeof(firmware_config_t));

	memcpy(hand, &handle->nand, sizeof(nand_config_t));
	memcpy(hand + sizeof(nand_config_t), &handle->cfg, sizeof(firmware_config_t));

	int ret = usbdev_sendbulk(handle->usb, hand, sizeof(nand_config_t) + sizeof(firmware_config_t));

	free(hand);

	if(ret == -1)
		return -1;

	if(usbdev_vendor(handle->usb, USBDEV_TODEV, VR_CONFIGRATION, DS_hand, 0, 0, 0) == -1)
		return -1;

	uint32_t result[8];

	ret = usbdev_recvbulk(handle->usb, result, sizeof(result));

	if(ret == -1)
		return -1;

	return 0;
}

int ingenic_load_sdram(void *hndl, void *data, uint32_t base, uint32_t size) {
	HANDLE;

	int max = size, value = 0;

	CALLBACK(progress, PROGRESS_INIT, 0, max);

	while(size) {
		int block = size > STAGE2_IOBUF ? STAGE2_IOBUF : size;

		debug(LEVEL_DEBUG, "Loading %d bytes from %p to 0x%08X\n", block, data, base);

		if(usbdev_sendbulk(handle->usb, data, block) == -1)
			return -1;
		
		if(ingenic_wordop(handle->usb, VR_SET_DATA_ADDRESS, base) == -1)
			return -1;

		if(ingenic_wordop(handle->usb, VR_SET_DATA_LENGTH, block) == -1)
			return -1;


		if(usbdev_vendor(handle->usb, USBDEV_TODEV, VR_SDRAM_OPS, SDRAM_LOAD, 0, 0, 0) == -1)
			return -1;

		uint32_t result[8];

		int ret = usbdev_recvbulk(handle->usb, result, sizeof(result));
		if(ret == -1)
			return -1;
		
		hexdump(result, ret);

		data += block;
		base += block;
		size -= block;
		value += block;

		CALLBACK(progress, PROGRESS_UPDATE, value, max);

	}

	CALLBACK(progress, PROGRESS_FINI, 0, 0);

	debug(LEVEL_DEBUG, "Load done\n");

	return 0;
}

int ingenic_load_sdram_file(void *hndl, uint32_t base, const char *file) {
	HANDLE;

	FILE *fd = fopen(file, "rb");

	if(fd == NULL) 
		return -1;

	fseek(fd, 0, SEEK_END);
	int size = ftell(fd);
	fseek(fd, 0, SEEK_SET);

	void *data = malloc(size);
	size_t bytes = fread(data, 1, size, fd);

	fclose(fd);

	if(bytes != size) {
		free(data);

		errno = EIO;

		return -1;
	}

	int ret = ingenic_load_sdram(handle, data, base, size);

	free(data);

	return ret;
}

int ingenic_go(void *hndl, uint32_t address) {
	HANDLE;

	debug(LEVEL_DEBUG, "Go to 0x%08X\n", address);
	
	return ingenic_wordop(handle->usb, VR_PROGRAM_START2, address);
}

static inline int ingenic_nandop(void *usb, uint8_t cs, uint8_t request, uint8_t param) {
	return usbdev_vendor(usb, USBDEV_TODEV, VR_NAND_OPS, (param << 12) | (cs << 4) | (request & 0x0F), 0, 0, 0);
}

int ingenic_query_nand(void *hndl, int cs, nand_info_t *info) {
	HANDLE;

	if(ingenic_nandop(handle->usb, cs, NAND_QUERY, 0) == -1)
		return -1;

	uint32_t dummy[8];

	int ret = usbdev_recvbulk(handle->usb, dummy, sizeof(dummy));

	if(ret == -1)
		return -1;

	if(ret < sizeof(nand_info_t)) {
		errno = EIO;

		return -1;
	}

	memcpy(info, dummy, sizeof(nand_info_t));

	if(usbdev_recvbulk(handle->usb, dummy, sizeof(dummy)) == -1)
		return -1;

	return 0;
}

int ingenic_dump_nand(void *hndl, int cs, int start, int pages, int type, const char *filename) {
	HANDLE;
	
	int raw = type & NAND_RAW;
	type &= ~NAND_RAW;
	
	int page_size = (handle->nand.nand_ps + (type == NO_OOB ? 0 : handle->nand.nand_os));
	int chunk_pages = STAGE2_IOBUF / page_size;
	
	FILE *dest = fopen(filename, "wb");
	
	if(dest == NULL)
		return -1;
	
	void *iobuf = malloc(chunk_pages * page_size);
	
	int ret = 0;
	int value = 0, max = pages;
	
	CALLBACK(progress, PROGRESS_INIT, 0, max);
	
	while(pages > 0) {
		int chunk = pages < chunk_pages ? pages : chunk_pages;
		int bytes = chunk * page_size;
	
		ret = ingenic_wordop(handle->usb, VR_SET_DATA_ADDRESS, start);
		
		if(ret == -1)
			break;
		
		ret = ingenic_wordop(handle->usb, VR_SET_DATA_LENGTH, chunk);
		
		if(ret == -1)
			break;
		
		ret = ingenic_nandop(handle->usb, cs, raw ? NAND_READ_RAW : NAND_READ, type);
		
		if(ret == -1)
			break;
		
		int ret = usbdev_recvbulk(handle->usb, iobuf, bytes);
	
		if(ret == -1)
			return -1;
	
		if(ret != bytes) {
			debug(LEVEL_ERROR, "Ingenic: NAND dump truncated: expected %d bytes, received %d\n", bytes, ret);
			
			errno = EIO;
		
			break;
		}
		
		uint16_t result[4];
	
		
		ret = usbdev_recvbulk(handle->usb, result, sizeof(result));
	
		if(ret == -1) 
			return -1;
		
		if(result[3] != 0 && !raw) {
			debug(LEVEL_ERROR, "Ingenic: ECC failure while reading NAND. See UART output for details\n");
					
			errno = EIO;
			
			break;
		}
			
		fwrite(iobuf, bytes, 1, dest);
		
		start += chunk;
		pages -= chunk;

		value += chunk;

		CALLBACK(progress, PROGRESS_UPDATE, value, max);
	}
	
	free(iobuf);
	fclose(dest);
	
	CALLBACK(progress, PROGRESS_FINI, 0, 0);

	return ret;
}

int ingenic_erase_nand(void *hndl, int cs, int start, int blocks) {
	HANDLE;
	
	if(ingenic_wordop(handle->usb, VR_SET_DATA_ADDRESS, start) == -1)
		return -1;
		
	if(ingenic_wordop(handle->usb, VR_SET_DATA_LENGTH, blocks) == -1)
		return -1;
			
	if(ingenic_nandop(handle->usb, cs, NAND_ERASE, 0) == -1)
		return -1;
		
	uint16_t result[4];
		
	int ret = usbdev_recvbulk(handle->usb, result, sizeof(result));
	
	if(ret == -1) 
		return -1;
	
	hexdump(result, ret);
		
	return 0;
}

int ingenic_program_nand(void *hndl, int cs, int start, int type, const char *filename) {
	HANDLE;
	
	int page_size = (handle->nand.nand_ps + (type == NO_OOB ? 0 : handle->nand.nand_os));
	int chunk_pages = STAGE2_IOBUF / page_size;	
	
	FILE *in = fopen(filename, "rb");
	
	if(in == NULL)
		return -1;
	
	fseek(in, 0, SEEK_END);
	int file_size = ftell(in);
	fseek(in, 0, SEEK_SET);
	
	int tail = file_size % page_size;

	if(tail) {
		tail = page_size - tail;

		file_size += tail;
	}

	int pages = file_size / page_size;
	int ret = 0;
	
	void *iobuf = malloc(chunk_pages * page_size);
		
	debug(LEVEL_INFO, "Programming %d pages from %d (%d bytes, %d bytes/page)\n", pages, start, file_size, page_size);
	
	int value = 0, max = pages;

	CALLBACK(progress, PROGRESS_INIT, 0, max);

	while(pages > 0) {
		int chunk = pages < chunk_pages ? pages : chunk_pages;
		int bytes = chunk * page_size;	
		
		ret = fread(iobuf, 1, bytes, in);
		
		if(pages < chunk_pages && tail) {
			memset(iobuf + ret, 0xFF, tail);

			ret += tail;
		}

		if(ret != bytes) {
			debug(LEVEL_ERROR, "fread: %d\n", ret);
			
			ret = -1;
			errno = EIO;
			
			break;
		}
		
		if(usbdev_sendbulk(handle->usb, iobuf, bytes) == -1)
			return -1;
		
		ret = ingenic_wordop(handle->usb, VR_SET_DATA_ADDRESS, start);
		
		if(ret == -1)
			break;
		
		ret = ingenic_wordop(handle->usb, VR_SET_DATA_LENGTH, chunk);
		
		if(ret == -1)
			break;
		
		ret = ingenic_nandop(handle->usb, cs, NAND_PROGRAM, type);
		
		if(ret == -1)
			break;
		
		uint16_t result[4];
		
		ret = usbdev_recvbulk(handle->usb, result, sizeof(result));
	
		if(ret == -1) 
			return -1;
		
		hexdump(result, ret);
		
		start += chunk;
		pages -= chunk;
		value += chunk;

		CALLBACK(progress, PROGRESS_UPDATE, value, max);
	}
	
	free(iobuf);
	fclose(in);

	CALLBACK(progress, PROGRESS_FINI, 0, 0);
	
	return ret;
}

int ingenic_load_nand(void *hndl, int cs, int start, int pages, uint32_t base) {
	HANDLE;
	
	if(ingenic_wordop(handle->usb, VR_PROGRAM_START1, base) == -1)
		return -1;
	
	if(ingenic_wordop(handle->usb, VR_SET_DATA_ADDRESS, start) == -1)
		return -1;
	
	if(ingenic_wordop(handle->usb, VR_SET_DATA_LENGTH, pages) == -1)
		return -1;	
	
	if(ingenic_nandop(handle->usb, cs, NAND_READ_TO_RAM, 0) == -1)
		return -1;
	
	uint16_t result[4];
		
	if(usbdev_recvbulk(handle->usb, result, sizeof(result)) == -1)
		return -1;
	
	return 0;
}

