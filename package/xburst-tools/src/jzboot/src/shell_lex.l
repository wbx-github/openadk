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

%{
#include "shell_internal.h"
#include <string.h>
#include <stdlib.h>

static char *str_append(char *str, const char *src) {
	if(str) {
		size_t newlen = strlen(str) + strlen(src) + 1;

		char *newstr = malloc(newlen);

		strcpy(newstr, str);
		strcat(newstr, src);

		free(str);

		return newstr;
	} else
		return strdup(src);
}
%}
%option noyywrap nounput noinput batch reentrant

%x STR
%%
["]		{ yyextra->strval = NULL; BEGIN(STR); }
;		return TOK_SEPARATOR;
[[:space:]]+	return TOK_SPACE;
[#]	return TOK_COMMENT;
[^[:space:];"#]+	{ yyextra->strval = strdup(yytext); return TOK_STRING; }
<STR>[^\\"]+	yyextra->strval = str_append(yyextra->strval, yytext);
<STR>\\["]	yyextra->strval = str_append(yyextra->strval, "\"");
<STR>\\		yyextra->strval = str_append(yyextra->strval, "\\");
<STR>["]	{ BEGIN(INITIAL); return TOK_STRING; }
