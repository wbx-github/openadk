/*
 * Copyright(C) 2009  Qi Hardware Inc.,
 * Authors: Marek Lindner <lindner_marek@yahoo.de>
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

#include <errno.h>
#include <confuse.h>
#include <unistd.h>
#include <string.h>
#include "ingenic_cfg.h"
#include "usb_boot_defines.h"

extern unsigned int total_size;

int check_dump_cfg(struct hand *h)
{
	printf("Now checking whether all configure args valid:");
	/* check PLL */
	if (h->fw_args.ext_clk > 27 || h->fw_args.ext_clk < 12) {
		printf(" EXTCLK setting invalid!\n");
		return 0;
	}
	if (h->fw_args.phm_div > 32 || h->fw_args.ext_clk < 2) {
		printf(" PHMDIV setting invalid!\n");
		return 0;
	}
	if ((h->fw_args.cpu_speed * h->fw_args.ext_clk ) % 12 != 0) {
		printf(" CPUSPEED setting invalid!\n");
		return 0;
	}

	/* check SDRAM */
	if (h->fw_args.bus_width > 1 ) {
		printf(" SDRAMWIDTH setting invalid!\n");
		return 0;
	}
	if (h->fw_args.bank_num > 1 ) {
		printf(" BANKNUM setting invalid!\n");
		return 0;
	}
	if (h->fw_args.row_addr > 13 && h->fw_args.row_addr < 11 ) {
		printf(" ROWADDR setting invalid!\n");
		return 0;
	}
	if (h->fw_args.col_addr > 13 && h->fw_args.col_addr < 11 ) {
		printf(" COLADDR setting invalid!\n");
		return 0;
	}

	/* check NAND */
	if (h->nand_ps < 2048 && h->nand_os > 16) {
		printf(" PAGESIZE or OOBSIZE setting invalid!\n");
		printf(" PAGESIZE is %d,\t OOBSIZE is %d\n",
		       h->nand_ps, h->nand_os);
		return 0;
	}
	if (h->nand_ps < 2048 && h->nand_ppb > 32) {
		printf(" PAGESIZE or PAGEPERBLOCK setting invalid!\n");
		return 0;
	}

	if (h->nand_ps > 512 && h->nand_os <= 16) {
		printf(" PAGESIZE or OOBSIZE setting invalid!\n");
		printf(" PAGESIZE is %d,\t OOBSIZE is %d\n",
		       h->nand_ps, h->nand_os);
		return 0;
	}
	if (h->nand_ps > 512 && h->nand_ppb < 64) {
		printf(" PAGESIZE or PAGEPERBLOCK setting invalid!\n");
		return 0;
	}
	printf(" YES\n");

	printf("Current device setup information:\n");
	printf("Crystal work at %dMHz, the CCLK up to %dMHz and PMH_CLK up to %dMHz\n",
		h->fw_args.ext_clk,
		(unsigned int)h->fw_args.cpu_speed * h->fw_args.ext_clk,
		((unsigned int)h->fw_args.cpu_speed * h->fw_args.ext_clk) / h->fw_args.phm_div);

	printf("SDRAM Total size is %d MB, work in %d bank and %d bit mode\n",
		total_size / 0x100000, 2 * (h->fw_args.bank_num + 1),
	       16 * (2 - h->fw_args.bus_width));

	printf("Nand page per block %d, "
	       "Nand page size %d, "
	       "ECC offset in OOB %d, "
	       "bad block offset in OOB %d, "
	       "bad block page %d, "
	       "use %d plane mode\n",
	       h->nand_ppb,
	       h->nand_ps,
	       h->nand_eccpos,
	       h->nand_bbpos,
	       h->nand_bbpage,
	       h->nand_plane);
	return 1;
}

int parse_configure(struct hand *h, char * file_path)
{
	cfg_t *cfg;
	cfg_opt_t opts[] = {
		CFG_INT("BOUDRATE", 57600, CFGF_NONE),
		CFG_INT("EXTCLK", 0, CFGF_NONE),
		CFG_INT("CPUSPEED", 0, CFGF_NONE),
		CFG_INT("PHMDIV", 0, CFGF_NONE),
		CFG_INT("USEUART", 0, CFGF_NONE),

		CFG_INT("BUSWIDTH", 0, CFGF_NONE),
		CFG_INT("BANKS", 0, CFGF_NONE),
		CFG_INT("ROWADDR", 0, CFGF_NONE),
		CFG_INT("COLADDR", 0, CFGF_NONE),

		CFG_INT("ISMOBILE", 0, CFGF_NONE),
		CFG_INT("ISBUSSHARE", 0, CFGF_NONE),
		CFG_INT("DEBUGOPS", 0, CFGF_NONE),
		CFG_INT("PINNUM", 0, CFGF_NONE),
		CFG_INT("START", 0, CFGF_NONE),
		CFG_INT("SIZE", 0, CFGF_NONE),

		CFG_INT("NAND_BUSWIDTH", 0, CFGF_NONE),
		CFG_INT("NAND_ROWCYCLES", 0, CFGF_NONE),
		CFG_INT("NAND_PAGESIZE", 0, CFGF_NONE),
		CFG_INT("NAND_PAGEPERBLOCK", 0, CFGF_NONE),
		CFG_INT("NAND_FORCEERASE", 0, CFGF_NONE),
		CFG_INT("NAND_OOBSIZE", 0, CFGF_NONE),
		CFG_INT("NAND_ECCPOS", 0, CFGF_NONE),
		CFG_INT("NAND_BADBLOCKPOS", 0, CFGF_NONE),
		CFG_INT("NAND_BADBLOCKPAGE", 0, CFGF_NONE),
		CFG_INT("NAND_PLANENUM", 0, CFGF_NONE),
		CFG_INT("NAND_BCHBIT", 0, CFGF_NONE),
		CFG_INT("NAND_WPPIN", 0, CFGF_NONE),
		CFG_INT("NAND_BLOCKPERCHIP", 0, CFGF_NONE),

		CFG_END()
	};

	if (access(file_path, F_OK)) {
		fprintf(stderr, "Error - can't read configure file %s.\n",
			file_path);
		return -1;
	}

	cfg = cfg_init(opts, 0);
	if (cfg_parse(cfg, file_path) == CFG_PARSE_ERROR)
		return -1;

	h->fw_args.boudrate = cfg_getint(cfg, "BOUDRATE");
	h->fw_args.ext_clk = cfg_getint(cfg, "EXTCLK");
	h->fw_args.cpu_speed = cfg_getint(cfg, "CPUSPEED");
	h->fw_args.phm_div = cfg_getint(cfg, "PHMDIV");
	h->fw_args.use_uart = cfg_getint(cfg, "USEUART");

	h->fw_args.bus_width = cfg_getint(cfg, "BUSWIDTH");
	h->fw_args.bank_num = cfg_getint(cfg, "BANKS");
	h->fw_args.row_addr = cfg_getint(cfg, "ROWADDR");
	h->fw_args.col_addr = cfg_getint(cfg, "COLADDR");

	h->fw_args.is_mobile = cfg_getint(cfg, "ISMOBILE");
	h->fw_args.is_busshare = cfg_getint(cfg, "ISBUSSHARE");
	h->fw_args.debug_ops = cfg_getint(cfg, "DEBUGOPS");
	h->fw_args.pin_num = cfg_getint(cfg, "PINNUM");
	h->fw_args.start = cfg_getint(cfg, "START");
	h->fw_args.size = cfg_getint(cfg, "SIZE");

	h->nand_bw = cfg_getint(cfg, "NAND_BUSWIDTH");
	h->nand_rc = cfg_getint(cfg, "NAND_ROWCYCLES");
	h->nand_ps = cfg_getint(cfg, "NAND_PAGESIZE");
	h->nand_ppb = cfg_getint(cfg, "NAND_PAGEPERBLOCK");
	h->nand_force_erase = cfg_getint(cfg, "NAND_FORCEERASE");
	h->nand_os = cfg_getint(cfg, "NAND_OOBSIZE");
	h->nand_eccpos = cfg_getint(cfg, "NAND_ECCPOS");
	h->nand_bbpos = cfg_getint(cfg, "NAND_BADBLOCKPOS");
	h->nand_bbpage = cfg_getint(cfg, "NAND_BADBLOCKPAGE");
	h->nand_plane = cfg_getint(cfg, "NAND_PLANENUM");
	h->nand_bchbit = cfg_getint(cfg, "NAND_BCHBIT");
	h->nand_wppin = cfg_getint(cfg, "NAND_WPPIN");
	h->nand_bpc = cfg_getint(cfg, "NAND_BLOCKPERCHIP");

	cfg_free(cfg);

	if (h->fw_args.bus_width == 32)
		h->fw_args.bus_width = 0;
	else
		h->fw_args.bus_width = 1;
	h->fw_args.bank_num = h->fw_args.bank_num / 4;
	h->fw_args.cpu_speed = h->fw_args.cpu_speed / h->fw_args.ext_clk;

	total_size = (unsigned int)
		(2 << (h->fw_args.row_addr + h->fw_args.col_addr - 1)) * 2
		* (h->fw_args.bank_num + 1) * 2
		* (2 - h->fw_args.bus_width);

	if (check_dump_cfg(h) < 1)
		return -1;

	return 1;
}
