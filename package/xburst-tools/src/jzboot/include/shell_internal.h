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

#ifndef __SHELL_INTERNAL__H__
#define __SHELL_INTERNAL__H__

#define SHELL_INTERNALS
#define STATE_WANTSTR	0
#define STATE_WANTSPACE	1

#define TOK_SEPARATOR	1
#define TOK_STRING	2
#define TOK_SPACE	3
#define TOK_COMMENT	4

typedef struct {
	void *device;
	char linebuf[512];
	char *strval;
	char *line;
	const struct shell_command *set_cmds;
	int shell_exit;
	int prev_progress;
} shell_context_t;


typedef struct {
	int argc;
	char **argv;
} shell_run_data_t;

int shell_pull(shell_context_t *ctx, char *buf, int maxlen);

#ifndef FLEX_SCANNER
typedef void *yyscan_t;
int yylex_init(yyscan_t *ptr_yy_globals);
int yylex_init_extra(shell_context_t *user_defined, yyscan_t *ptr_yy_globals);
int yylex(yyscan_t yyscanner) ;
int yylex_destroy (yyscan_t yyscanner) ;
#else
#define YY_EXTRA_TYPE shell_context_t *
#define YY_INPUT(buf, result, max_size) result = shell_pull(yyextra, buf, max_size);
#endif

#include "shell.h"

#endif

