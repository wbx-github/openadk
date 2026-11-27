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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "shell.h"
#include "app_config.h"
#include "ingenic.h"

static int builtin_help(shell_context_t *ctx, int argc, char *argv[]);
static int builtin_exit(shell_context_t *ctx, int argc, char *argv[]);
static int builtin_source(shell_context_t *ctx, int argc, char *argv[]);
static int builtin_echo(shell_context_t *ctx, int argc, char *argv[]);
static int builtin_sleep(shell_context_t *ctx, int argc, char *argv[]);
static int builtin_redetect(shell_context_t *ctx, int argc, char *argv[]);
static int builtin_rebuildcfg(shell_context_t *ctx, int argc, char *argv[]);
static int builtin_set(shell_context_t *ctx, int argc, char *argv[]);
static int builtin_safe(shell_context_t *ctx, int argc, char *argv[]);

const shell_command_t builtin_cmdset[] = {
	{ "help", "Display this message", builtin_help, NULL },
	{ "exit", "Batch: stop current script, interactive: end session", builtin_exit, NULL },
	{ "source", "Run specified script", builtin_source, "<FILENAME>" },
	{ "echo", "Output specified string", builtin_echo,  "<STRING> ..." },
	{ "sleep", "Sleep a specified amount of time", builtin_sleep, "<MILLISECONDS>" },
	{ "set", "Print or set configuraton variables", builtin_set, "[VARIABLE] [VALUE]" },
	{ "safe", "Run command ignoring errors", builtin_safe, "<COMMAND> [ARG] ..." },

	{ "redetect", "Redetect CPU", builtin_redetect, NULL },
	{ "rebuildcfg", "Rebuild firmware configuration data", builtin_rebuildcfg, NULL },

	{ NULL, NULL, NULL }
};

static int help_maxwidth_function(shell_context_t *ctx, const shell_command_t *cmd, void *arg) {
	int len = strlen(cmd->cmd), *maxlen = arg;

	if(cmd->args)
		len += strlen(cmd->args) + 1;

	if(len > *maxlen)
		*maxlen = len;		

	return 0;
}

static int help_print_function(shell_context_t *ctx, const shell_command_t *cmd, void *arg) {
	int len = strlen(cmd->cmd), *maxlen = arg;

	fputs(cmd->cmd, stdout);

	if(cmd->args) {
		len += strlen(cmd->args) + 1;

		putchar(' ');
		fputs(cmd->args, stdout);
	}

	for(int i = 0; i < *maxlen - len; i++)
		putchar(' ');

	puts(cmd->description);

	return 0;
}

static int builtin_help(shell_context_t *ctx, int argc, char *argv[]) {
	int maxwidth = 0;

	shell_enumerate_commands(ctx, help_maxwidth_function, &maxwidth);

	maxwidth += 2;

	return shell_enumerate_commands(ctx, help_print_function, &maxwidth);
}

static int builtin_exit(shell_context_t *ctx, int argc, char *argv[]) {
	shell_exit(ctx, 1);

	return 0;
}

static int builtin_source(shell_context_t *ctx, int argc, char *argv[]) {
	int ret = shell_source(ctx, argv[1]);

	if(ret == -1) {
		fprintf(stderr, "Error while sourcing file %s: %s\n", argv[1], strerror(errno));
	}

	shell_exit(ctx, 0);

	return ret;
}

static int builtin_echo(shell_context_t *ctx, int argc, char *argv[]) {
	for(int i = 1; i < argc; i++) {
		fputs(argv[i], stdout);

		putchar((i < argc - 1) ? ' ' : '\n');
	}

	return 0;
}

static int builtin_sleep(shell_context_t *ctx, int argc, char *argv[]) {
	uint32_t ms = atoi(argv[1]);

	usleep(ms * 1000);

	return 0;
}

static int builtin_redetect(shell_context_t *ctx, int argc, char *argv[]) {
	if(ingenic_redetect(shell_device(ctx)) == -1) {
		perror("ingenic_redetect");

		return -1;
	} else
		return 0;
}


static int builtin_set(shell_context_t *ctx, int argc, char *argv[]) {
	if(argc == 1) {
		if(cfg_environ) {
			for(int i = 0; cfg_environ[i] != NULL; i++)
				printf("%s\n", cfg_environ[i]);
		}

	} else if(argc == 2) {
		cfg_unsetenv(argv[1]);

	} else if(argc == 3) {
		cfg_setenv(argv[1], argv[2]);
	}

	return 0;
}


static int builtin_rebuildcfg(shell_context_t *ctx, int argc, char *argv[]) {
	return ingenic_rebuild(shell_device(ctx));
}

static int builtin_safe(shell_context_t *ctx, int argc, char *argv[]) {
	if(shell_run(ctx, argc - 1, argv + 1) == -1)
		perror("shell_run");

	return 0;
}

