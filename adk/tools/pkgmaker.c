/*
 * pkgmaker - create package meta-data for OpenADK buildsystem
 *
 * Copyright (C) 2010-2016 Waldemar Brodkorb <wbx@openadk.org>
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
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "sortfile.h"
#include "strmap.h"

#define MAXLINE 4096
#define MAXVALUE 168
#define MAXVAR 	64
#define MAXPATH 320
#define HASHSZ	96

static int nobinpkgs;

#define fatal_error(...) { \
	fprintf(stderr, "Fatal error. "); \
	fprintf(stderr, __VA_ARGS__); \
	fprintf(stderr, "\n"); \
	exit(1); \
}

static int parse_var_hash(char *buf, const char *varname, StrMap *strmap) {

	char *key, *value, *string;

	string = strstr(buf, varname);
	if (string != NULL) {
		string[strlen(string)-1] = '\0';
		key = strtok(string, ":=");
		value = strtok(NULL, "=\t");
		if (value != NULL)
			strmap_put(strmap, key, value);
		return(0);
	}
	return(1);
}

static int parse_var(char *buf, const char *varname, char *pvalue, char **result) {

	char *pkg_var;
	char *key, *value, *string;
	char pkg_str[MAXVAR];

	if ((pkg_var = malloc(MAXLINE)) != NULL)
		memset(pkg_var, 0, MAXLINE);
	else {
		perror("Can not allocate memory");
		exit(EXIT_FAILURE);
	}

	if (snprintf(pkg_str, MAXVAR, "%s:=", varname) < 0)
		perror("can not create path variable.");
	string = strstr(buf, pkg_str);
	if (string != NULL) {
		string[strlen(string)-1] = '\0';
		key = strtok(string, ":=");
		value = strtok(NULL, "=\t");
		if (value != NULL) {
			strncat(pkg_var, value, strlen(value));
			*result = strdup(pkg_var);
		} else {
			nobinpkgs = 1;
			*result = NULL;
		}
		free(pkg_var);
		return(0);
	} else {
		if (snprintf(pkg_str, MAXVAR, "%s+=", varname) < 0)
			perror("can not create path variable.");
		string = strstr(buf, pkg_str);
		if (string != NULL) {
			string[strlen(string)-1] = '\0';
			key = strtok(string, "+=");
			value = strtok(NULL, "=\t");
			if (pvalue != NULL)
				strncat(pkg_var, pvalue, strlen(pvalue));
			strncat(pkg_var, " ", 1);
			if (value != NULL)
				strncat(pkg_var, value, strlen(value));
			*result = strdup(pkg_var);
			free(pkg_var);
			return(0);
		}
	}
	free(pkg_var);
	return(1);
}

static int parse_var_with_system(char *buf, const char *varname, char *pvalue, char **result, char **sysname, int varlen) {

	char *pkg_var, *check;
	char *key, *value, *string;

	if ((pkg_var = malloc(MAXLINE)) != NULL)
		memset(pkg_var, 0, MAXLINE);
	else {
		perror("Can not allocate memory");
		exit(EXIT_FAILURE);
	}

	check = strstr(buf, ":=");
	if (check != NULL) {
		string = strstr(buf, varname);
		if (string != NULL) {
			string[strlen(string)-1] = '\0';
			key = strtok(string, ":=");
			*sysname = strdup(key+varlen);
			value = strtok(NULL, "=\t");
			if (value != NULL) {
				strncat(pkg_var, value, strlen(value));
				*result = strdup(pkg_var);
			}
			free(pkg_var);
			return(0);
		}
	} else {
		string = strstr(buf, varname);
		if (string != NULL) {
			string[strlen(string)-1] = '\0';
			key = strtok(string, "+=");
			value = strtok(NULL, "=\t");
			if (pvalue != NULL)
				strncat(pkg_var, pvalue, strlen(pvalue));
			strncat(pkg_var, " ", 1);
			if (value != NULL)
				strncat(pkg_var, value, strlen(value));
			*result = strdup(pkg_var);
			free(pkg_var);
			return(0);
		}
	}
	free(pkg_var);
	return(1);
}

static int parse_var_with_pkg(char *buf, const char *varname, char *pvalue, char **result, char **pkgname, int varlen) {

	char *pkg_var, *check;
	char *key, *value, *string;

	if ((pkg_var = malloc(MAXLINE)) != NULL)
		memset(pkg_var, 0, MAXLINE);
	else {
		perror("Can not allocate memory");
		exit(EXIT_FAILURE);
	}

	check = strstr(buf, ":=");
	if (check != NULL) {
		string = strstr(buf, varname);
		if (string != NULL) {
			string[strlen(string)-1] = '\0';
			key = strtok(string, ":=");
			*pkgname = strdup(key+varlen);
			value = strtok(NULL, "=\t");
			if (value != NULL) {
				strncat(pkg_var, value, strlen(value));
				*result = strdup(pkg_var);
			}
			free(pkg_var);
			return(0);
		}
	} else {
		string = strstr(buf, varname);
		if (string != NULL) {
			string[strlen(string)-1] = '\0';
			key = strtok(string, "+=");
			value = strtok(NULL, "=\t");
			if (pvalue != NULL)
				strncat(pkg_var, pvalue, strlen(pvalue));
			strncat(pkg_var, " ", 1);
			if (value != NULL)
				strncat(pkg_var, value, strlen(value));
			*result = strdup(pkg_var);
			free(pkg_var);
			return(0);
		}
	}
	free(pkg_var);
	return(1);
}

#if 0
static void iter_debug(const char *key, const char *value, const void *obj) {
	fprintf(stderr, "HASHMAP key: %s value: %s\n", key, value);
}
#endif

static int hash_str(char *string) {

	int i;
	int hash;

	hash = 0;
	for (i=0; i<(int)strlen(string); i++) {
		hash += string[i];
	}
	return(hash);
}

static void iter(const char *key, const char *value, const void *obj) {

	FILE *config, *section, *global;
	int hash;
	char *valuestr, *pkg, *subpkg, *subsect, *sect, *keystr;
	char buf[MAXPATH];
	char infile[MAXPATH];
	char outfile[MAXPATH];
	char configsect[MAXPATH];

	keystr = strdup(key);
	sect = strtok(keystr, "/");
	subsect = strtok(NULL, "/");

	snprintf(configsect, MAXPATH, "package/Config.in.auto.%s.%s", sect, subsect);

	valuestr = strdup(value);
	config = fopen(configsect, "a");
	if (config == NULL)
		fatal_error("Can not open file Config.in.auto.<section>.<subsection>");

	hash = hash_str(valuestr);
	snprintf(infile, MAXPATH, "package/pkglist.d/sectionlst.%d", hash);
	snprintf(outfile, MAXPATH, "package/pkglist.d/sectionlst.%d.sorted", hash);

	if (access(infile, F_OK) == 0) {
		valuestr[strlen(valuestr)-1] = '\0';
		fprintf(config, "menu \"%s\"\n", valuestr);
		sortfile(infile, outfile);
		/* avoid duplicate section entries */
		unlink(infile);
		section = fopen(outfile, "r");
		while (fgets(buf, MAXPATH, section) != NULL) {
			buf[strlen(buf)-1] = '\0';
			if (buf[strlen(buf)-1] == '@') {
				buf[strlen(buf)-1] = '\0';
				fprintf(config, "source \"package/%s/Config.in.manual\"\n", buf);
			} else {
				subpkg = strtok(buf, "|");
				subpkg[strlen(subpkg)-1] = '\0';
				pkg = strtok(NULL, "|");
				fprintf(config, "source \"package/pkgconfigs.d/%s/Config.in.%s\"\n", pkg, subpkg);
			}
		}
		fprintf(config, "endmenu\n\n");
		fclose(section);
	}
	fclose(config);
}

static char *tolowerstr(char *string) {

	int i;
	char *str;

	/* transform to lowercase variable name */
	str = strdup(string);
	for (i=0; i<(int)strlen(str); i++) {
		if (str[i] == '_')
			str[i] = '-';
		str[i] = tolower(str[i]);
	}
	return(str);
}

static char *toupperstr(char *string) {

	static char *sdup = NULL;
	static int sduplen = 0;
	int i;

	if (!string) {
		free(sdup);
		sduplen = 0;
		return NULL;
	}

	if (sduplen <= strlen(string)) {
		sduplen = strlen(string) + 1;
		sdup = realloc(sdup, sduplen);
		if (!sdup)
			fatal_error("%s: memory allocation failed: %s\n",
				    __func__, strerror(errno));
	}

	/* transform to uppercase variable name */
	for (i = 0; i < strlen(string) + 1; i++) {
		switch (string[i]) {
		case '+':
			sdup[i] = 'X';
			break;
		case '-':
			sdup[i] = '_';
			break;
		case '!':
			sdup[i] = '_';
			break;
		case '\0':
			sdup[i] = '\0';
			break;
		default:
			sdup[i] = toupper(string[i]);
		}
	}
	return sdup;
}


int main() {

	DIR *pkgdir, *pkglistdir, *scriptdir;
	struct dirent *pkgdirp;
	struct dirent *scriptdirp;
	size_t len;
	FILE *pkg, *cfg, *menuglobal, *section, *initscript, *icfg;
	char hvalue[MAXVALUE];
	char buf[MAXPATH];
	char ibuf[MAXPATH];
	char tbuf[MAXPATH];
	char path[MAXPATH];
	char script[MAXPATH];
	char script2[MAXPATH];
	char spath[MAXPATH];
	char dir[MAXPATH];
	char variable[2*MAXVAR];
	char *key, *value, *token, *cftoken, *sp, *hkey, *val, *pkg_fd;
	char *pkg_name, *pkg_depends, *pkg_kdepends, *pkg_needs, *pkg_depends_system, *pkg_depends_libc, *pkg_section, *pkg_descr, *pkg_url;
	char *pkg_subpkgs, *pkg_cfline, *pkg_dflt;
	char *pkgname, *sysname, *pkg_debug, *pkg_bb;
	char *pkg_libc_depends, *pkg_host_depends, *pkg_system_depends, *pkg_arch_depends, *pkg_flavours, *pkg_flavours_string, *pkg_choices, *pseudo_name;
	char *packages, *pkg_name_u, *pkgs, *pkg_opts, *pkg_libname;
	char *saveptr, *p_ptr, *s_ptr, *pkg_helper, *sname, *sname2;
	int result;
	StrMap *pkgmap, *sectionmap;
	const char runtime[] = "target/config/Config.in.scripts";

	pkg_name = NULL;
	pkg_descr = NULL;
	pkg_section = NULL;
	pkg_url = NULL;
	pkg_depends = NULL;
	pkg_kdepends = NULL;
	pkg_needs = NULL;
	pkg_depends_system = NULL;
	pkg_depends_libc = NULL;
	pkg_opts = NULL;
	pkg_libname = NULL;
	pkg_flavours = NULL;
	pkg_flavours_string = NULL;
	pkg_choices = NULL;
	pkg_subpkgs = NULL;
	pkg_arch_depends = NULL;
	pkg_system_depends = NULL;
	pkg_host_depends = NULL;
	pkg_libc_depends = NULL;
	pkg_dflt = NULL;
	pkg_cfline = NULL;
	pkgname = NULL;
	sysname = NULL;
	pkg_helper = NULL;
	pkg_debug = NULL;
	pkg_bb = NULL;

	p_ptr = NULL;
	s_ptr = NULL;

	system("rm package/Config.in.auto.* 2>/dev/null");
	unlink(runtime);
	/* open global sectionfile */
	menuglobal = fopen("package/Config.in.auto.global", "w");
	if (menuglobal == NULL)
		fatal_error("global section file not writable.");

	/* read section list and create a hash table */
	section = fopen("package/section.lst", "r");
	if (section == NULL)
		fatal_error("section listfile is missing");

	sectionmap = strmap_new(HASHSZ);
	while (fgets(tbuf, MAXPATH, section) != NULL) {
		key = strtok(tbuf, "\t");
		value = strtok(NULL, "\t");
		strmap_put(sectionmap, key, value);
	}
	fclose(section);
	
	if (mkdir("package/pkgconfigs.d", S_IRWXU) > 0)
		fatal_error("creation of package/pkgconfigs.d failed.");
	if (mkdir("package/pkgconfigs.d/gcc", S_IRWXU) > 0)
		fatal_error("creation of package/pkgconfigs.d/gcc failed.");
	if (mkdir("package/pkglist.d", S_IRWXU) > 0)
		fatal_error("creation of package/pkglist.d failed.");

	/* delete Config.in.dev */
	if (snprintf(path, MAXPATH, "package/pkgconfigs.d/gcc/Config.in.dev") < 0)
		fatal_error("failed to create path variable.");
	unlink(path);
	cfg = fopen(path, "w");
	if (cfg == NULL)
		fatal_error("Config.in.dev can not be opened");
	fprintf(cfg, "config ADK_PACKAGE_GLIBC_DEV\n");
	fprintf(cfg, "\tprompt \"glibc-dev............ development files for glibc\"\n");
	fprintf(cfg, "\tboolean\n");
	fprintf(cfg, "\tdefault n\n");
	fprintf(cfg, "\tdepends on ADK_TARGET_LIB_GLIBC\n");
	fprintf(cfg, "\thelp\n");
	fprintf(cfg, "\t  GNU C library header files.\n\n");
	fprintf(cfg, "config ADK_PACKAGE_UCLIBC_NG_DEV\n");
	fprintf(cfg, "\tprompt \"uclibc-ng-dev........ development files for uclibc-ng\"\n");
	fprintf(cfg, "\tboolean\n");
	fprintf(cfg, "\tdefault n\n");
	fprintf(cfg, "\tdepends on ADK_TARGET_LIB_UCLIBC_NG\n");
	fprintf(cfg, "\thelp\n");
	fprintf(cfg, "\t  C library header files.\n\n");
	fprintf(cfg, "config ADK_PACKAGE_MUSL_DEV\n");
	fprintf(cfg, "\tprompt \"musl-dev............. development files for musl\"\n");
	fprintf(cfg, "\tboolean\n");
	fprintf(cfg, "\tdefault n\n");
	fprintf(cfg, "\tdepends on ADK_TARGET_LIB_MUSL\n");
	fprintf(cfg, "\thelp\n");
	fprintf(cfg, "\t  C library header files.\n\n");
	fclose(cfg);	


	/* read Makefile's for all packages */
	pkgdir = opendir("package");
	while ((pkgdirp = readdir(pkgdir)) != NULL) {
		/* skip dotfiles */
		if (strncmp(pkgdirp->d_name, ".", 1) > 0) {
			if (snprintf(path, MAXPATH, "package/%s/Makefile", pkgdirp->d_name) < 0)
				fatal_error("can not create path variable.");
			pkg = fopen(path, "r");
			if (pkg == NULL)
				continue;

			/* runtime configuration */
			if (snprintf(script, MAXPATH, "package/%s/files", pkgdirp->d_name) < 0)
				fatal_error("script variable creation failed.");
			scriptdir = opendir(script);
			if (scriptdir != NULL) {
				while ((scriptdirp = readdir(scriptdir)) != NULL) {
					/* skip dotfiles */
					if (strncmp(scriptdirp->d_name, ".", 1) > 0) {
						len = strlen(scriptdirp->d_name);
						if (strlen(".init") > len)
							continue;
						if (strncmp(scriptdirp->d_name + len - strlen(".init"), ".init", strlen(".init")) == 0) {
							if (snprintf(script, MAXPATH, "package/%s/files/%s", pkgdirp->d_name, scriptdirp->d_name) < 0)
								fatal_error("script variable creation failed.");
							initscript = fopen(script, "r");
							if (initscript == NULL)
								continue;

							while (fgets(ibuf, MAXPATH, initscript) != NULL) {
								if (strncmp("#PKG", ibuf, 4) == 0) {
									sname = strdup(ibuf+5);
									sname[strlen(sname)-1] = '\0';
									sname2 = strdup(scriptdirp->d_name);
									sname2[strlen(sname2)-5] = '\0';
									icfg = fopen(runtime, "a");
									if (icfg == NULL)
										continue;
									if (strncmp("busybox", sname, 7) == 0) {
										fprintf(icfg, "config ADK_RUNTIME_START_%s", toupperstr(sname));
										fprintf(icfg, "_%s\n", toupperstr(sname2));
									} else {
										fprintf(icfg, "config ADK_RUNTIME_START_%s\n", toupperstr(sname));
									}
									fprintf(icfg, "\tprompt \"Start %s on boot\"\n", sname2);
									fprintf(icfg, "\ttristate\n");
									if (strncmp("busybox", sname, 7) == 0)
										fprintf(icfg, "\tdepends on BUSYBOX_%s\n", toupperstr(sname2));
									else
										fprintf(icfg, "\tdepends on ADK_PACKAGE_%s\n", toupperstr(sname));
									fprintf(icfg, "\tdepends on ADK_RUNTIME_START_SERVICES\n");
									fprintf(icfg, "\tdefault n\n\n");
									fclose(icfg);
								}
								continue;
								free(sname);
								free(sname2);
							}
						}
					}
				}
				closedir(scriptdir);
			}

			/* skip manually maintained packages */
			if (snprintf(path, MAXPATH, "package/%s/Config.in.manual", pkgdirp->d_name) < 0)
				fatal_error("can not create path variable.");
			if (!access(path, F_OK)) {
				while (fgets(buf, MAXPATH, pkg) != NULL) {
					if ((parse_var(buf, "PKG_SECTION", NULL, &pkg_section)) == 0)
						continue;
				}

				memset(hvalue, 0 , MAXVALUE);
				result = strmap_get(sectionmap, pkg_section, hvalue, sizeof(hvalue));
				if (result == 1) {
					if (snprintf(spath, MAXPATH, "package/pkglist.d/sectionlst.%d", hash_str(hvalue)) < 0)
						fatal_error("can not create path variable.");
					section = fopen(spath, "a");
					if (section != NULL) {
						fprintf(section, "%s@\n", pkgdirp->d_name);
						fclose(section);
					}
				} else
					fatal_error("Can not find section description %s for package %s.",
							pkg_section, pkgdirp->d_name);
				
				fclose(pkg);
				continue;
			}

			nobinpkgs = 0;
			
			/* create output directories */
			if (snprintf(dir, MAXPATH, "package/pkgconfigs.d/%s", pkgdirp->d_name) < 0)
				fatal_error("can not create dir variable.");
			if (mkdir(dir, S_IRWXU) > 0)
				fatal_error("can not create directory.");


			/* allocate memory */
			hkey = malloc(MAXVAR);
			memset(hkey, 0, MAXVAR);
			memset(variable, 0, 2*MAXVAR);

			pkgmap = strmap_new(HASHSZ);

			/* parse package Makefile */
			while (fgets(buf, MAXPATH, pkg) != NULL) {
				/* just read variables prefixed with PKG */
				if (strncmp(buf, "PKG", 3) == 0) {
					if ((parse_var(buf, "PKG_NAME", NULL, &pkg_name)) == 0)
						continue;
					if (pkg_name != NULL)
						pkg_name_u = toupperstr(pkg_name);
					else
						pkg_name_u = toupperstr(pkgdirp->d_name);

					snprintf(variable, MAXVAR, "PKG_CFLINE_%s", pkg_name_u);
					if ((parse_var(buf, variable, pkg_cfline, &pkg_cfline)) == 0)
						continue;
					snprintf(variable, MAXVAR, "PKG_DFLT_%s", pkg_name_u);
					if ((parse_var(buf, variable, NULL, &pkg_dflt)) == 0)
						continue;
					if ((parse_var(buf, "PKG_LIBC_DEPENDS", NULL, &pkg_libc_depends)) == 0)
						continue;
					if ((parse_var(buf, "PKG_HOST_DEPENDS", NULL, &pkg_host_depends)) == 0)
						continue;
					if ((parse_var(buf, "PKG_ARCH_DEPENDS", NULL, &pkg_arch_depends)) == 0)
						continue;
					if ((parse_var(buf, "PKG_SYSTEM_DEPENDS", NULL, &pkg_system_depends)) == 0)
						continue;
					if ((parse_var(buf, "PKG_DESCR", NULL, &pkg_descr)) == 0)
						continue;
					if ((parse_var(buf, "PKG_SECTION", NULL, &pkg_section)) == 0)
						continue;
					if ((parse_var(buf, "PKG_URL", NULL, &pkg_url)) == 0)
						continue;
					if ((parse_var(buf, "PKG_BB", NULL, &pkg_bb)) == 0)
						continue;
					if ((parse_var(buf, "PKG_DEPENDS", pkg_depends, &pkg_depends)) == 0)
						continue;
					if ((parse_var(buf, "PKG_KDEPENDS", pkg_kdepends, &pkg_kdepends)) == 0)
						continue;
					if ((parse_var(buf, "PKG_NEEDS", pkg_needs, &pkg_needs)) == 0)
						continue;
					if ((parse_var_with_system(buf, "PKG_DEPENDS_", pkg_depends_system, &pkg_depends_system, &sysname, 12)) == 0)
						continue;
					if ((parse_var_with_system(buf, "PKG_DEPENDS_", pkg_depends_libc, &pkg_depends_libc, &sysname, 12)) == 0)
						continue;
					if ((parse_var(buf, "PKG_LIBNAME", pkg_libname, &pkg_libname)) == 0) 
						continue;
					if ((parse_var(buf, "PKG_OPTS", pkg_opts, &pkg_opts)) == 0)
						continue;
					if ((parse_var_with_pkg(buf, "PKG_FLAVOURS_STRING_", pkg_flavours_string, &pkg_flavours_string, &pkgname, 20)) == 0)
						continue;
					if ((parse_var_with_pkg(buf, "PKG_FLAVOURS_", pkg_flavours, &pkg_flavours, &pkgname, 13)) == 0)
						continue;
					if ((parse_var_hash(buf, "PKGFD_", pkgmap)) == 0)
						continue;
					if ((parse_var_hash(buf, "PKGFX_", pkgmap)) == 0)
						continue;
					if ((parse_var_hash(buf, "PKGFS_", pkgmap)) == 0)
						continue;
					if ((parse_var_hash(buf, "PKGFC_", pkgmap)) == 0)
						continue;
					if ((parse_var_with_pkg(buf, "PKG_CHOICES_", pkg_choices, &pkg_choices, &pkgname, 12)) == 0)
						continue;
					if ((parse_var_hash(buf, "PKGCD_", pkgmap)) == 0)
						continue;
					if ((parse_var_hash(buf, "PKGCS_", pkgmap)) == 0)
						continue;
					if ((parse_var(buf, "PKG_SUBPKGS", pkg_subpkgs, &pkg_subpkgs)) == 0)
						continue;
					if ((parse_var_hash(buf, "PKGSD_", pkgmap)) == 0)
						continue;
					if ((parse_var_hash(buf, "PKGSS_", pkgmap)) == 0)
						continue;
					if ((parse_var_hash(buf, "PKGSC_", pkgmap)) == 0)
						continue;
					if ((parse_var_hash(buf, "PKGSK_", pkgmap)) == 0)
						continue;
					if ((parse_var_hash(buf, "PKGSN_", pkgmap)) == 0)
						continue;
				}
			}

			/* when PKG_LIBNAME exist use this instead of PKG_NAME, but only for !libmix */
			if (pkg_libname != NULL)
				if (pkg_opts != NULL)
					if (strstr(pkg_opts, "libmix") == NULL)
						pkg_name = strdup(pkg_libname);

			/* end of package Makefile parsing */
			if (fclose(pkg) != 0)
				perror("Failed to close file stream for Makefile");

#if 0
			if (pkg_name != NULL)
				fprintf(stderr, "Package name is %s\n", pkg_name);
			if (pkg_libname != NULL)
				fprintf(stderr, "Package library name is %s\n", pkg_libname);
			if (pkg_section != NULL)
				fprintf(stderr, "Package section is %s\n", pkg_section);
			if (pkg_descr != NULL)
				fprintf(stderr, "Package description is %s\n", pkg_descr);
			if (pkg_depends != NULL)
				fprintf(stderr, "Package dependencies are %s\n", pkg_depends);
			if (pkg_needs != NULL)
				fprintf(stderr, "Package needing %s\n", pkg_needs);
			if (pkg_depends_system != NULL)
				fprintf(stderr, "Package systemspecific dependencies are %s\n", pkg_depends_system);
			if (pkg_subpkgs != NULL)
				fprintf(stderr, "Package subpackages are %s\n", pkg_subpkgs);
			if (pkg_flavours != NULL && pkgname != NULL)
				fprintf(stderr, "Package flavours for %s are %s\n", pkgname, pkg_flavours);
			if (pkg_flavours_string != NULL && pkgname != NULL)
				fprintf(stderr, "Package string flavours for %s are %s\n", pkgname, pkg_flavours_string);
			if (pkg_choices != NULL && pkgname != NULL)
				fprintf(stderr, "Package choices for %s are %s\n", pkgname, pkg_choices);
			if (pkg_url != NULL)
				fprintf(stderr, "Package homepage is %s\n", pkg_url);
			if (pkg_cfline != NULL)
				fprintf(stderr, "Package cfline is %s\n", pkg_cfline);
			if (pkg_opts != NULL)
				fprintf(stderr, "Package options are %s\n", pkg_opts);

			strmap_enum(pkgmap, iter_debug, NULL);
#endif

			/* generate master source Config.in file */
			if (snprintf(path, MAXPATH, "package/pkgconfigs.d/%s/Config.in", pkgdirp->d_name) < 0)
				fatal_error("path variable creation failed.");
			fprintf(menuglobal, "source \"%s\"\n", path);
			/* recreating file is faster than truncating with w+ */
			unlink(path);
			cfg = fopen(path, "w");
			if (cfg == NULL)
				continue;

			pkgs = NULL;
			if (pkg_subpkgs != NULL)
				pkgs = strdup(pkg_subpkgs);

			fprintf(cfg, "config ADK_COMPILE_%s\n", toupperstr(pkgdirp->d_name));
			fprintf(cfg, "\tboolean\n");
			if (nobinpkgs == 0) {
				fprintf(cfg, "\tdepends on ");
				if (pkgs != NULL) {
					token = strtok(pkgs, " ");
					fprintf(cfg, "ADK_PACKAGE_%s", token);
					token = strtok(NULL, " ");
					while (token != NULL) {
						fprintf(cfg, " || ADK_PACKAGE_%s", token);
						token = strtok(NULL, " ");
					}
					fprintf(cfg, "\n");
				} else {
					fprintf(cfg, "ADK_PACKAGE_%s\n", toupperstr(pkg_name));
				}
			} 
			fprintf(cfg, "\tdefault n\n");
			fclose(cfg);
			free(pkgs);

			/* skip packages without binary package output */
			if (nobinpkgs == 1)
				continue;

			/* generate binary package specific Config.in files */
			if (pkg_subpkgs != NULL)
				packages = tolowerstr(pkg_subpkgs);
			else
				packages = strdup(pkg_name);

			token = strtok_r(packages, " ", &p_ptr);
			while (token != NULL) {
				strncat(hkey, "PKGSC_", 6);
				strncat(hkey, toupperstr(token), strlen(token));
				memset(hvalue, 0 , MAXVALUE);
				result = strmap_get(pkgmap, hkey, hvalue, sizeof(hvalue));
				memset(hkey, 0 , MAXVAR);
				if (result == 1)
					pkg_section = strdup(hvalue);

				strncat(hkey, "PKGSD_", 6);
				strncat(hkey, toupperstr(token), strlen(token));
				memset(hvalue, 0 , MAXVALUE);
				result = strmap_get(pkgmap, hkey, hvalue, sizeof(hvalue));
				memset(hkey, 0 , MAXVAR);
				if (result == 1)
					pkg_descr = strdup(hvalue);

				pseudo_name = malloc(MAXLINE);
				memset(pseudo_name, 0, MAXLINE);
				strncat(pseudo_name, token, strlen(token));
				while (strlen(pseudo_name) < 23)
					strncat(pseudo_name, ".", 1);

				if (snprintf(path, MAXPATH, "package/pkgconfigs.d/%s/Config.in.%s", pkgdirp->d_name, token) < 0)
					fatal_error("failed to create path variable.");

				/* create temporary section files */
				memset(hvalue, 0 , MAXVALUE);
				result = strmap_get(sectionmap, pkg_section, hvalue, sizeof(hvalue));
				if (result == 1) {
					if (snprintf(spath, MAXPATH, "package/pkglist.d/sectionlst.%d", hash_str(hvalue)) < 0)
						fatal_error("failed to create path variable.");
					section = fopen(spath, "a");
					if (section != NULL) {
						fprintf(section, "%s |%s\n", token, pkgdirp->d_name);
						fclose(section);
					}
				} else
					fatal_error("Can not find section description for package %s.", pkgdirp->d_name);

				unlink(path);
				cfg = fopen(path, "w");
				if (cfg == NULL)
					perror("Can not open Config.in file");

				if (pkg_bb != NULL) {
					fprintf(cfg, "comment \"%s... %s (provided by busybox)\"\n", token, pkg_descr);
					fprintf(cfg, "depends on ADK_PACKAGE_BUSYBOX_HIDE\n\n");
				}

				/* save token in pkg_debug */
				pkg_debug = strdup(token);
				fprintf(cfg, "config ADK_PACKAGE_%s\n", toupperstr(token));
				/* no prompt for devonly packages */
				if (pkg_opts != NULL) {
					if (strstr(pkg_opts, "devonly") != NULL) {
						fprintf(cfg, "\t#prompt \"%s. %s\"\n", pseudo_name, pkg_descr);
					} else {
						fprintf(cfg, "\tprompt \"%s. %s\"\n", pseudo_name, pkg_descr);
					}
				} else {
					fprintf(cfg, "\tprompt \"%s. %s\"\n", pseudo_name, pkg_descr);
				}	
				
				fprintf(cfg, "\tbool\n");
				free(pseudo_name);

				/* print custom cf line */
				if (pkg_cfline != NULL) {
					cftoken = strtok_r(pkg_cfline, "@", &saveptr);
					while (cftoken != NULL) {
						fprintf(cfg, "\t%s\n", cftoken);
						cftoken = strtok_r(NULL, "@", &saveptr);
					}
					free(pkg_cfline);
					pkg_cfline = NULL;
				}

				/* add sub package dependencies */
				strncat(hkey, "PKGSN_", 6);
				strncat(hkey, toupperstr(token), strlen(token));
				memset(hvalue, 0, MAXVALUE);
				result = strmap_get(pkgmap, hkey, hvalue, sizeof(hvalue));
				if (result == 1) {
					val = strtok_r(hvalue, " ", &saveptr);
					while (val != NULL) { 
						fprintf(cfg, "\tdepends on ADK_PACKAGE_%s\n", toupperstr(val));
						val = strtok_r(NULL, " ", &saveptr);
					}
				}
				memset(hkey, 0, MAXVAR);

				/* add sub package auto selections */
				strncat(hkey, "PKGSS_", 6);
				strncat(hkey, toupperstr(token), strlen(token));
				memset(hvalue, 0, MAXVALUE);
				result = strmap_get(pkgmap, hkey, hvalue, sizeof(hvalue));
				if (result == 1) {
					val = strtok_r(hvalue, " ", &saveptr);
					while (val != NULL) { 
						fprintf(cfg, "\tselect ADK_PACKAGE_%s\n", toupperstr(val));
						val = strtok_r(NULL, " ", &saveptr);
					}
				}
				memset(hkey, 0, MAXVAR);

				/* add sub package kernel selections */
				strncat(hkey, "PKGSK_", 6);
				strncat(hkey, toupperstr(token), strlen(token));
				memset(hvalue, 0, MAXVALUE);
				result = strmap_get(pkgmap, hkey, hvalue, sizeof(hvalue));
				if (result == 1) {
					val = strtok_r(hvalue, " ", &saveptr);
					while (val != NULL) { 
						fprintf(cfg, "\tselect ADK_KERNEL_%s\n", toupperstr(val));
						val = strtok_r(NULL, " ", &saveptr);
					}
				}
				memset(hkey, 0, MAXVAR);

				/* create package target system dependency information */
				if (pkg_system_depends != NULL) {
					pkg_helper = strdup(pkg_system_depends);
					token = strtok(pkg_helper, " ");
					fprintf(cfg, "\tdepends on ");
					sp = "";
					while (token != NULL) {
						if(strncmp(token, "!", 1) == 0) {
							fprintf(cfg, "%s!ADK_TARGET_SYSTEM%s", sp, toupperstr(token));
							sp = " && ";
						} else {
							fprintf(cfg, "%sADK_TARGET_SYSTEM_%s", sp, toupperstr(token));
							sp = " || ";
						}
						token = strtok(NULL, " ");
					}
					fprintf(cfg, "\n");
					free(pkg_helper);
					pkg_helper = NULL;
				}
				/* create package host dependency information */
				if (pkg_host_depends != NULL) {
					pkg_helper = strdup(pkg_host_depends);
					token = strtok(pkg_helper, " ");
					fprintf(cfg, "\tdepends on ");
					sp = "";
					while (token != NULL) {
						if(strncmp(token, "!", 1) == 0) {
							fprintf(cfg, "%s!ADK_HOST%s", sp, toupperstr(token));
							sp = " && ";
						} else {
							fprintf(cfg, "%sADK_HOST_%s", sp, toupperstr(token));
							sp = " || ";
						}
						token = strtok(NULL, " ");
					}
					fprintf(cfg, "\n");
					free(pkg_helper);
					pkg_helper = NULL;
				}

				/* create package libc dependency information */
				if (pkg_libc_depends != NULL) {
					pkg_helper = strdup(pkg_libc_depends);
					token = strtok(pkg_helper, " ");
					fprintf(cfg, "\tdepends on ");
					sp = "";
					while (token != NULL) {
						if(strncmp(token, "!", 1) == 0) {
							fprintf(cfg, "%s!ADK_TARGET_LIB_%s", sp, toupperstr(token));
							sp = " && ";
						} else {
							fprintf(cfg, "%sADK_TARGET_LIB_%s", sp, toupperstr(token));
							sp = " || ";
						}
						token = strtok(NULL, " ");
					}
					fprintf(cfg, "\n");
					free(pkg_helper);
					pkg_helper = NULL;
				}
				/* create package target architecture dependency information */
				if (pkg_arch_depends != NULL) {
					pkg_helper = strdup(pkg_arch_depends);
					token = strtok(pkg_helper, " ");
					fprintf(cfg, "\tdepends on ");
					sp = "";
					while (token != NULL) {
						if(strncmp(token, "!", 1) == 0) {
							fprintf(cfg, "%s!ADK_TARGET_ARCH%s", sp, toupperstr(token));
							sp = " && ";
						} else {
							fprintf(cfg, "%sADK_TARGET_ARCH_%s", sp, toupperstr(token));
							sp = " || ";
						}
						token = strtok(NULL, " ");
					}
					fprintf(cfg, "\n");
					free(pkg_helper);
					pkg_helper = NULL;
				}

				/* create needs dependency information */
				if (pkg_needs != NULL) {
					token = strtok(pkg_needs, " ");
					while (token != NULL) {
						if (strncmp(token, "c++", 3) == 0) {
							fprintf(cfg, "\tselect ADK_TOOLCHAIN_WITH_CXX\n");
							fprintf(cfg, "\tselect ADK_PACKAGE_LIBSTDCXX\n");
						}
						if (strncmp(token, "iconv", 5) == 0)
							fprintf(cfg, "\tselect ADK_TARGET_LIBC_WITH_LIBICONV if ADK_TARGET_LIB_UCLIBC_NG && !ADK_PACKAGE_LIBICONV\n");
						if (strncmp(token, "intl", 4) == 0)
							fprintf(cfg, "\tselect ADK_TARGET_LIBC_WITH_LIBINTL if ADK_TARGET_LIB_UCLIBC_NG\n");
						if (strncmp(token, "locale", 6) == 0)
							fprintf(cfg, "\tselect ADK_TARGET_LIBC_WITH_LOCALE if ADK_TARGET_LIB_UCLIBC_NG\n");
						if (strncmp(token, "threads", 7) == 0)
							fprintf(cfg, "\tselect ADK_TARGET_LIB_WITH_THREADS\n");
						if (strncmp(token, "data", 4) == 0)
							fprintf(cfg, "\tselect ADK_RUNTIME_DATA_PARTITION\n");
						if (strncmp(token, "mmu", 3) == 0)
							fprintf(cfg, "\tdepends on ADK_TARGET_WITH_MMU\n");
						token = strtok(NULL, " ");
					}
					free(pkg_needs);
					pkg_needs = NULL;
				}

				/* create package dependency information */
				if (pkg_depends != NULL) {
					token = strtok(pkg_depends, " ");
					while (token != NULL) {
						fprintf(cfg, "\tselect ADK_PACKAGE_%s\n", toupperstr(token));
						token = strtok(NULL, " ");
					}
					free(pkg_depends);
					pkg_depends = NULL;
				}
				/* create kernel package dependency information */
				if (pkg_kdepends != NULL) {
					token = strtok(pkg_kdepends, " ");
					while (token != NULL) {
						fprintf(cfg, "\tselect ADK_LINUX_KERNEL_%s m if ADK_TARGET_OS_LINUX\n", toupperstr(token));
						token = strtok(NULL, " ");
					}
					free(pkg_kdepends);
					pkg_kdepends = NULL;
				}
				/* create system specific package dependency information */
				if (pkg_depends_system != NULL) {
					token = strtok(pkg_depends_system, " ");
					while (token != NULL) {
						fprintf(cfg, "\tselect ADK_PACKAGE_%s if ADK_TARGET_SYSTEM_%s\n", toupperstr(token), sysname);
						token = strtok(NULL, " ");
					}
					free(pkg_depends_system);
					pkg_depends_system = NULL;
				}
				/* create libc specific package dependency information */
				if (pkg_depends_libc != NULL) {
					token = strtok(pkg_depends_libc, " ");
					while (token != NULL) {
						fprintf(cfg, "\tselect ADK_PACKAGE_%s if ADK_TARGET_LIB_%s\n", toupperstr(token), sysname);
						token = strtok(NULL, " ");
					}
					free(pkg_depends_libc);
					pkg_depends_libc = NULL;
				}

				if (pkg_bb != NULL) {
					fprintf(cfg, "\tdepends on !ADK_PACKAGE_BUSYBOX_HIDE\n");
				}
				fprintf(cfg, "\tselect ADK_COMPILE_%s\n", toupperstr(pkgdirp->d_name));

				if (pkg_dflt != NULL) {
					fprintf(cfg, "\tdefault %s\n", pkg_dflt);
					pkg_dflt = NULL;
				} else {
					fprintf(cfg, "\tdefault n\n");
				}

				fprintf(cfg, "\thelp\n");
				fprintf(cfg, "\t  %s\n\n", pkg_descr);
				if (pkg_url != NULL)
					fprintf(cfg, "\t  WWW: %s\n", pkg_url);

				/* handle debug subpackages */
				fprintf(cfg, "\nconfig ADK_PACKAGE_%s_DBG\n", toupperstr(pkg_debug));
				fprintf(cfg, "\tbool \"add debug symbols package\"\n");
				fprintf(cfg, "\tdepends on ADK_PACKAGE_GDB && ADK_BUILD_WITH_DEBUG\n");
				fprintf(cfg, "\tdepends on ADK_DEBUG\n");
				fprintf(cfg, "\tdepends on ADK_PACKAGE_%s\n", toupperstr(pkg_debug));
				fprintf(cfg, "\tdefault n\n");
				fprintf(cfg, "\thelp\n\n");

				/* package flavours */
				if (pkg_flavours != NULL) {
					token = strtok(pkg_flavours, " ");
					while (token != NULL) {
						fprintf(cfg, "\nconfig ADK_PACKAGE_%s_%s\n", pkgname, toupperstr(token));

						// process default value
						strncat(hkey, "PKGFX_", 6);
						strncat(hkey, token, strlen(token));
						memset(hvalue, 0 , MAXVALUE);
						strmap_get(pkgmap, hkey, hvalue, sizeof(hvalue));
						memset(hkey, 0 , MAXVAR);
						pkg_fd = strdup(hvalue);
						if (strlen(pkg_fd) > 0)
							fprintf(cfg, "\tdefault %s\n", pkg_fd);
						else
							fprintf(cfg, "\tdefault n\n");


						// process flavour cfline
						strncat(hkey, "PKGFC_", 6);
						strncat(hkey, token, strlen(token));
						memset(hvalue, 0 , MAXVALUE);
						strmap_get(pkgmap, hkey, hvalue, sizeof(hvalue));
						memset(hkey, 0 , MAXVAR);
						pkg_fd = strdup(hvalue);
						if (strlen(pkg_fd) > 0)
							fprintf(cfg, "\t%s\n", pkg_fd);

						fprintf(cfg, "\tboolean ");
						strncat(hkey, "PKGFD_", 6);
						strncat(hkey, token, strlen(token));
						memset(hvalue, 0 , MAXVALUE);
						strmap_get(pkgmap, hkey, hvalue, sizeof(hvalue));
						memset(hkey, 0 , MAXVAR);
						pkg_fd = strdup(hvalue);

						fprintf(cfg, "\"%s\"\n", pkg_fd);
						fprintf(cfg, "\tdepends on ADK_PACKAGE_%s\n", pkgname);
						strncat(hkey, "PKGFS_", 6);
						strncat(hkey, token, strlen(token));

						result = strmap_get(pkgmap, hkey, hvalue, sizeof(hvalue));
						if (result == 1) {
							val = strtok_r(hvalue, " ", &saveptr);
							while (val != NULL) { 
								fprintf(cfg, "\tselect ADK_PACKAGE_%s\n", toupperstr(val));
								val = strtok_r(NULL, " ", &saveptr);
							}
						}
						memset(hkey, 0, MAXVAR);
						fprintf(cfg, "\thelp\n");
						fprintf(cfg, "\t  %s\n", pkg_fd);
						token = strtok(NULL, " ");
					}
					free(pkg_flavours);
					pkg_flavours = NULL;
				}

				/* package flavours string */
				if (pkg_flavours_string != NULL) {
					token = strtok(pkg_flavours_string, " ");
					while (token != NULL) {
						fprintf(cfg, "\nconfig ADK_PACKAGE_%s_%s\n", pkgname, toupperstr(token));

						// process default value
						strncat(hkey, "PKGFX_", 6);
						strncat(hkey, token, strlen(token));
						memset(hvalue, 0 , MAXVALUE);
						strmap_get(pkgmap, hkey, hvalue, sizeof(hvalue));
						memset(hkey, 0 , MAXVAR);
						pkg_fd = strdup(hvalue);
						if (strlen(pkg_fd) > 0)
							fprintf(cfg, "\tdefault \"%s\"\n", pkg_fd);

						// process flavour cfline
						strncat(hkey, "PKGFC_", 6);
						strncat(hkey, token, strlen(token));
						memset(hvalue, 0 , MAXVALUE);
						strmap_get(pkgmap, hkey, hvalue, sizeof(hvalue));
						memset(hkey, 0 , MAXVAR);
						pkg_fd = strdup(hvalue);
						if (strlen(pkg_fd) > 0)
							fprintf(cfg, "\t%s\n", pkg_fd);

						fprintf(cfg, "\tstring ");
						strncat(hkey, "PKGFD_", 6);
						strncat(hkey, token, strlen(token));
						memset(hvalue, 0 , MAXVALUE);
						strmap_get(pkgmap, hkey, hvalue, sizeof(hvalue));
						memset(hkey, 0 , MAXVAR);
						pkg_fd = strdup(hvalue);
						fprintf(cfg, "\"%s\"\n", pkg_fd);

						fprintf(cfg, "\tdepends on ADK_PACKAGE_%s\n", pkgname);
						strncat(hkey, "PKGFS_", 6);
						strncat(hkey, token, strlen(token));

						result = strmap_get(pkgmap, hkey, hvalue, sizeof(hvalue));
						if (result == 1) {
							val = strtok_r(hvalue, " ", &saveptr);
							while (val != NULL) { 
								fprintf(cfg, "\tselect ADK_PACKAGE_%s\n", toupperstr(val));
								val = strtok_r(NULL, " ", &saveptr);
							}
						}
						memset(hkey, 0, MAXVAR);
						fprintf(cfg, "\thelp\n");
						fprintf(cfg, "\t  %s\n", pkg_fd);
						token = strtok(NULL, " ");
					}
					free(pkg_flavours_string);
					pkg_flavours_string = NULL;
				}

				/* package choices */
				if (pkg_choices != NULL) {
					fprintf(cfg, "\nchoice\n");
					fprintf(cfg, "prompt \"Package flavour choice\"\n");
					fprintf(cfg, "depends on ADK_PACKAGE_%s\n\n", pkgname);
					token = strtok(pkg_choices, " ");
					while (token != NULL) {
						fprintf(cfg, "config ADK_PACKAGE_%s_%s\n", pkgname, toupperstr(token));

						fprintf(cfg, "\tbool ");
						strncat(hkey, "PKGCD_", 6);
						strncat(hkey, token, strlen(token));
						memset(hvalue, 0 , MAXVALUE);
						strmap_get(pkgmap, hkey, hvalue, sizeof(hvalue));
						memset(hkey, 0 , MAXVAR);
						fprintf(cfg, "\"%s\"\n", hvalue);

						strncat(hkey, "PKGCS_", 6);
						strncat(hkey, token, strlen(token));
						memset(hvalue, 0, MAXVALUE);
						result = strmap_get(pkgmap, hkey, hvalue, sizeof(hvalue));
						if (result == 1) {
							val = strtok_r(hvalue, " ", &saveptr);
							while (val != NULL) { 
								fprintf(cfg, "\tselect ADK_PACKAGE_%s\n", toupperstr(val));
								val = strtok_r(NULL, " ", &saveptr);
							}
						}
						memset(hkey, 0, MAXVAR);
						token = strtok(NULL, " ");
					}
					fprintf(cfg, "\nendchoice\n");
					free(pkg_choices);
					pkg_choices = NULL;
				}
				/* close file descriptor for Config.in file */
				fclose(cfg);
				/* create Config.in files for development packages */
				if (pkg_opts != NULL) {
					if (strstr(pkg_opts, "dev") != NULL) {
						if (snprintf(path, MAXPATH, "package/pkgconfigs.d/gcc/Config.in.dev") < 0)
							fatal_error("failed to create path variable.");
						cfg = fopen(path, "a");
						if (cfg == NULL)
							perror("Can not open Config.in.dev file");

						if (pkg_libname == NULL)
							pkg_libname = strdup(pkg_name);

						fprintf(cfg, "\n");
						fprintf(cfg, "config ADK_PACKAGE_%s_DEV\n", toupperstr(pkg_libname));

						pseudo_name = malloc(MAXLINE);
						memset(pseudo_name, 0, MAXLINE);
						strncat(pseudo_name, pkg_libname, strlen(pkg_libname));
						strncat(pseudo_name, "-dev", 4);
						while (strlen(pseudo_name) < 20)
							strncat(pseudo_name, ".", 1);

						fprintf(cfg, "\tprompt \"%s. development files for %s\"\n", pseudo_name, pkg_libname);
						fprintf(cfg, "\tboolean\n");

						/* create package target architecture dependency information */
						if (pkg_arch_depends != NULL) {
							pkg_helper = strdup(pkg_arch_depends);
							token = strtok(pkg_helper, " ");
							fprintf(cfg, "\tdepends on ");
							sp = "";
							while (token != NULL) {
								if(strncmp(token, "!", 1) == 0) {
									fprintf(cfg, "%s!ADK_TARGET_ARCH%s", sp, toupperstr(token));
									sp = " && ";
								} else {
									fprintf(cfg, "%sADK_TARGET_ARCH_%s", sp, toupperstr(token));
									sp = " || ";
								}
							token = strtok(NULL, " ");
							}
							fprintf(cfg, "\n");
							free(pkg_helper);
							pkg_helper = NULL;
						}

						fprintf(cfg, "\tdepends on ADK_PACKAGE_GCC && ADK_PACKAGE_%s\n", toupperstr(pkg_libname));
						fprintf(cfg, "\tdefault n\n");
						fclose(cfg);
						free(pseudo_name);
						free(pkg_libname);
						pkg_libname = NULL;
					}
					pkg_opts = NULL;
				}
				/* parse next package */
				token = strtok_r(NULL, " ", &p_ptr);
			}

			/* end of package output generation */
			free(packages);
			packages = NULL;

			/* reset flags, free memory */
			free(pkg_name);
			free(pkg_libname);
			free(pkg_descr);
			free(pkg_section);
			free(pkg_url);
			free(pkg_depends);
			free(pkg_kdepends);
			free(pkg_flavours);
			free(pkg_flavours_string);
			free(pkg_choices);
			free(pkg_subpkgs);
			free(pkg_arch_depends);
			free(pkg_system_depends);
			free(pkg_host_depends);
			free(pkg_libc_depends);
			free(pkg_dflt);
			free(pkg_cfline);
			free(pkg_bb);
			pkg_name = NULL;
			pkg_libname = NULL;
			pkg_descr = NULL;
			pkg_section = NULL;
			pkg_url = NULL;
			pkg_depends = NULL;
			pkg_kdepends = NULL;
			pkg_flavours = NULL;
			pkg_flavours_string = NULL;
			pkg_choices = NULL;
			pkg_subpkgs = NULL;
			pkg_arch_depends = NULL;
			pkg_system_depends = NULL;
			pkg_host_depends = NULL;
			pkg_libc_depends = NULL;
			pkg_dflt = NULL;
			pkg_cfline = NULL;
			pkg_bb = NULL;

			strmap_delete(pkgmap);
			nobinpkgs = 0;
			free(hkey);
		}
	}

	/* add menu to gcc package */
	if (snprintf(path, MAXPATH, "package/pkgconfigs.d/gcc/Config.in.gcc") < 0)
		fatal_error("failed to create path variable.");
	cfg = fopen(path, "a");
	if (cfg == NULL)
		perror("Can not open Config.in.gcc file");
	fprintf(cfg, "menu \"Development packages\"\n");
	fprintf(cfg, "depends on ADK_PACKAGE_GCC\n");
	fprintf(cfg, "source \"package/pkgconfigs.d/gcc/Config.in.dev\"\n");
	fprintf(cfg, "endmenu\n");
	fclose(cfg);

	/* create Config.in.auto */
	strmap_enum(sectionmap, iter, NULL);

	strmap_delete(sectionmap);
	fclose(menuglobal);
	closedir(pkgdir);

	/* remove temporary section files */
	pkglistdir = opendir("package/pkglist.d");
	while ((pkgdirp = readdir(pkglistdir)) != NULL) {
		if (strncmp(pkgdirp->d_name, "sectionlst.", 11) == 0) {
			if (snprintf(path, MAXPATH, "package/pkglist.d/%s", pkgdirp->d_name) < 0)
				fatal_error("creating path variable failed.");
			if (unlink(path) < 0)
				fatal_error("removing file failed.");
		}
	}
	toupperstr(NULL);
	closedir(pkglistdir);
	return(0);
}
