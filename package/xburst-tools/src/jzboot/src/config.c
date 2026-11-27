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

#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "app_config.h"
#include "debug.h"

char **cfg_environ = NULL;

static int env_size() {
	int size = 0;

	if(cfg_environ == NULL)
		return 0;

	for(int i = 0; cfg_environ[i] != NULL; i++)
		size++;

	return size;
}

char *cfg_getenv(const char *variable) {
	if(cfg_environ == NULL)
		return NULL;

	size_t len = strlen(variable);

	for(int i = 0; cfg_environ[i] != NULL; i++) {
		char *str = cfg_environ[i], *sep = strchr(str, '=');

		if(sep - str == len && memcmp(str, variable, len) == 0) {
			return sep + 1;
		}
	}

	return NULL;
}

void cfg_unsetenv(const char *variable) {
	int size = env_size();

	if(size == 0)
		return;

	size_t len = strlen(variable);

	for(int i = 0; cfg_environ[i] != NULL; i++) {
		char *str = cfg_environ[i], *sep = strchr(str, '=');

		if(sep - str == len && memcmp(str, variable, len) == 0) {
			free(str);

			memcpy(cfg_environ + i, cfg_environ + i + 1, sizeof(char *) * (size - i));

			cfg_environ = realloc(cfg_environ, sizeof(char *) * size);

			return;
		}
	}
}

void cfg_setenv(const char *variable, const char *newval) {
	int size = env_size();

	size_t len = strlen(variable);

	char *newstr = malloc(len + 1 + strlen(newval) + 1);

	strcpy(newstr, variable);
	strcat(newstr, "=");
	strcat(newstr, newval);

	if(size > 0) {
		for(int i = 0; cfg_environ[i] != NULL; i++) {
			char *str = cfg_environ[i], *sep = strchr(str, '=');

			if(sep - str == len && memcmp(str, variable, len) == 0) {
				free(str);

				cfg_environ[i] = newstr;

				return;
			}
		}
	}

	cfg_environ = realloc(cfg_environ, sizeof(char *) * (size + 2));

	cfg_environ[size] = newstr;
	cfg_environ[size + 1] = NULL;
}
