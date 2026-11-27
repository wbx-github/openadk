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

#ifndef __CMD_H__
#define __CMD_H__

#include "usb_boot_defines.h"

#define COMMAND_NUM 31

struct ingenic_dev ingenic_dev;
struct hand hand;
struct sdram_in sdram_in;
struct nand_in nand_in;

unsigned int total_size;
unsigned char code_buf[4 * 512 * 1024];
unsigned char check_buf[4 * 512 * 1024];
unsigned char cs[16];
unsigned char ret[8];

static const char IMAGE_TYPE[][30] = {
	"with oob and ecc",
	"with oob and without ecc",
	"without oob",
};

int boot(char *stage1_path, char *stage2_path);
int init_nand_in();
int nand_read(int mode);
int nand_prog(void);
int nand_query(void);
int nand_erase(struct nand_in *nand_in);
int debug_memory(unsigned int start, unsigned int size);
int debug_gpio(unsigned char ops, unsigned char pin);
int debug_go(void);
int device_reset(int ops);
int nand_markbad(struct nand_in *nand_in);
int sdram_load_file(struct sdram_in *sdram_in, char *file_path);

#endif  /* __CMD_H__ */
