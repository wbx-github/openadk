/* $MirOS: contrib/hosted/fwcf/ft_pack.c,v 1.7 2006/09/23 23:21:04 tg Exp $ */

/*-
 * Copyright (c) 2006
 *	Thorsten Glaser <tg@mirbsd.de>
 *
 * Licensee is hereby permitted to deal in this work without restric-
 * tion, including unlimited rights to use, publicly perform, modify,
 * merge, distribute, sell, give away or sublicence, provided all co-
 * pyright notices above, these terms and the disclaimer are retained
 * in all redistributions or reproduced in accompanying documentation
 * or other materials provided with binary redistributions.
 *
 * Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
 * express, or implied, to the maximum extent permitted by applicable
 * law, without malicious intent or gross negligence; in no event may
 * licensor, an author or contributor be held liable for any indirect
 * or other damage, or direct damage except proven a consequence of a
 * direct error of said person and intended use of this work, loss or
 * other issues arising in any way out of its use, even if advised of
 * the possibility of such damage or existence of a defect.
 */

#define _GNU_SOURCE
#include <sys/param.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "defs.h"
#include "fts_subs.h"
#include "pack.h"

__RCSID("$MirOS: contrib/hosted/fwcf/ft_pack.c,v 1.7 2006/09/23 23:21:04 tg Exp $");

char *
ft_pack(ftsf_entry *e)
{
	char f_header[4096], *hdrptr = f_header;
	size_t hdrleft = sizeof (f_header), k;
	char *f_data = NULL, *rv;
	off_t e_size;

	if (e == NULL)
		return (NULL);
	if ((e->etype != FTSF_FILE) && (e->etype != FTSF_SYMLINK) &&
	    (e->etype != FTSF_DIR))
		return (NULL);

	e_size = e->statp->st_size;

	if ((k = strlcpy(hdrptr, e->pathname, hdrleft)) >= hdrleft)
		return (NULL);
	hdrptr += ++k;
	hdrleft -= k;

	if (e->etype == FTSF_SYMLINK) {
		STOREB(0x03);
		e->statp->st_mtime = 0;
		e->statp->st_mode = 0;
	} else if (e->etype == FTSF_DIR) {
		STOREB(0x05);
		e_size = 0;
	}

	if (e->statp->st_mtime) {
		STOREB(0x10);
		STORED(e->statp->st_mtime);
	}

	if (e->statp->st_gid > 0xFF) {
		STOREB('G');
		STORED(e->statp->st_gid);
	} else if (e->statp->st_gid) {
		STOREB('g');
		STOREB(e->statp->st_gid);
	}

	if (e->statp->st_mode > 0xFFFF) {
		STOREB('M');
		STORED(e->statp->st_mode);
	} else if (e->statp->st_mode) {
		STOREB('m');
		STOREW(e->statp->st_mode);
	}

	if (e->statp->st_uid > 0xFF) {
		STOREB('U');
		STORED(e->statp->st_uid);
	} else if (e->statp->st_uid) {
		STOREB('u');
		STOREB(e->statp->st_uid);
	}

	/* e_size is zero for everything except files and symlinks */
	if (e_size > 0xFF) {
		STOREB('S');
		STORET(e_size);
	} else if (e_size) {
		STOREB('s');
		STOREB(e_size);
	}

	STOREB(0);

	if (e_size) {
		if ((f_data = malloc(e_size)) == NULL)
			return (NULL);
		if (asprintf(&rv, "%s/%s", ftsf_prefix, e->pathname) == -1)
			return (NULL);
		if (e->etype == FTSF_SYMLINK) {
			if (readlink(rv, f_data, e_size) != e_size)
				return (NULL);
		} else {
			int fd;

			if ((fd = open(rv, O_RDONLY, 0)) < 0)
				return (NULL);
			if (read(fd, f_data, e_size) != e_size)
				return (NULL);
			close(fd);
		}
		free(rv);
	}
	k = sizeof (size_t) + (hdrptr - f_header) + e_size;
	if ((rv = malloc(k)) == NULL)
		return (NULL);
	*(size_t *)rv = k;
	memcpy(rv + sizeof (size_t), f_header, hdrptr - f_header);
	memcpy(rv + sizeof (size_t) + (hdrptr - f_header), f_data, e_size);
	return (rv);
}
