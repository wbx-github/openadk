/*
 * Copyright (C) 2009 Qi Hardware Inc.,
 * Author:  Xiangfu Liu <xiangfu@sharism.cc>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 3 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA
 */

#include "target/nandflash.h"
#include "target/jz4740.h"
#include "target/usb_boot.h"
#include "usb_boot_defines.h"

#define __nand_enable()		(REG_EMC_NFCSR |= EMC_NFCSR_NFE1 | EMC_NFCSR_NFCE1)
#define __nand_disable()	(REG_EMC_NFCSR &= ~(EMC_NFCSR_NFCE1))
#define __nand_ecc_rs_encoding()	(REG_EMC_NFECR = EMC_NFECR_ECCE | EMC_NFECR_ERST | EMC_NFECR_RS | EMC_NFECR_RS_ENCODING)
#define __nand_ecc_rs_decoding()	(REG_EMC_NFECR = EMC_NFECR_ECCE | EMC_NFECR_ERST | EMC_NFECR_RS | EMC_NFECR_RS_DECODING)
#define __nand_ecc_disable()		(REG_EMC_NFECR &= ~EMC_NFECR_ECCE)
#define __nand_ecc_encode_sync()	while (!(REG_EMC_NFINTS & EMC_NFINTS_ENCF))
#define __nand_ecc_decode_sync()	while (!(REG_EMC_NFINTS & EMC_NFINTS_DECF))

#define __nand_ready()		((REG_GPIO_PXPIN(2) & 0x40000000) ? 1 : 0)
#define __nand_ecc()		(REG_EMC_NFECC & 0x00ffffff)
#define __nand_cmd(n)		(REG8(cmdport) = (n))
#define __nand_addr(n)		(REG8(addrport) = (n))
#define __nand_data8()		REG8(dataport)
#define __nand_data16()		REG16(dataport)

#define CMD_READA	0x00
#define CMD_READB	0x01
#define CMD_READC	0x50
#define CMD_ERASE_SETUP	0x60
#define CMD_ERASE	0xD0
#define CMD_READ_STATUS	0x70
#define CMD_CONFIRM	0x30
#define CMD_SEQIN	0x80
#define CMD_PGPROG	0x10
#define CMD_READID	0x90

#define OP_ERASE	0
#define OP_WRITE	1
#define OP_READ		2

#define ECC_BLOCK	512
#define PAR_SIZE	9

static volatile unsigned char *gpio_base = (volatile unsigned char *)0xb0010000;
static volatile unsigned char *emc_base = (volatile unsigned char *)0xb3010000;
static volatile unsigned char *addrport = (volatile unsigned char *)0xb8010000;
static volatile unsigned char *dataport = (volatile unsigned char *)0xb8000000;
static volatile unsigned char *cmdport = (volatile unsigned char *)0xb8008000;

static int bus, row, pagesize, oobsize, ppb;
static int bad_block_pos, bad_block_page, force_erase, ecc_pos, wp_pin;
static u8 oob_buf[256] = {0};

extern struct hand Hand;
extern u16 handshake_PKT[4];

static unsigned int EMC_CSN[4] = {
	0xb8000000,
	0xb4000000,
	0xa8000000,
	0xa4000000
};

static inline void __nand_sync(void)
{
	unsigned int timeout = 100000;
	while ((REG_GPIO_PXPIN(2) & 0x40000000) && timeout--)
		;
	while (!(REG_GPIO_PXPIN(2) & 0x40000000))
		;
}

static void select_chip(int block)
{
	int t;
	if (!Hand.nand_bpc) 
		return;

	t = (block / Hand.nand_bpc) % 4;
	addrport = (volatile unsigned char *)(EMC_CSN[t] + 0x10000);
	dataport = (volatile unsigned char *)EMC_CSN[t];
	cmdport =  (volatile unsigned char *)(EMC_CSN[t] + 0x8000);
}

static int read_oob(void *buf, u32 size, u32 pg);
static int nand_data_write8(char *buf, int count);
static int nand_data_write16(char *buf, int count);
static int nand_data_read8(char *buf, int count);
static int nand_data_read16(char *buf, int count);
static int (*write_proc)(char *, int) = NULL;
static int (*read_proc)(char *, int) = NULL;

static nand_init_gpio(void)
{
	/* modify this fun to a specifical borad
	 * this fun init those gpio use by all flash chip
	 * select the gpio function related to flash chip
	 */
	__gpio_as_nand();
}

inline void nand_enable_4740(unsigned int csn)
{
	/* modify this fun to a specifical borad
	 * this fun to enable the chip select pin csn
	 * the choosn chip can work after this fun
	 */
	__nand_enable();
}

inline void nand_disable_4740(unsigned int csn)
{
	/* modify this fun to a specifical borad
	 * this fun to enable the chip select pin csn
	 * the choosn chip can not work after this fun
	 */
	__nand_disable();
}

unsigned int nand_query_4740(u8 *id)
{
	__nand_sync();
	__nand_cmd(CMD_READID);
	__nand_addr(0);

	id[0] = __nand_data8();      /* VID */
	id[1] = __nand_data8();      /* PID */
	id[2] = __nand_data8();      /* CHIP ID */
	id[3] = __nand_data8();      /* PAGE ID */
	id[4] = __nand_data8();      /* PLANE ID */

	return 0;
}

int nand_init_4740(int bus_width, int row_cycle, int page_size, int page_per_block,
		   int bbpage,int bbpos,int force,int ep)
{
	bus = bus_width;
	row = row_cycle;
	pagesize = page_size;
	oobsize = pagesize / 32;
	ppb = page_per_block;
	bad_block_pos = bbpos;
	bad_block_page = bbpage;
	force_erase = force;
	ecc_pos = ep;
	wp_pin = Hand.nand_wppin;

	/* Initialize NAND Flash Pins */
	if (wp_pin) {
		__gpio_as_output(wp_pin);
		__gpio_disable_pull(wp_pin);
	}
	nand_init_gpio();
	select_chip(0);
	REG_EMC_SMCR1 = 0x0fff7700;      /* slow speed */
/* 	REG_EMC_SMCR1 = 0x04444400;      normal speed */
/* 	REG_EMC_SMCR1 = 0x0d221200;      fast speed */

	if (bus == 8) {
		write_proc = nand_data_write8;
		read_proc = nand_data_read8;
	} else {
		write_proc = nand_data_write16;
		read_proc = nand_data_read16;
	}

	return 0;
}

int nand_fini_4740(void)
{
	__nand_disable();
	return 0;
}

/*
 * Read oob <pagenum> pages from <startpage> page.
 * Don't skip bad block.
 * Don't use HW ECC.
 */
u32 nand_read_oob_4740(void *buf, u32 startpage, u32 pagenum)
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
	u32 pg, i;
	if (bad_block_page >= ppb) {
		/* do absolute bad block detect! */
		pg = block * ppb + 0;
		read_oob(oob_buf, oobsize, pg);
		if (oob_buf[0] != 0xff || oob_buf[1] != 0xff)
			goto bad;

		pg = block * ppb + 1;
		read_oob(oob_buf, oobsize, pg);
		if (oob_buf[0] != 0xff || oob_buf[1] != 0xff)
			goto bad;

		pg = block * ppb + ppb - 2 ;
		read_oob(oob_buf, oobsize, pg);
		if (oob_buf[0] != 0xff || oob_buf[1] != 0xff)
			goto bad;

		pg = block * ppb + ppb - 1 ;
		read_oob(oob_buf, oobsize, pg);
		if ( oob_buf[0] != 0xff || oob_buf[1] != 0xff )
			goto bad;

	} else {
		pg = block * ppb + bad_block_page;
		read_oob(oob_buf, oobsize, pg);
		if (oob_buf[bad_block_pos] != 0xff)
			goto bad;

	}

	return 0;

bad:
	serial_puts("Absolute skip a bad block\n");
	return 1;
	
}

/*
 * Read data <pagecount> pages from <startpage> page.
 * Don't skip bad block.
 * Don't use HW ECC.
 */
u32 nand_read_raw_4740(void *buf, u32 startpage, u32 pagecount, int option)
{
	u32 cnt, j;
	u32 cur_page, rowaddr;
	u8 *tmpbuf;

	tmpbuf = (u8 *)buf;

	cur_page = startpage;
	cnt = 0;
	while (cnt < pagecount) {
		select_chip(cnt / ppb);
		if ((cur_page % ppb) == 0) {
			if (nand_check_block(cur_page / ppb)) {
				cur_page += ppb; /* Bad block, set to next block  */
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
		read_proc(tmpbuf, pagesize);

		tmpbuf += pagesize;
		if (option != NO_OOB) {
			read_oob(tmpbuf, oobsize, cur_page);
			tmpbuf += oobsize;
		}

		cur_page++;
		cnt++;
	}

	return cur_page;
}

u32 nand_erase_4740(int blk_num, int sblk, int force)
{
	int j;
	u32 cur, rowaddr;

	if (wp_pin)
		__gpio_set_pin(wp_pin);

	for (cur = sblk * ppb; cur < (sblk + blk_num) * ppb; cur += ppb) {
		rowaddr = cur;
		select_chip(cur / ppb);
		if (!force) {
			if (nand_check_block(cur / ppb)) {
				blk_num += Hand.nand_plane;
				continue;
			}
		}

		__nand_cmd(CMD_ERASE_SETUP);

		for (j = 0; j < row; j++) {
			__nand_addr(rowaddr & 0xff);
			rowaddr >>= 8;
		}
		__nand_cmd(CMD_ERASE);
		__nand_sync();
		__nand_cmd(CMD_READ_STATUS);

		if (__nand_data8() & 0x01) {
			serial_puts("\nErase fail at: \t");
			serial_put_hex(cur / ppb);
			nand_mark_bad_4740(cur/ppb);
			continue;
		}
	}

	if (wp_pin)
		__gpio_clear_pin(wp_pin);

	return cur;
}

static int read_oob(void *buf, u32 size, u32 pg)
{
	u32 i, coladdr, rowaddr;

	select_chip(pg / ppb);
	if (pagesize == 512)
		coladdr = 0;
	else
		coladdr = pagesize;

	if (pagesize == 512)
		__nand_cmd(CMD_READC); /* Send READOOB command */
	else
		__nand_cmd(CMD_READA); /* Send READ0 command */

	__nand_addr(coladdr & 0xff); /* Send column address */

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
	return 0;
}

void rs_correct(unsigned char *buf, int idx, int mask)
{
	int i, j;
	unsigned short d, d1, dm;

	i = (idx * 9) >> 3;
	j = (idx * 9) & 0x7;

	i = (j == 0) ? (i - 1) : i;
	j = (j == 0) ? 7 : (j - 1);

	d = (buf[i] << 8) | buf[i - 1];

	d1 = (d >> j) & 0x1ff;
	d1 ^= mask;

	dm = ~(0x1ff << j);
	d = (d & dm) | (d1 << j);

	buf[i - 1] = d & 0xff;
	buf[i] = (d >> 8) & 0xff;
}

 /*
 * Read data <pagecount> pages from <startpage> page.
 * Skip bad block if detected.
 * HW ECC is used.
 */
u32 nand_read_4740(void *buf, u32 startpage, u32 pagecount, int option)
{
	u32 j, k;
	u32 cur_page, cur_blk, cnt, rowaddr, ecccnt;
	u8 *tmpbuf,flag = 0;
	ecccnt = pagesize / ECC_BLOCK;
	cur_page = startpage;
	cnt = 0;
	tmpbuf = buf;
	handshake_PKT[3] = 0;

	while (cnt < pagecount) {
		select_chip(cnt / ppb);
		/* If this is the first page of the block, check for bad. */
		if ((cur_page % ppb) == 0) {
			cur_blk = cur_page / ppb;
			if (nand_check_block(cur_blk)) {
				cur_page += ppb; /* Bad block, set to next block  */
				continue;
			}
		}
		/* read oob first */
		read_oob(oob_buf, oobsize, cur_page);
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

		for (j = 0; j < ecccnt; j++) {
			volatile u8 *paraddr = (volatile u8 *)EMC_NFPAR0;
			u32 stat;
			flag = 0;

			REG_EMC_NFINTS = 0x0;
			__nand_ecc_rs_decoding();
			read_proc(tmpbuf, ECC_BLOCK);
			for (k = 0; k < PAR_SIZE; k++) {
				*paraddr++ = oob_buf[ecc_pos + j*PAR_SIZE + k];
				if (oob_buf[ecc_pos + j*PAR_SIZE + k] != 0xff)
					flag = 1;
			}
			REG_EMC_NFECR |= EMC_NFECR_PRDY;
			__nand_ecc_decode_sync();
			__nand_ecc_disable();
			/* Check decoding */
			stat = REG_EMC_NFINTS;
			if (stat & EMC_NFINTS_ERR) {
				if (stat & EMC_NFINTS_UNCOR) {
					if (flag) {
						serial_puts("\nUncorrectable error occurred, Page:");
						serial_put_hex(cur_page);
						handshake_PKT[3] = 1;
					}
				} else {
					handshake_PKT[3] = 0;
					u32 errcnt = (stat & EMC_NFINTS_ERRCNT_MASK) >> EMC_NFINTS_ERRCNT_BIT;
					switch (errcnt) {
					case 4:
						rs_correct(tmpbuf, (REG_EMC_NFERR3 & EMC_NFERR_INDEX_MASK) >> EMC_NFERR_INDEX_BIT, (REG_EMC_NFERR3 & EMC_NFERR_MASK_MASK) >> EMC_NFERR_MASK_BIT);
					case 3:
						rs_correct(tmpbuf, (REG_EMC_NFERR2 & EMC_NFERR_INDEX_MASK) >> EMC_NFERR_INDEX_BIT, (REG_EMC_NFERR2 & EMC_NFERR_MASK_MASK) >> EMC_NFERR_MASK_BIT);
					case 2:
						rs_correct(tmpbuf, (REG_EMC_NFERR1 & EMC_NFERR_INDEX_MASK) >> EMC_NFERR_INDEX_BIT, (REG_EMC_NFERR1 & EMC_NFERR_MASK_MASK) >> EMC_NFERR_MASK_BIT);
					case 1:
						rs_correct(tmpbuf, (REG_EMC_NFERR0 & EMC_NFERR_INDEX_MASK) >> EMC_NFERR_INDEX_BIT, (REG_EMC_NFERR0 & EMC_NFERR_MASK_MASK) >> EMC_NFERR_MASK_BIT);
						break;
					default:
						break;
					}
				
				}
			}
			/* increment pointer */
			tmpbuf += ECC_BLOCK;
		}

		switch (option) {
		case OOB_ECC:
			for (j = 0; j < oobsize; j++)
				tmpbuf[j] = oob_buf[j];
			tmpbuf += oobsize;
			break;
		case OOB_NO_ECC:
			for (j = 0; j < ecccnt * PAR_SIZE; j++)
				oob_buf[ecc_pos + j] = 0xff;
			for (j = 0; j < oobsize; j++)
				tmpbuf[j] = oob_buf[j];
			tmpbuf += oobsize;
			break;
		case NO_OOB:
			break;
		}

		cur_page++;
		cnt++;
	}
	return cur_page;
}

u32 nand_program_4740(void *context, int spage, int pages, int option)
{
	size_t datasize;
	u32 i, j, cur, rowaddr;
	u8 *tmpbuf;
	u32 ecccnt,oobsize_sav,ecccnt_sav,eccpos_sav;
	u8 ecc_buf[256];

	datasize = pagesize;
	if (option != NO_OOB)
		datasize += oobsize;


	if (wp_pin)
		__gpio_set_pin(wp_pin);
restart:
	tmpbuf = (u8 *)context;
	ecccnt_sav = ecccnt = pagesize / ECC_BLOCK;
	oobsize_sav = oobsize;
	eccpos_sav = ecc_pos;
	i = 0;
	cur = spage;

	while (i < pages) {
		select_chip(cur / ppb);
		if (cur < 8) {
			ecccnt = 4;
			oobsize = 64;
			ecc_pos = 6;
		} else {
			ecccnt = ecccnt_sav;
			oobsize = oobsize_sav;
			ecc_pos = eccpos_sav;
		}

                /* Skip 16KB after nand_spl if pagesize=4096 */
		if ((pagesize == 4096) && (cur == 8))
			tmpbuf += 16 * 1024;

		if ((cur % ppb) == 0) {
			if (nand_check_block(cur / ppb)) {
				cur += ppb;   /*  Bad block, set to next block  */
				continue;
			}
		}

		for (j = 0; j < datasize; ++j) {
			if (tmpbuf[j] != 0xff)
				break;
		}

		if (j == datasize) {
			tmpbuf += datasize;
			++i;
			++cur;
			continue;
		}

		if (pagesize == 512)
			__nand_cmd(CMD_READA);

		__nand_cmd(CMD_SEQIN);
		__nand_addr(0);

		if (pagesize != 512)
			__nand_addr(0);

		rowaddr = cur;
		for (j = 0; j < row; j++) {
			__nand_addr(rowaddr & 0xff);
			rowaddr >>= 8;
		}

		switch (option) {
		case OOB_ECC:
			write_proc(tmpbuf, pagesize);  /* write data */
			tmpbuf += pagesize;
			write_proc((u8 *)tmpbuf, oobsize); /* write oob */
			tmpbuf += oobsize;

			break;
		case OOB_NO_ECC:          
			for (j = 0; j < ecccnt; j++) {
				volatile u8 *paraddr = (volatile u8 *)EMC_NFPAR0;
				int k;

				REG_EMC_NFINTS = 0x0;				
				__nand_ecc_rs_encoding();
				write_proc(tmpbuf, ECC_BLOCK);
				__nand_ecc_encode_sync();
				__nand_ecc_disable();

				/* Read PAR values */
				for (k = 0; k < PAR_SIZE; k++) {
					ecc_buf[j*PAR_SIZE+k] = *paraddr++;
				}
				
				tmpbuf += ECC_BLOCK;
			}
			for (j = 0; j < oobsize; j++) {
				oob_buf[j] = tmpbuf[j];
			}
			
			for (j = 0; j < ecccnt*PAR_SIZE; j++) 
				oob_buf[ecc_pos + j] = ecc_buf[j];
			write_proc((u8 *)oob_buf, oobsize);
			tmpbuf += oobsize;

			break;
		case NO_OOB: /* bin image */
			/* write out data */
			for (j = 0; j < ecccnt; j++) {
				volatile u8 *paraddr = (volatile u8 *)EMC_NFPAR0;
				int k;

				REG_EMC_NFINTS = 0x0;				
				__nand_ecc_rs_encoding();
				write_proc(tmpbuf, ECC_BLOCK);
				__nand_ecc_encode_sync();
				__nand_ecc_disable();

				/* Read PAR values */
				for (k = 0; k < PAR_SIZE; k++) {
					ecc_buf[j*PAR_SIZE+k] = *paraddr++;
				}
				
				tmpbuf += ECC_BLOCK;
			}
			
			for (j = 0; j < oobsize; j++) {
				oob_buf[j] = 0xff;
			}

			oob_buf[2] = 0;
			oob_buf[3] = 0;
			oob_buf[4] = 0;

			for (j = 0; j < ecccnt*PAR_SIZE; j++) {
				oob_buf[ecc_pos + j] = ecc_buf[j];
			}

			write_proc((u8 *)oob_buf, oobsize);
			break;
		}

		/* send program confirm command */
		__nand_cmd(CMD_PGPROG);
		__nand_sync();

		__nand_cmd(CMD_READ_STATUS);

		/* page program error */
		if (__nand_data8() & 0x01) {
			serial_puts("Skip a write fail block\n");
			nand_erase_4740(1, cur/ppb, 1);  /* force erase before */
			nand_mark_bad_4740(cur / ppb);
			spage += ppb;
			goto restart;
		}
			
		i ++;
		cur ++;
	}

	if (wp_pin)
		__gpio_clear_pin(wp_pin);

	ecccnt = ecccnt_sav;
	oobsize = oobsize_sav;
	ecc_pos = eccpos_sav;

	return cur;
}

static u32 nand_mark_bad_page(u32 page)
{
	u8 badbuf[4096 + 128];
	u32 i;

	if (wp_pin)
		__gpio_set_pin(wp_pin);
	/* all set to 0x00 */
	for (i = 0; i < pagesize + oobsize; i++)
		badbuf[i] = 0x00;

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
}


u32 nand_mark_bad_4740(int block)
{
	u32 rowaddr;

	if (bad_block_page >= ppb) {  /* mark four page! */
		rowaddr = block * ppb + 0;
		nand_mark_bad_page(rowaddr);

		rowaddr = block * ppb + 1;
		nand_mark_bad_page(rowaddr);

		rowaddr = block * ppb + ppb - 2;
		nand_mark_bad_page(rowaddr);

		rowaddr = block * ppb + ppb - 1;
		nand_mark_bad_page(rowaddr);
	} else {                        /* mark one page only */
		rowaddr = block * ppb + bad_block_page;
		nand_mark_bad_page(rowaddr);
	}

	return rowaddr;
}

static int nand_data_write8(char *buf, int count)
{
	int i;
	u8 *p = (u8 *)buf;
	for (i = 0; i < count; i++)
		__nand_data8() = *p++;
	return 0;
}

static int nand_data_write16(char *buf, int count)
{
	int i;
	u16 *p = (u16 *)buf;
	for (i = 0; i < count / 2; i++)
		__nand_data16() = *p++;
	return 0;
}

static int nand_data_read8(char *buf, int count)
{
	int i;
	u8 *p = (u8 *)buf;
	for (i = 0; i < count; i++)
		*p++ = __nand_data8();
	return 0;
}

static int nand_data_read16(char *buf, int count)
{
	int i;
	u16 *p = (u16 *)buf;
	for (i = 0; i < count / 2; i++)
		*p++ = __nand_data16();
	return 0;
}
