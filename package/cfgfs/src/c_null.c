/* $MirOS: contrib/hosted/fwcf/c_null.c,v 1.5 2006/09/23 23:46:35 tg Exp $ */

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

#include <sys/param.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "compress.h"

__RCSID("$MirOS: contrib/hosted/fwcf/c_null.c,v 1.5 2006/09/23 23:46:35 tg Exp $");

static void c_null_load(void) __attribute__((constructor));
static int c_init(void);
static int c_compress(char **, char *, size_t)
    __attribute__((access (read_only, 2, 3)));
static int c_decompress(char *, size_t, char *, size_t)
    __attribute__((access (read_write, 1, 2)))
    __attribute__((access (read_only, 3, 4)));

static fwcf_compressor c_null = {
	c_init,			/* init */
	c_compress,		/* compress */
	c_decompress,		/* decompress */
	"null",			/* name */
	0			/* code */
};

static void
c_null_load(void)
{
	if (compress_register(&c_null))
		fputs("warning: cannot register compressor 'null'!\n", stderr);
}

static int
c_init(void)
{
	return (0);
}

static int
c_compress(char **dst, char *src, size_t len)
{
	if ((*dst = malloc(len)) == NULL)
		return (-1);
	memcpy(*dst, src, len);
	return (len);
}

static int
c_decompress(char *dst, size_t dstlen, char *src, size_t srclen)
{
	size_t len = MIN(srclen, dstlen);
	memmove(dst, src, len);
	return (len);
}
