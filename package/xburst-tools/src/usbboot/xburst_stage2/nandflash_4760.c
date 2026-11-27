/*
 * Copyright (C) 2007 Ingenic Semiconductor Inc.
 * Author: Regen Huang <lhhuang@ingenic.cn>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include "target/jz4760.h"
#include "target/nandflash.h"
#include "target/usb_boot.h"
#include "target/xburst_types.h"
#include "usb_boot_defines.h"

#define USE_BCH 1
#define USE_PN  1
#define NEMC_PNCR (NEMC_BASE + 0x100)
#define NEMC_PNDR (NEMC_BASE + 0x104)
#define REG_NEMC_PNCR REG32(NEMC_PNCR)
#define REG_NEMC_PNDR REG32(NEMC_PNDR)

#define pn_enable() \
	do {\
		REG_NEMC_PNCR = 0x3;\
	}while(0)
#define pn_disable() \
	do {\
		REG_NEMC_PNCR = 0x0;\
	}while(0)

#ifdef DEBUG
#define dprintf(n...) printf(n)
#else
#define dprintf(n...)
#endif

/* for spl */
#define ECC_BLOCK0       256
#define PAR_SIZE_SPL     78
#define PAR_SIZE_SPL1   ((PAR_SIZE_SPL+1)/2)

/*
 * NAND flash definitions
 */
#define NAND_DATAPORT	0xBA000000
#define NAND_ADDRPORT   0xBA800000
#define NAND_COMMPORT   0xBA400000

#define ECC_BLOCK	512
static int par_size, par_size1;

#define CMD_READA	0x00
#define CMD_READB	0x01
#define CMD_READC	0x50
#define CMD_ERASE_SETUP	0x60
#define CMD_ERASE	0xD0
#define CMD_READ_STATUS 0x70
#define CMD_CONFIRM	0x30
#define CMD_SEQIN	0x80
#define CMD_PGPROG	0x10
#define CMD_READID	0x90

#define __nand_cmd(n)		(REG8(NAND_COMMPORT) = (n))
#define __nand_addr(n)		(REG8(NAND_ADDRPORT) = (n))
#define __nand_data8()		REG8(NAND_DATAPORT)
#define __nand_data16()		REG16(NAND_DATAPORT)

#define __nand_enable()		(REG_NEMC_NFCSR |= NEMC_NFCSR_NFE1 | NEMC_NFCSR_NFCE1)
#define __nand_disable()	(REG_NEMC_NFCSR &= ~(NEMC_NFCSR_NFCE1))

static int bus = 8, row = 2, pagesize = 512, oobsize = 16, ppb = 32;
static int eccpos = 3, bchbit = 8, par_size = 26, par_size1 = 13, forceerase = 1, wp_pin = 0;
static int oobfs = 0;            /* 1:store file system information in oob, 0:don't store */
static int oobecc = 0;           /* Whether the oob data of the binary contains ECC data? */
static int bad_block_page = 127; /* Specify the page number of badblock flag inside a block */
static u32 bad_block_pos = 0;    /* Specify the badblock flag offset inside the oob */
static u8 oob_buf[256] = {0};
extern struct hand Hand;
extern u16 handshake_PKT[4];

static inline void __nand_sync(void)
{
	unsigned int timeout = 1000;
	while ((REG_GPIO_PXPIN(0) & 0x00100000) && timeout--);
	while (!(REG_GPIO_PXPIN(0) & 0x00100000));
}

/*
 * External routines
 */
extern void flush_cache_all(void);
extern int serial_init(void);
extern void serial_puts(const char *s);
extern void sdram_init(void);
extern void pll_init(void);

static int read_oob(void *buf, u32 size, u32 pg);
static int nand_data_write8(char *buf, int count);
static int nand_data_write16(char *buf, int count);
static int nand_data_read8(char *buf, int count);
static int nand_data_read16(char *buf, int count);

static int (*write_proc)(char *, int) = NULL;
static int (*read_proc)(char *, int) = NULL;

int read_nand_spl_page(unsigned char *databuf, unsigned int pageaddr);
int program_nand_spl_page(unsigned char *databuf, unsigned int pageaddr);

/*
 * NAND flash routines
 */

static inline void nand_read_buf16(void *buf, int count)
{
	int i;
	u16 *p = (u16 *)buf;

	for (i = 0; i < count; i += 2)
		*p++ = __nand_data16();
}

static inline void nand_read_buf8(void *buf, int count)
{
	int i;
	u8 *p = (u8 *)buf;

	for (i = 0; i < count; i++)
		*p++ = __nand_data8();
}

static inline void nand_read_buf(void *buf, int count, int bw)
{
	if (bw == 8)
		nand_read_buf8(buf, count);
	else
		nand_read_buf16(buf, count);
}

inline void nand_enable_4760(unsigned int csn)
{
	//modify this fun to a specifical borad
	//this fun to enable the chip select pin csn
	//the choosn chip can work after this fun
	//dprintf("\n Enable chip select :%d",csn);
	__gpio_as_nand_8bit(1);
	__nand_enable();
}

inline void nand_disable_4760(unsigned int csn)
{
	//modify this fun to a specifical borad
	//this fun to enable the chip select pin csn
	//the choosn chip can not work after this fun
	//dprintf("\n Disable chip select :%d",csn);
	__nand_disable();
}

void udelay(unsigned long usec)
{
	volatile int i, j;

	for (i = 0; i < usec; i++) {
		for (j = 0; j < 100; j++) {
			;
		}
	}
}

unsigned int nand_query_4760(u8 *id)
{
	__nand_disable();
	__nand_enable();
#if 1
	__nand_cmd(0xff);
	__nand_sync();
#endif
	__nand_cmd(CMD_READID);
	__nand_addr(0);
	udelay(1000);
#if 1
	id[0] = __nand_data8();      //VID
	id[1] = __nand_data8();      //PID
	id[2] = __nand_data8();      //CHIP ID
	id[3] = __nand_data8();      //PAGE ID
	id[4] = __nand_data8();      //PLANE ID

	serial_put_hex(id[0]);
	serial_put_hex(id[1]);
	serial_put_hex(id[2]);
	serial_put_hex(id[3]);
	serial_put_hex(id[4]);
	
#endif

	__nand_disable();
	return 0;
}

int nand_init_4760(int bus_width, int row_cycle, int page_size, int page_per_block,
		   int bch_bit, int ecc_pos, int bad_pos, int bad_page, int force)
{
	bus = bus_width;
	row = row_cycle;
	pagesize = page_size;
	oobsize = pagesize / 32;
	ppb = page_per_block;
	bchbit = bch_bit;
	forceerase = force;
	eccpos = ecc_pos;
	bad_block_pos = bad_pos;
	bad_block_page = bad_page;
	wp_pin = Hand.nand_wppin;

	if(bchbit == 4)
		par_size = 13;
	else if(bchbit == 8)
		par_size = 26;
	else if(bchbit == 12)
		par_size =39;
	else if(bchbit == 16)
		par_size =52;
	else if(bchbit == 20)
		par_size = 65;
	else
		par_size ==78;

	par_size1 = (par_size + 1)/2;

	/* Initialize NAND Flash Pins */
	if (bus == 8) {
		REG_NEMC_SMCR1 = 0x0d444400;
		__gpio_as_nand_8bit(1);
		write_proc = nand_data_write8;
		read_proc = nand_data_read8;
	} else {
		REG_NEMC_SMCR1 = 0x0d444400 | 0x40;
		__gpio_as_nand_16bit(1);
		write_proc = nand_data_write16;
		read_proc = nand_data_read16;
	}

	if (wp_pin)
	{
		__gpio_as_output(wp_pin);
		__gpio_disable_pull(wp_pin);
	}
	__nand_enable();

       /* If ECCPOS isn't configured in config file, the initial value is 0 */
 	if (eccpos == 0) {
		eccpos = 3;
	}

#ifdef USE_BCH
	serial_puts("Use bch.\n");
#else
	serial_puts("Not use bch.\n");
#endif
#ifdef USE_PN
	serial_puts("Use PN.\n");
#else
	serial_puts("Not use PN.\n");
#endif
	return 0;
}

/*
 * Correct the error bit in ECC_BLOCK bytes data
 */
static void bch_correct(unsigned char *dat, int idx)
{
	int i, bit;  // the 'bit' of i byte is error 
	i = (idx - 1) >> 3;
	bit = (idx - 1) & 0x7;
	if (i < ECC_BLOCK)
		dat[i] ^= (1 << bit);
}

u32 nand_read_oob_4760(void *buf, u32 startpage, u32 pagenum)
{
	u32 cnt, cur_page;
	u8 *tmpbuf;

	tmpbuf = (u8 *)buf;

	cur_page = startpage;
	cnt = 0;

	while (cnt < pagenum) {
		read_oob((void *)tmpbuf, oobsize, cur_page);
		tmpbuf += oobsize;
		cur_page++;
		cnt++;
	}

	return cur_page;
}

static int nand_check_block(u32 block)
{
	u32 pg,i;
	
	if ( bad_block_page >= ppb )    //do absolute bad block detect!
	{
		pg = block * ppb + 0;
		read_oob(oob_buf, oobsize, pg);
		if ( oob_buf[0] != 0xff || oob_buf[1] != 0xff )
		{
			serial_puts("Absolute skip a bad block\n");
			serial_put_hex(block);
			return 1;
		}

		pg = block * ppb + 1;
		read_oob(oob_buf, oobsize, pg);
		if ( oob_buf[0] != 0xff || oob_buf[1] != 0xff )
		{
			serial_puts("Absolute skip a bad block\n");
			serial_put_hex(block);
			return 1;
		}

		pg = block * ppb + ppb - 2 ;
		read_oob(oob_buf, oobsize, pg);
		if ( oob_buf[0] != 0xff || oob_buf[1] != 0xff )
		{
			serial_puts("Absolute skip a bad block\n");
			serial_put_hex(block);
			return 1;
		}

		pg = block * ppb + ppb - 1 ;
		read_oob(oob_buf, oobsize, pg);
		if ( oob_buf[0] != 0xff || oob_buf[1] != 0xff )
		{
			serial_puts("Absolute skip a bad block\n");
			serial_put_hex(block);
			return 1;
		}

	}
	else
	{
		pg = block * ppb + bad_block_page;
		read_oob(oob_buf, oobsize, pg);
		if (oob_buf[bad_block_pos] != 0xff)
		{
			serial_put_hex(oob_buf[bad_block_pos]);
			serial_puts("Skip a bad block at:\n");
			serial_put_hex(block);

			return 1;
		}

	}
	return 0;
}

u32 nand_erase_4760(int blk_num, int sblk, int force)
{
	int i, j;
	u32 cur, rowaddr;

	__nand_enable();

	if (wp_pin)
		__gpio_set_pin(wp_pin);
	cur = sblk * ppb;
	for (i = 0; i < blk_num; i++) {
		rowaddr = cur;

		if (!force)	/* if set, erase anything */
			if (nand_check_block(cur/ppb))
			{
				cur += ppb;
				blk_num += Hand.nand_plane;
				continue;
			}
		
		__nand_cmd(CMD_ERASE_SETUP);

		for (j = 0; j < row; j++) {
			__nand_addr(rowaddr & 0xff);
			rowaddr >>= 8;
		}
		__nand_cmd(CMD_ERASE);
		__nand_sync();
		__nand_cmd(CMD_READ_STATUS);

		if (__nand_data8() & 0x01) 
		{
			serial_puts("Erase fail at ");
			serial_put_hex(cur / ppb);
			nand_mark_bad_4760(cur / ppb);
			cur += ppb;
			blk_num += Hand.nand_plane;
			continue;
		}
		cur += ppb;
	}

	if (wp_pin)
		__gpio_clear_pin(wp_pin);

	__nand_disable();
	return cur;
}

/*
 * Read oob
 */
static int read_oob(void *buf, unsigned int size, unsigned int pg)
{
	unsigned int i, coladdr, rowaddr;

	__nand_enable();

	if (pagesize == 512)
		coladdr = 0;
	else {
		if (bus == 8)
			coladdr = pagesize;
		else
			coladdr = pagesize / 2;
	}

	if (pagesize == 512)
		/* Send READOOB command */
		__nand_cmd(CMD_READC);
	else
		/* Send READ0 command */
		__nand_cmd(CMD_READA);

	/* Send column address */
	__nand_addr(coladdr & 0xff);
	if (pagesize != 512)
		__nand_addr(coladdr >> 8);

	/* Send page address */
	rowaddr = pg;
	for (i = 0; i < row; i++) {
		__nand_addr(rowaddr & 0xff);
		rowaddr >>= 8;
	}

	/* Send READSTART command for 2048 ps NAND */
	if (pagesize != 512)
		__nand_cmd(CMD_CONFIRM);

	/* Wait for device ready */
	__nand_sync();

	/* Read oob data */
	read_proc(buf, size);

	if (pagesize == 512)
		__nand_sync();

	__nand_disable();
	return 0;
}

/*
 * Read data <pagenum> pages from <startpage> page.
 * Don't skip bad block.
 * Don't use HW ECC.
 */
u32 nand_read_raw_4760(void *buf, u32 startpage, u32 pagenum, int option)
{
	u32 cnt, j;
	u32 cur_page, rowaddr;
	u8 *tmpbuf;

	tmpbuf = (u8 *)buf;

	cur_page = startpage;
	cnt = 0;
	while (cnt < pagenum) {
		if ((cur_page % ppb) == 0) {
			if (nand_check_block(cur_page / ppb)) {
				cur_page += ppb;   // Bad block, set to next block 
				continue;
			}
		}

		__nand_cmd(CMD_READA);
		__nand_addr(0);
		if (pagesize != 512)
			__nand_addr(0);

		rowaddr = cur_page;
		for (j = 0; j < row; j++) {
			__nand_addr(rowaddr & 0xff);
			rowaddr >>= 8;
		}

		if (pagesize != 512)
			__nand_cmd(CMD_CONFIRM);

		__nand_sync();
#ifdef USE_PN
	pn_enable();
#endif

		read_proc(tmpbuf, pagesize);

		tmpbuf += pagesize;
		if (option != NO_OOB)
		{
			read_oob(tmpbuf, oobsize, cur_page);
			tmpbuf += oobsize;
		}
#ifdef USE_PN
		pn_disable();
#endif
		cur_page++;
		cnt++;
	}

	return cur_page;
}

#ifndef CFG_NAND_BADBLOCK_PAGE
#define CFG_NAND_BADBLOCK_PAGE 0 /* NAND bad block was marked at this page in a block, starting from 0 */
#endif

/*
 * Read data <pagenum> pages from <startpage> page.
 * Skip bad block if detected.
 * HW ECC is used.
 */
u32 nand_read_4760(void *buf, u32 startpage, u32 pagenum, int option)
{
	u32 j, k;
	u32 cur_page, cur_blk, cnt, rowaddr, ecccnt;
	u8 *tmpbuf, *p, flag = 0;
	u32 oob_per_eccsize;
	u32 spl_size = 8 * 1024 / pagesize;
	ecccnt = pagesize / ECC_BLOCK;
	oob_per_eccsize = eccpos / ecccnt;

	cur_page = startpage;
	cnt = 0;

	if(startpage >= 0 && startpage < spl_size * 2)
		tmpbuf = buf + 8 * 1024;
	else
		tmpbuf = buf;

	__nand_enable();
	while (cnt < pagenum) {
		if (cur_page < spl_size * 2) {
			u32 m;
			for (m=0; (m < pagenum) && (m < spl_size); m++)
				read_nand_spl_page(buf + pagesize * m, m * 2);
			
			cur_page = ppb * 2;
			cnt = spl_size;
			continue;
		}

		/* If this is the first page of the block, check for bad. */
		if ((cur_page % ppb) == 0) {
			cur_blk = cur_page / ppb;
			if (nand_check_block(cur_blk)) {
				cur_page += ppb;   // Bad block, set to next block 
				continue;
			}
		}
		__nand_cmd(CMD_READA);

		__nand_addr(0);
		if (pagesize != 512)
			__nand_addr(0);

		rowaddr = cur_page;
		for (j = 0; j < row; j++) {
			__nand_addr(rowaddr & 0xff);
			rowaddr >>= 8;
		}

		if (pagesize != 512)
			__nand_cmd(CMD_CONFIRM);

		__nand_sync();

#ifdef USE_PN
//		pn_enable();
#endif
		/* Read data */
		read_proc((char *)tmpbuf, pagesize);

		/* read oob first */
		read_proc((char *)oob_buf, oobsize);
#ifdef USE_PN
//		pn_disable();
#endif

		for (j = 0; j < ecccnt; j++) {
			u32 stat;
			flag = 0;
			REG_BCH_INTS = 0xffffffff;

			if (cur_page >= 16384 / pagesize)
			{
				if(bchbit == 4)
					__ecc_decoding_4bit();
				else if(bchbit == 8)
					__ecc_decoding_8bit();
				else if(bchbit == 12)
					__ecc_decoding_12bit();
				else if(bchbit == 16)
					__ecc_decoding_16bit();
				else if(bchbit == 20)
					__ecc_decoding_20bit();
				else
					__ecc_decoding_24bit();
			}
			else
			{
				__ecc_decoding_24bit();
			}

			if (option != NO_OOB) 
				__ecc_cnt_dec(ECC_BLOCK*2 + oob_per_eccsize*2 + par_size);
			else
				__ecc_cnt_dec(ECC_BLOCK*2 + par_size);

			for (k = 0; k < ECC_BLOCK; k++) {
				REG_BCH_DR = tmpbuf[k];
			}
			
			if (option != NO_OOB) {
				for (k = 0; k < oob_per_eccsize; k++) {
					REG_BCH_DR = oob_buf[oob_per_eccsize * j + k];
				}
			}

			for (k = 0; k < par_size1; k++) {
				REG_BCH_DR = oob_buf[eccpos + j * par_size1 + k];
				if (oob_buf[eccpos + j * par_size1 + k] != 0xff)  //why?
					flag = 1;
			}

			/* Wait for completion */
			__ecc_decode_sync();
			__ecc_disable();
			/* Check decoding */
			stat = REG_BCH_INTS;
		
			if (stat & BCH_INTS_ERR) {
				if (stat & BCH_INTS_UNCOR) {
					if (flag)
					{
						dprintf("Uncorrectable ECC error occurred\n");
						handshake_PKT[3] = 1;
					}
				}
				else {
					handshake_PKT[3] = 0;
					unsigned int errcnt = (stat & BCH_INTS_ERRC_MASK) >> BCH_INTS_ERRC_BIT;
					switch (errcnt) {
					case 24:
						dprintf("correct 24th error\n");
						bch_correct(tmpbuf, (REG_BCH_ERR11 & BCH_ERR_INDEX_ODD_MASK) >> BCH_ERR_INDEX_ODD_BIT);
					case 23:
						bch_correct(tmpbuf, (REG_BCH_ERR11 & BCH_ERR_INDEX_EVEN_MASK) >> BCH_ERR_INDEX_EVEN_BIT);
					case 22:
						bch_correct(tmpbuf, (REG_BCH_ERR10 & BCH_ERR_INDEX_ODD_MASK) >> BCH_ERR_INDEX_ODD_BIT);
					case 21:
						bch_correct(tmpbuf, (REG_BCH_ERR10 & BCH_ERR_INDEX_EVEN_MASK) >> BCH_ERR_INDEX_EVEN_BIT);
					case 20:
						bch_correct(tmpbuf, (REG_BCH_ERR9 & BCH_ERR_INDEX_ODD_MASK) >> BCH_ERR_INDEX_ODD_BIT);
					case 19:
						bch_correct(tmpbuf, (REG_BCH_ERR9 & BCH_ERR_INDEX_EVEN_MASK) >> BCH_ERR_INDEX_EVEN_BIT);
					case 18:
						bch_correct(tmpbuf, (REG_BCH_ERR8 & BCH_ERR_INDEX_ODD_MASK) >> BCH_ERR_INDEX_ODD_BIT);
					case 17:
						bch_correct(tmpbuf, (REG_BCH_ERR8 & BCH_ERR_INDEX_EVEN_MASK) >> BCH_ERR_INDEX_EVEN_BIT);
					case 16:
						bch_correct(tmpbuf, (REG_BCH_ERR7 & BCH_ERR_INDEX_ODD_MASK) >> BCH_ERR_INDEX_ODD_BIT);
					case 15:
						bch_correct(tmpbuf, (REG_BCH_ERR7 & BCH_ERR_INDEX_EVEN_MASK) >> BCH_ERR_INDEX_EVEN_BIT);
					case 14:
						bch_correct(tmpbuf, (REG_BCH_ERR6 & BCH_ERR_INDEX_ODD_MASK) >> BCH_ERR_INDEX_ODD_BIT);
					case 13:
						bch_correct(tmpbuf, (REG_BCH_ERR6 & BCH_ERR_INDEX_EVEN_MASK) >> BCH_ERR_INDEX_EVEN_BIT);
					case 12:
						bch_correct(tmpbuf, (REG_BCH_ERR5 & BCH_ERR_INDEX_ODD_MASK) >> BCH_ERR_INDEX_ODD_BIT);
					case 11:
						bch_correct(tmpbuf, (REG_BCH_ERR5 & BCH_ERR_INDEX_EVEN_MASK) >> BCH_ERR_INDEX_EVEN_BIT);
					case 10:
						bch_correct(tmpbuf, (REG_BCH_ERR4 & BCH_ERR_INDEX_ODD_MASK) >> BCH_ERR_INDEX_ODD_BIT);
					case 9:
						bch_correct(tmpbuf, (REG_BCH_ERR4 & BCH_ERR_INDEX_EVEN_MASK) >> BCH_ERR_INDEX_EVEN_BIT);
					case 8:
						dprintf("correct 8th error\n");
						bch_correct(tmpbuf, (REG_BCH_ERR3 & BCH_ERR_INDEX_ODD_MASK) >> BCH_ERR_INDEX_ODD_BIT);
					case 7:
						dprintf("correct 7th error\n");
						bch_correct(tmpbuf, (REG_BCH_ERR3 & BCH_ERR_INDEX_EVEN_MASK) >> BCH_ERR_INDEX_EVEN_BIT);
					case 6:
						dprintf("correct 6th error\n");
						bch_correct(tmpbuf, (REG_BCH_ERR2 & BCH_ERR_INDEX_ODD_MASK) >> BCH_ERR_INDEX_ODD_BIT);
					case 5:
						dprintf("correct 5th error\n");
						bch_correct(tmpbuf, (REG_BCH_ERR2 & BCH_ERR_INDEX_EVEN_MASK) >> BCH_ERR_INDEX_EVEN_BIT);
					case 4:
						dprintf("correct 4th error\n");
						bch_correct(tmpbuf, (REG_BCH_ERR1 & BCH_ERR_INDEX_ODD_MASK) >> BCH_ERR_INDEX_ODD_BIT);
					case 3:
						dprintf("correct 3th error\n");
						bch_correct(tmpbuf, (REG_BCH_ERR1 & BCH_ERR_INDEX_EVEN_MASK) >> BCH_ERR_INDEX_EVEN_BIT);
					case 2:
						dprintf("correct 2th error\n");
						bch_correct(tmpbuf, (REG_BCH_ERR0 & BCH_ERR_INDEX_ODD_MASK) >> BCH_ERR_INDEX_ODD_BIT);
					case 1:
						dprintf("correct 1th error\n");
						bch_correct(tmpbuf, (REG_BCH_ERR0 & BCH_ERR_INDEX_EVEN_MASK) >> BCH_ERR_INDEX_EVEN_BIT);
					break;
					default:
						dprintf("no error\n");
						break;
					}
				}
			}
			/* increment pointer */
			tmpbuf += ECC_BLOCK;
		}

		switch (option)
		{
		case	OOB_ECC:
			for (j = 0; j < oobsize; j++)
				tmpbuf[j] = oob_buf[j];
			tmpbuf += oobsize;
			break;
		case	OOB_NO_ECC:
			for (j = 0; j < par_size1 * ecccnt; j++)
				oob_buf[eccpos + j] = 0xff;
			for (j = 0; j < oobsize; j++)
				tmpbuf[j] = oob_buf[j];
			tmpbuf += oobsize;
			break;
		case	NO_OOB:
			break;
		}

		cur_page++;
		cnt++;
	}

	__nand_disable();

	return cur_page;
}

int read_nand_spl_page(unsigned char *databuf, unsigned int pageaddr)
{
	unsigned int i, j;
	unsigned int rowaddr, ecccnt;
	u8 *tmpbuf;
	char eccbuf[1024];

	for(i=0; i<1024; i++)
		eccbuf[i] = 0xff;

	/* read oob first */
	__nand_enable();

	ecccnt = pagesize / ECC_BLOCK0;
	__nand_cmd(CMD_READA);

	__nand_addr(0);
	if (pagesize != 512)
		__nand_addr(0);

	rowaddr = pageaddr+1; //??

	for (i = 0; i < row; i++) {
		__nand_addr(rowaddr & 0xff);
		rowaddr >>= 8;
	}

	if (pagesize != 512)
		__nand_cmd(CMD_CONFIRM);

	__nand_sync();

#ifdef USE_PN
	pn_enable();
#endif
	/* Read ecc */
	read_proc(eccbuf, pagesize/ECC_BLOCK0*PAR_SIZE_SPL1);

#ifdef USE_PN
	pn_disable();
#endif

	__nand_disable();

	/* read data */
	__nand_enable();

	ecccnt = pagesize / ECC_BLOCK0;
	
	__nand_cmd(CMD_READA);

	__nand_addr(0);
	if (pagesize != 512)
		__nand_addr(0);

	rowaddr = pageaddr;

	for (i = 0; i < row; i++) {
		__nand_addr(rowaddr & 0xff);
		rowaddr >>= 8;
	}

	if (pagesize != 512)
		__nand_cmd(CMD_CONFIRM);

	__nand_sync();

#ifdef USE_EFNAND
	__nand_cmd(CMD_READ_STATUS);
	
	if (__nand_data8() & 0x01) { /* page program error */
		__nand_disable();

		return 1;
	} 
	__nand_cmd(CMD_READA);
#endif

	tmpbuf = (u8 *)databuf;
	for(i=0; i<pagesize; i++)
		tmpbuf[i] = 0xff;

	for (i = 0; i < ecccnt; i++) {
		unsigned int stat;
	
#ifdef USE_PN
		if (!(((pageaddr % 64) == 0) && (i == 0)))
			pn_enable();
		else
			dprintf("don't use pn. pageaddr=%d ecccnt=%d\n", pageaddr,i);
#endif
		/* Read data */
		read_proc((char *)tmpbuf, ECC_BLOCK0);
#ifdef USE_PN
		pn_disable();
#endif

#ifdef USE_BCH
		REG_BCH_INTS = 0xffffffff;

		__ecc_decoding_24bit();

		__ecc_cnt_dec(2 * ECC_BLOCK0 + PAR_SIZE_SPL);

		for (j = 0; j < ECC_BLOCK0; j++) {//if(i==1)serial_put_hex(tmpbuf[j]);
			REG_BCH_DR = tmpbuf[j];
		}

                /* assume parities be wrote to data register not parity register */ 
		for (j = 0; j < PAR_SIZE_SPL1; j++) {
			REG_BCH_DR = eccbuf[i*PAR_SIZE_SPL1 + j];
		}
		
		/* Wait for completion */
		__ecc_decode_sync();
		
		__ecc_disable();

		/* Check decoding */
		stat = REG_BCH_INTS;

		if (stat & BCH_INTS_ERR) {
			if (stat & BCH_INTS_UNCOR) {
				serial_puts("ecc Uncorrectable ECC error occurred __spl__\n");
				serial_put_hex(i);
			}
			else {
				unsigned int errcnt = (stat & BCH_INTS_ERRC_MASK) >> BCH_INTS_ERRC_BIT;
				switch (errcnt) {
				case 24:
					dprintf("correct 24th error\n");
					bch_correct(tmpbuf, (REG_BCH_ERR11 & BCH_ERR_INDEX_ODD_MASK) >> BCH_ERR_INDEX_ODD_BIT);
				case 23:
					bch_correct(tmpbuf, (REG_BCH_ERR11 & BCH_ERR_INDEX_EVEN_MASK) >> BCH_ERR_INDEX_EVEN_BIT);
				case 22:
					bch_correct(tmpbuf, (REG_BCH_ERR10 & BCH_ERR_INDEX_ODD_MASK) >> BCH_ERR_INDEX_ODD_BIT);
				case 21:
					bch_correct(tmpbuf, (REG_BCH_ERR10 & BCH_ERR_INDEX_EVEN_MASK) >> BCH_ERR_INDEX_EVEN_BIT);
				case 20:
					bch_correct(tmpbuf, (REG_BCH_ERR9 & BCH_ERR_INDEX_ODD_MASK) >> BCH_ERR_INDEX_ODD_BIT);
				case 19:
					bch_correct(tmpbuf, (REG_BCH_ERR9 & BCH_ERR_INDEX_EVEN_MASK) >> BCH_ERR_INDEX_EVEN_BIT);
				case 18:
					bch_correct(tmpbuf, (REG_BCH_ERR8 & BCH_ERR_INDEX_ODD_MASK) >> BCH_ERR_INDEX_ODD_BIT);
				case 17:
					bch_correct(tmpbuf, (REG_BCH_ERR8 & BCH_ERR_INDEX_EVEN_MASK) >> BCH_ERR_INDEX_EVEN_BIT);
				case 16:
					bch_correct(tmpbuf, (REG_BCH_ERR7 & BCH_ERR_INDEX_ODD_MASK) >> BCH_ERR_INDEX_ODD_BIT);
				case 15:
					bch_correct(tmpbuf, (REG_BCH_ERR7 & BCH_ERR_INDEX_EVEN_MASK) >> BCH_ERR_INDEX_EVEN_BIT);
				case 14:
					bch_correct(tmpbuf, (REG_BCH_ERR6 & BCH_ERR_INDEX_ODD_MASK) >> BCH_ERR_INDEX_ODD_BIT);
				case 13:
					bch_correct(tmpbuf, (REG_BCH_ERR6 & BCH_ERR_INDEX_EVEN_MASK) >> BCH_ERR_INDEX_EVEN_BIT);
				case 12:
					bch_correct(tmpbuf, (REG_BCH_ERR5 & BCH_ERR_INDEX_ODD_MASK) >> BCH_ERR_INDEX_ODD_BIT);
				case 11:
					bch_correct(tmpbuf, (REG_BCH_ERR5 & BCH_ERR_INDEX_EVEN_MASK) >> BCH_ERR_INDEX_EVEN_BIT);
				case 10:
					bch_correct(tmpbuf, (REG_BCH_ERR4 & BCH_ERR_INDEX_ODD_MASK) >> BCH_ERR_INDEX_ODD_BIT);
				case 9:
					bch_correct(tmpbuf, (REG_BCH_ERR4 & BCH_ERR_INDEX_EVEN_MASK) >> BCH_ERR_INDEX_EVEN_BIT);
				case 8:
					dprintf("correct 8th error\n");
					bch_correct(tmpbuf, (REG_BCH_ERR3 & BCH_ERR_INDEX_ODD_MASK) >> BCH_ERR_INDEX_ODD_BIT);
				case 7:
					dprintf("correct 7th error\n");
					bch_correct(tmpbuf, (REG_BCH_ERR3 & BCH_ERR_INDEX_EVEN_MASK) >> BCH_ERR_INDEX_EVEN_BIT);
				case 6:
					dprintf("correct 6th error\n");
					bch_correct(tmpbuf, (REG_BCH_ERR2 & BCH_ERR_INDEX_ODD_MASK) >> BCH_ERR_INDEX_ODD_BIT);
				case 5:
					dprintf("correct 5th error\n");
					bch_correct(tmpbuf, (REG_BCH_ERR2 & BCH_ERR_INDEX_EVEN_MASK) >> BCH_ERR_INDEX_EVEN_BIT);
				case 4:
					dprintf("correct 4th error\n");
					bch_correct(tmpbuf, (REG_BCH_ERR1 & BCH_ERR_INDEX_ODD_MASK) >> BCH_ERR_INDEX_ODD_BIT);
				case 3:
					dprintf("correct 3th error\n");
					bch_correct(tmpbuf, (REG_BCH_ERR1 & BCH_ERR_INDEX_EVEN_MASK) >> BCH_ERR_INDEX_EVEN_BIT);
				case 2:
					dprintf("correct 2th error\n");
					bch_correct(tmpbuf, (REG_BCH_ERR0 & BCH_ERR_INDEX_ODD_MASK) >> BCH_ERR_INDEX_ODD_BIT);
				case 1:
					dprintf("correct 1th error\n");
					bch_correct(tmpbuf, (REG_BCH_ERR0 & BCH_ERR_INDEX_EVEN_MASK) >> BCH_ERR_INDEX_EVEN_BIT);
					break;
				default:
					dprintf("no error\n");
					break;
				}
			}
		}
#endif
		/* increment pointer */
		tmpbuf += ECC_BLOCK0;
	}

	__nand_disable();

	return 0;
}

u32 nand_program_4760(void *context, int spage, int pages, int option)
{
	u32 i, j, cur_page, cur_blk, rowaddr;
	u8 *tmpbuf;
	u32 ecccnt;
	u8 ecc_buf[1024], oob_buf[512];
	u32 oob_per_eccsize;
	int spl_size = 8 * 1024 / pagesize;

	if (wp_pin)
		__gpio_set_pin(wp_pin);
restart:
	tmpbuf = (u8 *)context;
	ecccnt = pagesize / ECC_BLOCK;
	oob_per_eccsize = eccpos / ecccnt;

	i = 0;
	cur_page = spage;
	
	while (i < pages) {
		if (cur_page == 0) {
			int k;
			for(k = 0; k < spl_size; k++) {
				program_nand_spl_page(context + pagesize * k, k * 2);
			}
#if 0
			for(k = 0; k < spl_size; k++) {
				program_nand_spl_page(context + pagesize * k, k * 2 + ppb );
			}
#endif
			tmpbuf += pagesize * spl_size;
			cur_page = 2 * ppb;
			i += spl_size;
			continue;
		}

		if ((cur_page % ppb) == 0) { /* First page of block, test BAD. */
			if (nand_check_block(cur_page / ppb)) {
				cur_page += ppb;   /* Bad block, set to next block */
				continue;
			}
		}

		if ( option != NO_OOB )      //if NO_OOB do not perform vaild check!
		{
			for ( j = 0 ; j < pagesize + oobsize; j++)
			{
				if (tmpbuf[j] != 0xff)
					break;
			}
			if ( j == oobsize + pagesize ) 
			{
				tmpbuf += (pagesize + oobsize) ;
				i ++;
				cur_page ++;
				continue;
			}
		}

		__nand_enable();
		__nand_sync();

		if (pagesize == 512)
			__nand_cmd(CMD_READA);

		__nand_cmd(CMD_SEQIN);
		__nand_addr(0);

		if (pagesize != 512)
			__nand_addr(0);

		rowaddr = cur_page;
		for (j = 0; j < row; j++) {
			__nand_addr(rowaddr & 0xff);
			rowaddr >>= 8;
		}

		/* write out data */
		for (j = 0; j < ecccnt; j++) {
			volatile u8 *paraddr;
			int k;

			paraddr = (volatile u8 *)BCH_PAR0;

			REG_BCH_INTS = 0xffffffff;
			if(bchbit == 4)
				__ecc_encoding_4bit();
			else if(bchbit == 8)
				__ecc_encoding_8bit();
			else if(bchbit == 12)
				__ecc_encoding_12bit();
			else if(bchbit == 16)
				__ecc_encoding_16bit();
			else if(bchbit == 20)
				__ecc_encoding_20bit();
			else
				__ecc_encoding_24bit();
					
			/* Set BCHCNT.DEC_COUNT to data block size in bytes */
			if (option != NO_OOB)
				__ecc_cnt_enc((ECC_BLOCK + oob_per_eccsize) * 2);
			else
				__ecc_cnt_enc(ECC_BLOCK * 2);
			
			/* Write data in data area to BCH */
			for (k = 0; k < ECC_BLOCK; k++) {
				REG_BCH_DR = tmpbuf[ECC_BLOCK * j + k];
			}
			
			/* Write file system information in oob area to BCH */
			if (option != NO_OOB) 
			{
				if(j == 0){
					REG_BCH_DR = 0xff;
					REG_BCH_DR = 0xff;
					for(k = 2; k < oob_per_eccsize; k++)
						REG_BCH_DR = tmpbuf[pagesize + k];
				} else {
					for (k = 0; k < oob_per_eccsize; k++) {
						REG_BCH_DR = tmpbuf[pagesize + oob_per_eccsize * j + k];
					}
				}
			}
			
			__ecc_encode_sync();
			__ecc_disable();
					
			/* Read PAR values */
			for (k = 0; k < par_size1; k++) {
				ecc_buf[j * par_size1 + k] = *paraddr++;
			}
#ifdef USE_PN
//			pn_enable();
#endif		
			write_proc((char *)&tmpbuf[ECC_BLOCK * j], ECC_BLOCK);
#ifdef USE_PN
//			pn_disable();
#endif
		}

		for(j=0; j<oobsize; j++)
			oob_buf[j] = 0xff;
		switch (option)
		{
		case OOB_ECC:
		case OOB_NO_ECC:          
			for (j = 2; j < eccpos; j++) {
				oob_buf[j] = tmpbuf[pagesize + j];
			}
			for (j = 0; j < ecccnt * par_size1; j++) {
				oob_buf[eccpos + j] = ecc_buf[j];
			}
			tmpbuf += pagesize + oobsize;
			break;
		case NO_OOB:              //bin image
			for (j = 0; j < ecccnt * par_size1; j++) {
				oob_buf[eccpos + j] = ecc_buf[j];
			}
			tmpbuf += pagesize;
			break;
		}

#ifdef USE_PN
//			pn_enable();
#endif	
		/* write out oob buffer */
		write_proc((u8 *)oob_buf, oobsize);

#ifdef USE_PN
#ifndef USE_STATUS_PORT
//		pn_disable();
#endif
#endif
		/* send program confirm command */
		__nand_cmd(CMD_PGPROG);
		__nand_sync();

		__nand_cmd(CMD_READ_STATUS);
		__nand_sync();

		if (__nand_data8() & 0x01)  /* page program error */
		{
			serial_puts("Skip a write fail block\n");
			nand_erase_4760( 1, cur_page/ppb, 1);  //force erase before
			nand_mark_bad_4760(cur_page/ppb);
			spage += ppb;
			goto restart;
		}
		__nand_disable();

		i++;
		cur_page++;
	}

	if (wp_pin)
		__gpio_clear_pin(wp_pin);

	return cur_page;
}

int program_nand_spl_page(unsigned char *databuf, unsigned int pageaddr)
{
	int i, j, ecccnt;
	char *tmpbuf;
	char ecc_buf[1024];  // need 39*16 bytes at least for 24bit BCH
	unsigned int rowaddr;

	for(i=0; i<1024; i++)
		ecc_buf[i] = 0xff;
  
	__nand_enable();

	tmpbuf = (char *)databuf;

	ecccnt = pagesize / ECC_BLOCK0;

	if (pagesize == 512)
		__nand_cmd(CMD_READA);

	__nand_cmd(CMD_SEQIN);

	/* write out col addr */
	__nand_addr(0);
	if (pagesize != 512)
		__nand_addr(0);

	rowaddr = pageaddr;
	/* write out row addr */
	for (i = 0; i < row; i++) {
		__nand_addr(rowaddr & 0xff);
		rowaddr >>= 8;
	}
	
	/* write out data */

	for (i = 0; i < ecccnt; i++) {
#ifdef USE_BCH
		volatile char *paraddr = (volatile char *)BCH_PAR0;
		
		REG_BCH_INTS = 0xffffffff;

		__ecc_encoding_24bit();

                /* Set BCHCNT.DEC_COUNT to data block size in bytes */
		__ecc_cnt_enc(2 * ECC_BLOCK0);

		for (j = 0; j < ECC_BLOCK0; j++) {
			REG_BCH_DR = tmpbuf[j];
		}

		__ecc_encode_sync();
		__ecc_disable();
			
		/* Read PAR values for 256 bytes from BCH_PARn to ecc_buf */
		for (j=0;j<PAR_SIZE_SPL1;j++) {
			ecc_buf[j + PAR_SIZE_SPL1 * i] = *paraddr++;
		}
#endif
#ifdef MAKE_ERROR
		char tmpbuf0[ECC_BLOCK0];
		u8 k, n_err;
		u16 err_bit;

		memcpy(tmpbuf0, tmpbuf, ECC_BLOCK0);
		n_err = 1 + random() % 24; // 1 ~ 24
		dprintf("generate %d error bits.\n",n_err);
		/* generate n_err error bits */
		for(k = 0; k < n_err; k++) {
			err_bit = random() % (256*8);
			dprintf("err_bit=%04x in databuf[%03d]=0x%x \n",err_bit,err_bit / 8,tmpbuf0[(err_bit / 8)]);
			tmpbuf0[(err_bit / 8)] ^= 1 << (err_bit % 8);
			dprintf("       error databuf[%03d]= 0x%x \n",err_bit / 8,databuf[(err_bit / 8)]);
		}
#endif

#ifdef USE_PN
		if (!(((pageaddr % 64) == 0) && (i == 0)))
			pn_enable();
		else
			dprintf("don't use pn. pageaddr=%d ecccnt=%d\n", pageaddr,i);
#endif

                /* write ECC_BLOCK0 bytes to nand */
#ifdef MAKE_ERROR
		write_proc((char *)tmpbuf0, ECC_BLOCK0);
#else
		write_proc((char *)tmpbuf, ECC_BLOCK0);
#endif

#ifdef USE_PN
#ifndef USE_STATUS_PORT
		pn_disable();
#endif
#endif
		tmpbuf += ECC_BLOCK0;
	}

	/* send program confirm command */
	__nand_cmd(CMD_PGPROG);
	dprintf("%s %d \n", __FUNCTION__, __LINE__);
	__nand_sync();
	dprintf("%s %d \n", __FUNCTION__, __LINE__);

#if 1
	__nand_cmd(CMD_READ_STATUS);
	dprintf("%s %d \n", __FUNCTION__, __LINE__);
	u8 status;
#ifdef USE_STATUS_PORT
	status = __nand_status();
#else
	status = __nand_data8();
#endif
	if (status & 0x01) {
		__nand_disable();
		return 1;
	}
	else {
		__nand_disable();
	}
	dprintf("%s %d \n", __FUNCTION__, __LINE__);
	/* -----program ecc----- */
	__nand_enable();
#endif
	if (pagesize == 512)
		__nand_cmd(CMD_READA);

	__nand_cmd(CMD_SEQIN);

	/* write out col addr */
	__nand_addr(0);
	if (pagesize != 512)
		__nand_addr(0);

	rowaddr = pageaddr + 1;
	/* write out row addr */
	for (i = 0; i < row; i++) {
		__nand_addr(rowaddr & 0xff);
		rowaddr >>= 8;
	}

#ifdef USE_PN
#ifdef PN_ADD_DELAY
	udelay(1000);
	dprintf("delay should be add for pn.\n");
#endif
#endif

#ifdef USE_PN
	pn_enable();
#endif
	dprintf("%s %d \n", __FUNCTION__, __LINE__);
	write_proc(ecc_buf, pagesize/ECC_BLOCK0*PAR_SIZE_SPL1);

#ifdef USE_PN
	pn_disable();
#endif

	/* send program confirm command */
	__nand_cmd(CMD_PGPROG);
	dprintf("%s %d \n", __FUNCTION__, __LINE__);
	__nand_sync();
	dprintf("%s %d \n", __FUNCTION__, __LINE__);
	__nand_cmd(CMD_READ_STATUS);

	if (__nand_data8() & 0x01) { /* page program error */
		__nand_disable();
		return 1;
	}
	else {
		__nand_disable();
		return 0;
	}
}

// be careful
static u32 nand_mark_bad_page(u32 page)
{
#if 1
	u8 badbuf[4096 + 128];
	u32 i;

	if (wp_pin)
		__gpio_set_pin(wp_pin);
	for (i = 0; i < pagesize + oobsize; i++)
		badbuf[i] = 0x00;
	//all set to 0x00

	__nand_cmd(CMD_READA);
	__nand_cmd(CMD_SEQIN);

	__nand_addr(0);
	if (pagesize != 512)
		__nand_addr(0);
	for (i = 0; i < row; i++) {
		__nand_addr(page & 0xff);
		page >>= 8;
	}

	write_proc((char *)badbuf, pagesize + oobsize);
	__nand_cmd(CMD_PGPROG);
	__nand_sync();

	if (wp_pin)
		__gpio_clear_pin(wp_pin);
	return page;
#endif
}

u32 nand_mark_bad_4760(int block)
{
	u32 rowaddr;

	if ( bad_block_page >= ppb )    //absolute bad block mark!
	{                               //mark four page!
		rowaddr = block * ppb + 0;
		nand_mark_bad_page(rowaddr);

		rowaddr = block * ppb + 1;
		nand_mark_bad_page(rowaddr);

		rowaddr = block * ppb + ppb - 2;
		nand_mark_bad_page(rowaddr);

		rowaddr = block * ppb + ppb - 1;
		nand_mark_bad_page(rowaddr);
	}
	else                            //mark one page only
	{
		rowaddr = block * ppb + bad_block_page;
		nand_mark_bad_page(rowaddr);
	}

	return rowaddr;
}

static int nand_data_write8(char *buf, int count)
{
	int i;
	u8 *p = (u8 *)buf;
	for (i=0;i<count;i++)
		__nand_data8() = *p++;
	return 0;
}

static int nand_data_write16(char *buf, int count)
{
	int i;
	u16 *p = (u16 *)buf;
	for (i=0;i<count/2;i++)
		__nand_data16() = *p++;
	return 0;
}

static int nand_data_read8(char *buf, int count)
{
	int i;
	u8 *p = (u8 *)buf;
	for (i=0;i<count;i++)
		*p++ = __nand_data8();
	return 0;
}

static int nand_data_read16(char *buf, int count)
{
	int i;
	u16 *p = (u16 *)buf;
	for (i=0;i<count/2;i++)
		*p++ = __nand_data16();
	return 0;
}
