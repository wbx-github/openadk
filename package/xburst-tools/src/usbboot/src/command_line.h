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

#ifndef __COMMAND_LINE_H__
#define __COMMAND_LINE_H__

#define MAX_ARGC	10
#define MAX_COMMAND_LENGTH	100

int com_argc;
char com_argv[MAX_ARGC][MAX_COMMAND_LENGTH];
char *stage1;
char *stage2;

int command_handle(char *buf);

#endif	/* __COMMAND_LINE_H__ */
