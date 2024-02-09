/*
 * depmaker - create package/Depends.mk for OpenADK buildsystem
 *
 * Copyright (C) 2010-2015 Waldemar Brodkorb <wbx@openadk.org>
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

#define _GNU_SOURCE
#include <ctype.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

#define MAXLINE 1024
#define MAXPATH 128

static int prefix = 0;
static int hprefix = 0;

static int check_symbol(char *symbol) {

	FILE *config;
	char buf[MAXLINE];
	char *sym;
	int ret;

	if ((sym = malloc(strlen(symbol) + 2)) != NULL)
		memset(sym, 0, strlen(symbol) + 2);
	else {
		perror("Can not allocate memory.");
		exit(EXIT_FAILURE);
	}

	strncat(sym, symbol, strlen(symbol));
	strncat(sym, "=", 1);
	if ((config = fopen(".config", "r")) == NULL) {
		perror("Can not open file \".config\".");
		exit(EXIT_FAILURE);
	}

	ret = 1;
	while (fgets(buf, MAXLINE, config) != NULL) {
		if (strncmp(buf, sym, strlen(sym)) == 0)
			ret = 0;
	}

	free(sym);
	if (fclose(config) != 0)
		perror("Closing file stream failed");

	return(ret);
}

/*@null@*/
static char *parse_line(char *package, char *pkgvar, char *string, int checksym, int pprefix, int system, int *prefixp) {

	char *key, *value, *dep, *key_sym, *pkgdeps, *depvar;
	char temp[MAXLINE];
	int i;

	string[strlen(string)-1] = '\0';
	if ((key = strtok(string, ":=")) == NULL) {
		perror("Can not get key from string.");
		exit(EXIT_FAILURE);
	}

	if (checksym == 1) {
		/* extract symbol */
		if ((key_sym = malloc(MAXLINE)) != NULL)
			memset(key_sym, 0, MAXLINE);
		else {
			perror("Can not allocate memory.");
			exit(EXIT_FAILURE);
		}
		switch(system) {
			case 0:
				if (pprefix == 0) {
					if (snprintf(key_sym, MAXLINE, "ADK_PACKAGE_%s_", pkgvar) < 0)
						perror("Can not create string variable.");
				} else {
					if (snprintf(key_sym, MAXLINE, "ADK_PACKAGE_") < 0)
						perror("Can not create string variable.");
				}
				strncat(key_sym, key+6, strlen(key)-6);
				break;
			case 1:
				if (snprintf(key_sym, MAXLINE, "ADK_TARGET_SYSTEM_%s", pkgvar) < 0)
					perror("Can not create string variable.");
				break;
			case 2:
				if (snprintf(key_sym, MAXLINE, "ADK_TARGET_LIB_%s", pkgvar) < 0)
					perror("Can not create string variable.");
				break;
		}
		if (check_symbol(key_sym) != 0) {
			free(key_sym);
			return(NULL);
		}
		free(key_sym);
	}

	if ((pkgdeps = malloc(MAXLINE)) != NULL)
		memset(pkgdeps, 0, MAXLINE);
	else {
		perror("Can not allocate memory.");
		exit(EXIT_FAILURE);
	}

	value = strtok(NULL, "=\t");
	dep = strtok(value, " ");
	while (dep != NULL) {
		/* check only for optional host tools, if they are required to build */
		if (checksym == 2) {
			if ((depvar = malloc(MAXLINE)) != NULL)
				memset(depvar, 0, MAXLINE);
			else {
				perror("Can not allocate memory.");
				exit(EXIT_FAILURE);
			}
			strncat(depvar, dep, strlen(dep)-5);
			if ((strncmp(depvar, "bc", 2) == 0) ||
				(strncmp(depvar, "file", 4) == 0) ||
				(strncmp(depvar, "gawk", 4) == 0) ||
				(strncmp(depvar, "grep", 4) == 0) ||
				(strncmp(depvar, "sed", 3) == 0) ||
				(strncmp(depvar, "xz", 2) == 0)) {

				/* transform to uppercase variable name */
				for (i=0; i<(int)strlen(depvar); i++) {
					if (depvar[i] == '+')
						depvar[i] = 'X';
					if (depvar[i] == '-')
						depvar[i] = '_';
					depvar[i] = toupper(depvar[i]);
				}

				/* extract symbol */
				if ((key_sym = malloc(MAXLINE)) != NULL)
					memset(key_sym, 0, MAXLINE);
				else {
					perror("Can not allocate memory.");
					exit(EXIT_FAILURE);
				}
				if (snprintf(key_sym, MAXLINE, "ADK_HOST_BUILD_%s", depvar) < 0)
						perror("Can not create string variable.");

				if (check_symbol(key_sym) != 0) {
					free(key_sym);
					free(depvar);
					return(NULL);
				}
				free(key_sym);
				free(depvar);
			}
		}
		if (*prefixp == 0) {
			*prefixp = 1;
			if (snprintf(temp, MAXLINE, "%s-compile: %s-compile", package, dep) < 0)
				perror("Can not create string variable.");
		} else {
			if (snprintf(temp, MAXLINE, " %s-compile", dep) < 0)
				perror("Can not create string variable.");
		}
		strncat(pkgdeps, temp, strlen(temp));
		dep = strtok(NULL, " ");
	}
	return(pkgdeps);
}

int main() {

	DIR *pkgdir;
	struct dirent *pkgdirp;
	FILE *pkg;
	char buf[MAXLINE];
	char path[MAXPATH];
	char *string, *pkgvar, *pkgdeps, *hpkgdeps = NULL, *tmp, *fpkg, *cpkg, *spkg, *key, *check, *dpkg;
	char *stringtmp;
	int i;

	spkg = NULL;
	cpkg = NULL;
	fpkg = NULL;
	
	/* read Makefile's for all packages */
	pkgdir = opendir("package");
	while ((pkgdirp = readdir(pkgdir)) != NULL) {
		/* skip dotfiles */
		if (strncmp(pkgdirp->d_name, ".", 1) > 0) {
			if (snprintf(path, MAXPATH, "package/%s/Makefile", pkgdirp->d_name) < 0)
				perror("Can not create string variable.");
			pkg = fopen(path, "r");
			if (pkg == NULL)
				continue;
			
			/* transform to uppercase variable name */
			pkgvar = strdup(pkgdirp->d_name);
			for (i=0; i<(int)strlen(pkgvar); i++) {
				if (pkgvar[i] == '+')
					pkgvar[i] = 'X';
				if (pkgvar[i] == '-')
					pkgvar[i] = '_';
				pkgvar[i] = toupper(pkgvar[i]);
			}
			
			/* exclude manual maintained packages from package/Makefile */
			if (
				!(strncmp(pkgdirp->d_name, "uclibc-ng", 9) == 0 && strlen(pkgdirp->d_name) == 9) &&
				!(strncmp(pkgdirp->d_name, "musl", 4) == 0) &&
				!(strncmp(pkgdirp->d_name, "glibc", 5) == 0)) {
				/* print result to stdout */
				printf("package-$(ADK_COMPILE_%s) += %s\n", pkgvar, pkgdirp->d_name); 
				printf("hostpackage-$(ADK_HOST_BUILD_%s) += %s\n", pkgvar, pkgdirp->d_name); 
			}

			if ((pkgdeps = malloc(MAXLINE)) != NULL)
				memset(pkgdeps, 0, MAXLINE);
			else {
				perror("Can not allocate memory.");
				exit(EXIT_FAILURE);
			}
			prefix = 0;
			hprefix = 0;

			/* generate build dependencies */
			while (fgets(buf, MAXLINE, pkg) != NULL) {
				if ((tmp = malloc(MAXLINE)) != NULL)
					memset(tmp, 0 , MAXLINE);
				else {
					perror("Can not allocate memory.");
					exit(EXIT_FAILURE);
				}

				/* just read variables prefixed with PKG */
				if (strncmp(buf, "PKG", 3) == 0) {

					string = strstr(buf, "PKG_BUILDDEP:=");
					if (string != NULL) {
						tmp = parse_line(pkgdirp->d_name, pkgvar, string, 0, 0, 0, &prefix);
						if (tmp != NULL) {
							strncat(pkgdeps, tmp, strlen(tmp));
						}
					}

					string = strstr(buf, "PKG_BUILDDEP+=");
					if (string != NULL) {
						tmp = parse_line(pkgdirp->d_name, pkgvar, string, 0, 0, 0, &prefix);
						if (tmp != NULL)
							strncat(pkgdeps, tmp, strlen(tmp));
					}

					// We need to find the system or libc name here
					string = strstr(buf, "PKG_BUILDDEP_");
					if (string != NULL) {
						check = strstr(buf, ":=");
						if (check != NULL) {
							stringtmp = strdup(string);
							string[strlen(string)-1] = '\0';
							key = strtok(string, ":=");
							dpkg = strdup(key+13);
							if (strncmp("UCLIBC_NG", dpkg, 9) == 0) {
								tmp = parse_line(pkgdirp->d_name, dpkg, stringtmp, 1, 0, 2, &prefix);
							} else if (strncmp("MUSL", dpkg, 4) == 0) {
								tmp = parse_line(pkgdirp->d_name, dpkg, stringtmp, 1, 0, 2, &prefix);
							} else if (strncmp("GLIBC", dpkg, 5) == 0) {
								tmp = parse_line(pkgdirp->d_name, dpkg, stringtmp, 1, 0, 2, &prefix);
							} else {
								tmp = parse_line(pkgdirp->d_name, dpkg, stringtmp, 1, 0, 1, &prefix);
							}
							if (tmp != NULL)
								strncat(pkgdeps, tmp, strlen(tmp));
						}
					}

					// We need to find the subpackage name here
					string = strstr(buf, "PKG_FLAVOURS_");
					if (string != NULL) {
						check = strstr(buf, ":=");
						if (check != NULL) {
							string[strlen(string)-1] = '\0';
							key = strtok(string, ":=");
							fpkg = strdup(key+13);
						}
					}

					string = strstr(buf, "PKGFB_");
					if (string != NULL) {
						tmp = parse_line(pkgdirp->d_name, fpkg, string, 1, 0, 0, &prefix);
						if (tmp != NULL)
							strncat(pkgdeps, tmp, strlen(tmp));
					}

					// We need to find the subpackage name here
					string = strstr(buf, "PKG_CHOICES_");
					if (string != NULL) {
						check = strstr(buf, ":=");
						if (check != NULL) {
							string[strlen(string)-1] = '\0';
							key = strtok(string, ":=");
							cpkg = strdup(key+12);
						}
					}
					string = strstr(buf, "PKGCB_");
					if (string != NULL) {
						tmp = parse_line(pkgdirp->d_name, cpkg, string, 1, 0, 0, &prefix);
						if (tmp != NULL)
							strncat(pkgdeps, tmp, strlen(tmp));
					}

					// We need to find the subpackage name here
					string = strstr(buf, "PKG_SUBPKGS_");
					if (string != NULL) {
						check = strstr(buf, ":=");
						if (check != NULL) {
							string[strlen(string)-1] = '\0';
							key = strtok(string, ":=");
							spkg = strdup(key+12);
						}
					}

					string = strstr(buf, "PKGSB_");
					if (string != NULL) {
						tmp = parse_line(pkgdirp->d_name, spkg, string, 1, 1, 0, &prefix);
						if (tmp != NULL) {
							strncat(pkgdeps, tmp, strlen(tmp));
						}
					}
				} else if (strncmp(buf, "HOST_BUILDDEP", 13) == 0) {
					//printf("DEBUG: HOST_BUILDDEP found for %s\n", pkgdirp->d_name);
					asprintf(&string, "%s-host", pkgdirp->d_name);
					// check retval; string for NULL
					tmp = parse_line(string, NULL, buf, 2, 0, 0, &hprefix);
					if (tmp && *tmp) {
						asprintf(&string, "%s%s",
						    hpkgdeps ? hpkgdeps : "",
						    tmp);
						free(hpkgdeps);
						hpkgdeps = string;
					}
				}
				free(tmp);
			}
			if (strlen(pkgdeps) != 0)
				printf("%s\n", pkgdeps);
			if (hpkgdeps && *hpkgdeps)
				printf("%s\n", hpkgdeps);
			free(hpkgdeps);
			hpkgdeps = NULL;
			free(pkgdeps);
			free(pkgvar);
			if (fclose(pkg) != 0)
				perror("Closing file stream failed");
		}
	}
	if (closedir(pkgdir) != 0)
		perror("Closing directory stream failed");

	return(0);
}
