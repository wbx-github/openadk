/* $MirOS: contrib/hosted/fwcf/c_zlib.c,v 1.4 2006/09/23 23:46:35 tg Exp $ */

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
#include <zlib.h>

#include "defs.h"
#include "compress.h"

__RCSID("$MirOS: contrib/hosted/fwcf/c_zlib.c,v 1.4 2006/09/23 23:46:35 tg Exp $");

static void c_zlib_load(void) __attribute__((constructor));
static int c_init(void);
static int c_compress(char **, char *, size_t)
    __attribute__((access (read_only, 2, 3)));
static int c_decompress(char *, size_t, char *, size_t)
    __attribute__((access (read_write, 1, 2)))
    __attribute__((access (read_only, 3, 4)));

static fwcf_compressor c_zlib = {
	c_init,			/* init */
	c_compress,		/* compress */
	c_decompress,		/* decompress */
	"zlib",			/* name */
	0x01			/* code */
};

static void
c_zlib_load(void)
{
	if (compress_register(&c_zlib))
		fputs("warning: cannot register compressor 'zlib'!\n", stderr);
}

static int
c_init(void)
{
	return (0);
}

static int
c_compress(char **dst, char *src, size_t len)
{
	uLongf dstlen;

	if (dst == NULL)
		return (-1);
	dstlen = compressBound(len);
	if ((*dst = malloc(dstlen)) == NULL)
		return (-1);
	return ((compress2((uint8_t *)*dst, &dstlen, (uint8_t *)src, len,
	    9) == Z_OK) ? (int)dstlen : -1);
}

static int
c_decompress(char *dst, size_t dstlen, char *src, size_t srclen)
{
	uLongf len = dstlen;

	return ((uncompress((uint8_t *)dst, &len, (uint8_t *)src,
	    srclen) == Z_OK) ? (int)len : -1);
}
