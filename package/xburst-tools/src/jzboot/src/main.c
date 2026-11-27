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

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "usbdev.h"
#include "debug.h"
#include "devmgr.h"
#include "ingenic.h"
#include "shell.h"
#include "xburst-tools-config.h"

static void usage(const char *app) {
	printf(
		"Usage: \n"
		"  Enumeration:               %1$s -e\n"
                "  Interactive mode:          %1$s -i <INDEX>\n"
                "  Batch mode (with script):  %1$s -i <INDEX> -b <FILE>\n"
                "  Batch mode (command list): %1$s -i <INDEX> -c <COMMAND>\n\n"

		"USB loader tool for Ingenic Semiconductor XBurst-based SoC\n\n"
		" -e         Enumerate devices only\n"
		" -i <INDEX> Open device with index INDEX in interactive or batch mode\n"
		" -c <CMD>   Run semicolon-separated commands and exit\n"
                " -d <DEBUG> Set output level (0 - no reporting, 4 - max reporting), default = 1 (errors only)\n"
                " -C <FILE>  Execute configuration script FILE before anything else\n"
		" -b <FILE>  Execute script in FILE\n"
		" -v         Print program version\n\n", app);
}

static void dev_handler(int idx, uint16_t vid, uint16_t pid, void *data) {
	printf("  Device %d: %04hX:%04hX\n", idx, vid, pid);
}

int main(int argc, char *argv[]) {
	int ch;
	int idx = -1, enumerate = 0;
	char *cmd = NULL, *script = NULL, *config = NULL;

	while((ch = getopt(argc, argv, "b:i:ec:d:C:v")) != -1) {
		switch(ch) {
		case 'e':
			enumerate = 1;

			break;

		case 'i':
			idx = atoi(optarg);

			break;

		case 'c':
			cmd = optarg;

			break;

		case 'b':
			script = optarg;

			break;

		case 'C':
			config = optarg;

			break;

		case 'd':
			set_debug_level(atoi(optarg));

			break;

		case 'v':
			printf("JZboot version %s\n", PACKAGE_VERSION);

			return 0;

		default:
			usage(argv[0]);

			return 1;
		}
	}

	if(!enumerate && idx < 0) {
		usage(argv[0]);

		return 1;
	}

	if(usbdev_init() == -1) {
		perror("usbdev_init");

		return 1;
	}

	atexit(usbdev_fini);

	if(usbdev_enumerate() == -1) {
		perror("usbdev_enumerate");

		return 1;
	}

	if(enumerate) {
		printf("Ingenic devices list:\n");

		enum_devices(dev_handler);

		return 0;
	}

	void *data = get_device(idx);

	if(data == NULL) {
		fprintf(stderr, "Device with index %d not found\n", idx);

		return 1;
	}

	void *hndl = usbdev_open(data);

	if(hndl == NULL) {
		perror("usbdev_open");

		return 1;
	}

	int ret = 0;

	void *ingenic = ingenic_open(hndl);

	if(ingenic == NULL) {
		perror("ingenic_open");

		ret = 1;

		goto exit_usb;
	}

	shell_context_t *shell = shell_init(ingenic);

	if(shell == NULL) {
		perror("shell_init");

		ret = 1;

		goto exit_ingenic;
	}

	if(config) {
		if(shell_source(shell, config) == -1) {
			perror("shell_source");

			ret = 1;

			goto exit_shell;
		}
	}

	if(cmd != NULL) {
		if(shell_execute(shell, cmd) == -1) {
			perror("shell_execute");

			ret = 1;
		}

	} else if(script != NULL) {
		if(shell_source(shell, script) == -1) {
			perror("shell_source");

			ret = 1;
		}
	} else
		shell_interactive(shell);

exit_shell:
	shell_fini(shell);

exit_ingenic:
	ingenic_close(ingenic);

exit_usb:
	usbdev_close(hndl);

	return ret;
}
