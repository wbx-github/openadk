/*
 * JzBoot: an USB bootloader for JZ series of Ingenic(R) microprocessors.
 * Copyright (C) 2010  Peter Zotov <whitequark@whitequark.org>
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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "shell.h"
#include "app_config.h"
#include "ingenic.h"
#include "elfldr.h"

static int usbboot_boot(shell_context_t *ctx, int argc, char *argv[]);
static int usbboot_load(shell_context_t *ctx, int argc, char *argv[]);
static int usbboot_go(shell_context_t *ctx, int argc, char *argv[]);
static int usbboot_load_kernel(shell_context_t *ctx, int argc, char *argv[]);
static int usbboot_nquery(shell_context_t *ctx, int argc, char *argv[]);
static int usbboot_ndump(shell_context_t *ctx, int argc, char *argv[]);
static int usbboot_nerase(shell_context_t *ctx, int argc, char *argv[]);
static int usbboot_nprogram(shell_context_t *ctx, int argc, char *argv[]);
static int usbboot_nload(shell_context_t *ctx, int argc, char *argv[]);

const shell_command_t usbboot_cmdset[] = {

	{ "boot", "Reconfigure stage2", usbboot_boot, NULL },
	{ "load", "Load file to SDRAM", usbboot_load, "<FILE> <BASE>" },
	{ "go", "Jump to <ADDRESS>", usbboot_go, "<ADDRESS>" },
	{ "load_kernel", "Load ELF kernel and initrd to memory", usbboot_load_kernel, "<KERNEL> <CMDLINE> [INITRAMFS]" },

	{ "nquery", "Query NAND information", usbboot_nquery, "<DEVICE>" },
	{ "ndump", "Dump NAND to file", usbboot_ndump, "<DEVICE> <STARTPAGE> <PAGES> <FILE>" },
	{ "ndump_oob", "Dump NAND with OOB to file", usbboot_ndump, "<DEVICE> <STARTPAGE> <PAGES> <FILE>" },
	{ "nerase", "Erase NAND blocks", usbboot_nerase, "<DEVICE> <STARTBLOCK> <BLOCKS>" },
	{ "nprogram", "Program NAND from file", usbboot_nprogram, "<DEVICE> <STARTPAGE> <FILE>" },
	{ "nprogram_oob", "Program NAND with OOB from file", usbboot_nprogram, "<DEVICE> <STARTPAGE> <FILE>" },
	{ "nload", "Load NAND data to SDRAM", usbboot_nload, "<DEVICE> <STARTPAGE> <PAGES> <BASE>" },
	
	{ NULL, NULL, NULL, NULL }
};

static int usbboot_boot(shell_context_t *ctx, int argc, char *argv[]) {
	int ret = ingenic_configure_stage2(shell_device(ctx));

	if(ret == -1)
		perror("ingenic_configure_stage2");

	return ret;
}

static int usbboot_load(shell_context_t *ctx, int argc, char *argv[]) {
	int ret = ingenic_load_sdram_file(shell_device(ctx), strtoul(argv[2], NULL, 0), argv[1]);

	if(ret == -1)
		perror("ingenic_load_sdram_file");

	return ret;
}

static int usbboot_go(shell_context_t *ctx, int argc, char *argv[]) {
	int ret = ingenic_go(shell_device(ctx), strtoul(argv[1], NULL, 0));

	if(ret == -1)
		perror("ingenic_go");

	return ret;
}

static int usbboot_nquery(shell_context_t *ctx, int argc, char *argv[]) {
	nand_info_t info;

	int ret = ingenic_query_nand(shell_device(ctx), atoi(argv[1]), &info);

	if(ret == -1) {
		perror("ingenic_query_nand");

		return -1;
	}

	printf(
		"VID:   %02hhX\n"
		"PID:   %02hhX\n"
		"Chip:  %02hhX\n"
		"Page:  %02hhX\n"
		"Plane: %02hhX\n",
		info.vid, info.pid, info.chip, info.page, info.plane);


	return 0;
}

static int usbboot_ndump(shell_context_t *ctx, int argc, char *argv[]) {
	int type = strcmp(argv[0], "ndump_oob") ? NO_OOB : OOB_ECC;
	
	if(cfg_getenv("NAND_RAW"))
		type |= NAND_RAW;
	
	int ret = ingenic_dump_nand(shell_device(ctx), atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), type, argv[4]);
	
	if(ret == -1)
		perror("ingenic_dump_nand");
	
	return ret;
}

static int usbboot_nerase(shell_context_t *ctx, int argc, char *argv[]) {
	int ret = ingenic_erase_nand(shell_device(ctx), atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	
	if(ret == -1)
		perror("ingenic_erase_nand");
	
	return ret;
	
}

static int usbboot_nprogram(shell_context_t *ctx, int argc, char *argv[]) {
	int type = strcmp(argv[0], "nprogram_oob") ? NO_OOB : OOB_ECC;
	
	if(strcmp(argv[0], "nprogram_oob") == 0) {
		if(cfg_getenv("NAND_RAW"))
			type = OOB_ECC;
		else
			type = OOB_NO_ECC;
	} else 
		type = NO_OOB;
	
	int ret = ingenic_program_nand(shell_device(ctx), atoi(argv[1]), atoi(argv[2]), type, argv[3]);
	
	if(ret == -1)
		perror("ingenic_program_nand");
	
	return ret;
}

static int usbboot_nload(shell_context_t *ctx, int argc, char *argv[]) {
	int ret = ingenic_load_nand(shell_device(ctx), atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), strtoul(argv[4], NULL, 0));
	
	if(ret == -1)
		perror("ingenic_load_nand");
	
	return ret;
}

static int usbboot_load_kernel(shell_context_t *ctx, int argc, char *argv[]) {
	return load_elf(shell_device(ctx), argv[1], argv[2],
	                argc == 4 ? argv[3] : NULL);
}

