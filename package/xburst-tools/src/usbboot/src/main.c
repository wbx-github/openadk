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
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include "xburst-tools-config.h"
#include "command_line.h"
#include "ingenic_usb.h"
#include "ingenic_cfg.h"

#define CONFIG_FILE_PATH (CFGDIR "usbboot.cfg")
#define STAGE1_FILE_PATH (DATADIR "xburst_stage1.bin")
#define STAGE2_FILE_PATH (DATADIR "xburst_stage2.bin")

extern struct ingenic_dev ingenic_dev;
extern struct hand hand;
extern char * stage1;
extern char * stage2;

static void help(void)
{
	printf("Usage: usbboot [options] ...\n"
	       "  -h --help\t\t\tPrint this help message\n"
	       "  -v --version\t\t\tPrint the version number\n"
	       "  -c --command\t\t\tDirect run the commands, split by ';'\n"
	       "              \t\t\tNOTICE: the max commands count is 10!\n"
	       "  -f --configure\t\tconfigure file path\n"
	       "  -1 --stage1\t\t\tstage1 file path\n"
	       "  -2 --stage2\t\t\tstage2 file path\n"
	       "  <run without options to enter commands via usbboot prompt>\n\n"
	       "Report bugs to xiangfu@sharism.cc.\n"
		);
}

static void print_version(void)
{
	printf("usbboot %s\n", PACKAGE_VERSION);
}

static struct option opts[] = {
	{ "help", 0, 0, 'h' },
	{ "version", 0, 0, 'v' },
	{ "command", 1, 0, 'c' },
	{ "configure", 1, 0, 'f' },
	{ "stage1", 1, 0, '1' },
	{ "stage2", 1, 0, '2' },
	{ 0, 0, 0, 0 }
};

int main(int argc, char **argv)
{
	char *cptr;
	char *cmdpt;
	int command = 0;
	char cmd_buf[512] = {0};
	char *cfgpath = CONFIG_FILE_PATH;

	stage1 = STAGE1_FILE_PATH;
	stage2 = STAGE2_FILE_PATH;

	while(1) {
		int c, option_index = 0;
		c = getopt_long(argc, argv, "hvc:f:1:2:", opts,
				&option_index);
		if (c == -1)
			break;

		switch (c) {
		case 'h':
			help();
			exit(EXIT_SUCCESS);
		case 'v':
			print_version();
			exit(EXIT_SUCCESS);
		case 'c':
			command = 1;
			cmdpt = optarg;
			break;
		case 'f':
			cfgpath = optarg;
			break;
		case '1':
			stage1 = optarg;
			break;
		case '2':
			stage2 = optarg;
			break;
		default:
			help();
			exit(2);
		}
	}

	printf("\nusbboot version %s - Ingenic XBurst USB Boot Utility\n"
	       "(c) 2009 Ingenic Semiconductor Inc., Qi Hardware Inc., Xiangfu Liu, Marek Lindner\n"
	       "This program is Free Software and comes with ABSOLUTELY NO WARRANTY.\n\n", PACKAGE_VERSION);

	if (usb_ingenic_init(&ingenic_dev) < 1)
	 	return EXIT_FAILURE;

	if (parse_configure(&hand, cfgpath) < 1)
		return EXIT_FAILURE;

#define MAX_COMMANDS	10
	if (command) {		/* direct run command */
		char *sub_cmd[MAX_COMMANDS];
		int i, loop = 0;

		sub_cmd[loop++] = strtok(cmdpt, ";");
		while ((sub_cmd[loop++] = strtok(NULL, ";")) != NULL)
			if (loop >= MAX_COMMANDS) {
				printf(" -c only support 10 commands\n");
				break;
			}

		for (i = 0; i < loop - 1; i++) {
			printf(" Execute command: %s \n", sub_cmd[i]);
			command_handle(sub_cmd[i]);
		}
		goto out;
	}

	while (1) {
		printf("usbboot# ");
		cptr = fgets(cmd_buf, sizeof(cmd_buf), stdin);
		if (cptr != NULL)
			if (command_handle(cmd_buf))
				break;
	}

out:
	usb_ingenic_cleanup(&ingenic_dev);

	return EXIT_SUCCESS;
}
