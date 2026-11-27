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

#ifndef __SHELL__H__
#define __SHELL__H__

#ifndef SHELL_INTERNALS
typedef void shell_context_t;
#endif

typedef struct shell_command {
	const char *cmd;
	const char *description;
	int (*handler)(shell_context_t *ctx, int argc, char *argv[]);
	const char *args;
} shell_command_t;

shell_context_t *shell_init(void *ingenic);
void shell_fini(shell_context_t *context);

void shell_interactive(shell_context_t *ctx);
int shell_source(shell_context_t *ctx, const char *filename);
int shell_execute(shell_context_t *ctx, const char *input);
void *shell_device(shell_context_t *ctx);
int shell_run(shell_context_t *ctx, int argc, char *argv[]);

void shell_exit(shell_context_t *ctx, int val);
int shell_enumerate_commands(shell_context_t *ctx, int (*callback)(shell_context_t *ctx, const shell_command_t *cmd, void *arg), void *arg);

extern const shell_command_t spl_cmdset[];
extern const shell_command_t usbboot_cmdset[];
extern const shell_command_t builtin_cmdset[];

#endif
