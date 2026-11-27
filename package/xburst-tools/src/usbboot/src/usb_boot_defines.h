/*
 * Copyright(C) 2009  Qi Hardware Inc.,
 * Authors: Marek Lindner <lindner_marek@yahoo.de>
 *          Xiangfu Liu <xiangfu@sharism.cc>
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

#ifndef __USB_BOOT_DEFINES_H__
#define __USB_BOOT_DEFINES_H__

#define SDRAM_SIZE ( 16 * 1024 * 1024 )
#define CODE_SIZE  ( 4 * 1024 * 1024 )
/* #define START_ADDR ( 0x80000000 + SDRAM_SIZE - CODE_SIZE ) */

#define NAND_MAX_BLK_NUM	10000000 /*((Hand.nand_pn / Hand.nand_ppb) + 1)*/
#define NAND_MAX_PAGE_NUM	1073740824	/*Hand.nand_pn */
#define NAND_SECTION_NUM	23
#define MAX_TRANSFER_SIZE	0x100000
#define MAX_LOAD_SIZE		0x3000
#define NAND_MAX_BYTE_NUM	(hand.nand_pn * hand.nand_ps)
#define MAX_DEV_NUM	16

enum CPUTYPE {
	JZ4740,
	JZ4750
};

enum USB_Boot_State {
	DISCONNECT,
	CONNECT,
	BOOT,
	UNBOOT
};

enum OPTION {
	OOB_ECC,
	OOB_NO_ECC,
	NO_OOB
};

enum NOR_OPS_TYPE {
	NOR_INIT = 0,
	NOR_QUERY,
	NOR_WRITE,
	NOR_ERASE_CHIP,
	NOR_ERASE_SECTOR
};

enum NOR_FLASH_TYPE
{
	NOR_AM29 = 0,
	NOR_SST28,
	NOR_SST39x16,
	NOR_SST39x8
};

enum NAND_OPS_TYPE {
	NAND_QUERY = 0,
	NAND_INIT,
	NAND_MARK_BAD,
	NAND_READ_OOB,
	NAND_READ_RAW,
	NAND_ERASE,
	NAND_READ,
	NAND_PROGRAM,
	NAND_READ_TO_RAM
};

enum SDRAM_OPS_TYPE {
	SDRAM_LOAD
};

enum DATA_STRUCTURE_OB {
	DS_flash_info = 0,
	DS_hand
};

struct fw_args {
	/* CPU ID */
	unsigned int  cpu_id;

	/* PLL args */
	unsigned char ext_clk;
	unsigned char cpu_speed;
	unsigned char phm_div;
	unsigned char use_uart;
	unsigned int  boudrate;

	/* SDRAM args */
	unsigned char bus_width;
	unsigned char bank_num;
	unsigned char row_addr;
	unsigned char col_addr;
	unsigned char is_mobile;
	unsigned char is_busshare;

	/* debug args */
	char debug_ops;
	unsigned char pin_num;
	unsigned int  start;
	unsigned int  size;
} __attribute__((packed));

struct hand {
	/* nand flash info */
	int pt;				/* cpu type */
	unsigned int nand_bw;		/* bus width */
	unsigned int nand_rc;		/* row cycle */
	unsigned int nand_ps;		/* page size */
	unsigned int nand_ppb;		/* page number per block */
	unsigned int nand_force_erase;
	unsigned int nand_pn;		/* page number in total */
	unsigned int nand_os;		/* oob size */
	unsigned int nand_eccpos;
	unsigned int nand_bbpage;
	unsigned int nand_bbpos;
	unsigned int nand_plane;
	unsigned int nand_bchbit;
	unsigned int nand_wppin;
	unsigned int nand_bpc;		/* block number per chip */

	struct fw_args fw_args;
} __attribute__((packed));

struct nand_in {
	unsigned char dev;
	unsigned char max_chip;
	unsigned char *buf;
	unsigned char *cs_map;
	unsigned int start;
	unsigned int length;
	unsigned int option;

	int (* check) (unsigned char *,unsigned char *,unsigned int);
};

struct nand_out {
	unsigned char *status;
};

struct sdram_in {
	unsigned char dev;
	unsigned char *buf;
	unsigned int start;
	unsigned int length;
	unsigned int option;
};

#endif	/* __USB_BOOT_DEFINES_H__ */

