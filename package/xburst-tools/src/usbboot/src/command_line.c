/*
 * Copyright(C) 2009  Qi Hardware Inc.,
 * Authors: Xiangfu Liu <xiangfu@sharism.cc>
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
#include <stdlib.h>
#include <string.h>
#include "usb_boot_defines.h"
#include "ingenic_usb.h"
#include "command_line.h"
#include "cmd.h"
 
static int handle_help(void)
{
	printf(
		" boot       boot device and make it in stage2\n"
		" reset      reset device\n"
		" nquery     query NAND flash info\n"
		" nprog      program NAND flash\n"
		" nerase     erase NAND flash\n"
		" nmark      mark a bad block in NAND flash\n"
		" nread      read NAND flash data with checking bad block and ECC\n"
		" nreadraw   read NAND flash data without checking bad block and ECC\n"
		" nreadoob   read NAND flash oob\n"
		" gpios      set one GPIO to high level\n"
		" gpioc      set one GPIO to low level\n"
		" load       load file data to SDRAM\n"
		" go         execute program in SDRAM\n"
		" memtest    memory test\n"
		" help       print this help\n"
		" exit\n");

	return 0;
}

/* need transfer two para :blk_num ,start_blk */
int handle_nerase(void)
{
	if (com_argc < 5) {
		printf(" Usage: nerase (1) (2) (3) (4)\n"
		       " 1:start block number\n"
		       " 2:block length\n"
		       " 3:device index number\n"
		       " 4:flash chip index number\n");
		return -1;
	}

	init_nand_in();

	nand_in.start = atoi(com_argv[1]);
	nand_in.length = atoi(com_argv[2]);
	nand_in.dev = atoi(com_argv[3]);
	if (atoi(com_argv[4]) >= MAX_DEV_NUM) {
		printf(" Flash index number overflow!\n");
		return -1;
	}
	(nand_in.cs_map)[atoi(com_argv[4])] = 1;

	if (nand_erase(&nand_in) < 1)
		return -1;

	return 0;
}

int handle_nmark(void)
{
	if (com_argc < 4) {
		printf(" Usage: nerase (1) (2) (3)\n"
		       " 1:bad block number\n"
		       " 2:device index number\n"
		       " 3:flash chip index number\n");
		return -1;
	}

	init_nand_in();

	nand_in.start = atoi(com_argv[1]);
	nand_in.dev = atoi(com_argv[2]);

	if (atoi(com_argv[3]) >= MAX_DEV_NUM) {
		printf(" Flash index number overflow!\n");
		return -1;
	}
	(nand_in.cs_map)[atoi(com_argv[3])] = 1;

	nand_markbad(&nand_in);
	return 0;
}

int handle_memtest(void)
{
	unsigned int start, size;
	if (com_argc != 2 && com_argc != 4) {
		printf(" Usage: memtest (1) [2] [3]\n"
		       " 1:device index number\n"
		       " 2:SDRAM start address\n"
		       " 3:test size\n");
		return -1;
	}

	if (com_argc == 4) {
		start = strtoul(com_argv[2], NULL, 0);
		size = strtoul(com_argv[3], NULL, 0);
	} else {
		start = 0;
		size = 0;
	}

	debug_memory(start, size);
	return 0;
}

int handle_gpio(int mode)
{
	if (com_argc < 3) {
		printf(" Usage:"
		       " gpios (1) (2)\n"
		       " 1:GPIO pin number\n"
		       " 2:device index number\n");
		return -1;
	}

	debug_gpio(mode, atoi(com_argv[1]));
	return 0;
}

int handle_load(void)
{
	if (com_argc < 4) {
		printf(" Usage:"
		       " load (1) (2) (3) \n"
		       " 1:SDRAM start address\n"
		       " 2:image file name\n"
		       " 3:device index number\n");

		return -1;
	}

	sdram_in.start=strtoul(com_argv[1], NULL, 0);
	sdram_in.dev = atoi(com_argv[3]);
	sdram_in.buf = code_buf;

	sdram_load_file(&sdram_in, com_argv[2]);
	return 0;
}

int command_handle(char *buf)
{
	char *p = strtok(buf, "\n ");
	if(p == NULL)
		return 0;

	com_argc = 0;
	strcpy(com_argv[com_argc++], p);

	while ((p = strtok(NULL, "\n ")) != NULL)
		strcpy(com_argv[com_argc++], p);

	if (!strcmp("boot", com_argv[0]))
		boot(stage1, stage2);
	else if (!strcmp("nprog", com_argv[0]))
		nand_prog();
	else if (!strcmp("nquery", com_argv[0]))
		nand_query();
	else if (!strcmp("nerase", com_argv[0]))
		handle_nerase();
	else if (!strcmp("nmark", com_argv[0]))
		handle_nmark();
	else if (!strcmp("nread", com_argv[0]))
		nand_read(NAND_READ);
	else if (!strcmp("nreadraw", com_argv[0]))
		nand_read(NAND_READ_RAW);
	else if (!strcmp("nreadoob", com_argv[0]))
		nand_read(NAND_READ_OOB);
	else if (!strcmp("gpios", com_argv[0]))
		handle_gpio(2);
	else if (!strcmp("gpioc", com_argv[0]))
		handle_gpio(3);
	else if (!strcmp("load", com_argv[0]))
		handle_load();
	else if (!strcmp("go", com_argv[0]))
		debug_go();
	else if (!strcmp("memtest", com_argv[0]))
		handle_memtest();
	else if (!strcmp("reset", com_argv[0]))
		device_reset(0);
	else if (!strcmp("help", com_argv[0]))
		handle_help();
	else if (!strcmp("exit", com_argv[0]))
		return -1;
	else
		printf(" type `help` show all commands\n");

	return 0;
}
