/*
 * device board 
 *
 * Copyright 2009 (C) Qi Hardware Inc.,
 * Author: Xiangfu Liu <xiangfu@sharism.cc>
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

#include "target/jz4740.h"
#include "target/configs.h"

void gpio_init_4740(void)
{
	/*
	 * Initialize SDRAM pins
	 */
#if 0
	/* PORT A: D0 ~ D31 */
	REG_GPIO_PXFUNS(0) = 0xffffffff;
	REG_GPIO_PXSELC(0) = 0xffffffff;

	/* PORT B: A0 ~ A16, DCS#, RAS#, CAS#, CKE#, RDWE#, CKO#, WE0# */
	REG_GPIO_PXFUNS(1) = 0x81f9ffff;
	REG_GPIO_PXSELC(1) = 0x81f9ffff;

	/* PORT C: WE1#, WE2#, WE3# */
	REG_GPIO_PXFUNS(2) = 0x07000000;
	REG_GPIO_PXSELC(2) = 0x07000000;

	/*
	 * Initialize Static Memory Pins
	 */

	/* CS4# */
	REG_GPIO_PXFUNS(1) = 0x10000000;
	REG_GPIO_PXSELC(1) = 0x10000000;

	/*
	 * Initialize UART0 pins
	 */

	/* PORT D: TXD/RXD */
	REG_GPIO_PXFUNS(3) = 0x06000000;
	REG_GPIO_PXSELS(3) = 0x06000000;
#endif

	__gpio_as_nand();
	/*
	 * Initialize SDRAM pins
	 */
	__gpio_as_sdram_32bit();

	/*
	 * Initialize UART0 pins
	 */
	__gpio_as_uart0();
	__gpio_as_uart1();
}

void pll_init_4740(void)
{
	register unsigned int cfcr, plcr1;
	static const int n2FR[33] = {
		0, 0, 1, 2, 3, 0, 4, 0, 5, 0, 0, 0, 6, 0, 0, 0,
		7, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0,
		9
	};
	/* int div[5] = {1, 4, 4, 4, 4}; */ /* divisors of I:S:P:L:M */
	int nf, pllout2;

	cfcr = CPM_CPCCR_CLKOEN |
		(n2FR[1] << CPM_CPCCR_CDIV_BIT) | 
		(n2FR[PHM_DIV] << CPM_CPCCR_HDIV_BIT) | 
		(n2FR[PHM_DIV] << CPM_CPCCR_PDIV_BIT) |
		(n2FR[PHM_DIV] << CPM_CPCCR_MDIV_BIT) |
		(n2FR[PHM_DIV] << CPM_CPCCR_LDIV_BIT);

	pllout2 = (cfcr & CPM_CPCCR_PCS) ? CFG_CPU_SPEED : (CFG_CPU_SPEED / 2);

	/* Init UHC clock */
	REG_CPM_UHCCDR = pllout2 / 48000000 - 1;

	nf = CFG_CPU_SPEED * 2 / CFG_EXTAL;
	plcr1 = ((nf - 2) << CPM_CPPCR_PLLM_BIT) | /* FD */
		(0 << CPM_CPPCR_PLLN_BIT) |	/* RD=0, NR=2 */
		(0 << CPM_CPPCR_PLLOD_BIT) |    /* OD=0, NO=1 */
		(0x20 << CPM_CPPCR_PLLST_BIT) | /* PLL stable time */
		CPM_CPPCR_PLLEN;                /* enable PLL */          

	/* init PLL */
	REG_CPM_CPCCR = cfcr;
	REG_CPM_CPPCR = plcr1;
} 

void sdram_init_4740(void)
{
	register unsigned int dmcr0, dmcr, sdmode, tmp, cpu_clk, mem_clk, ns;

	static const unsigned int cas_latency_sdmr[2] = {
		EMC_SDMR_CAS_2,
		EMC_SDMR_CAS_3,
	};

	static const unsigned int cas_latency_dmcr[2] = {
		1 << EMC_DMCR_TCL_BIT,	/* CAS latency is 2 */
		2 << EMC_DMCR_TCL_BIT	/* CAS latency is 3 */
	};

	static const int div[] = {1, 2, 3, 4, 6, 8, 12, 16, 24, 32};

	if (SDRAM_BW16 == 0xff)
		return;

	cpu_clk = CFG_CPU_SPEED;
	mem_clk = cpu_clk * div[__cpm_get_cdiv()] / div[__cpm_get_mdiv()];

	REG_EMC_BCR = 0;	/* Disable bus release */
	REG_EMC_RTCSR = 0;	/* Disable clock for counting */

	/* Fault DMCR value for mode register setting*/
#define SDRAM_ROW0    11
#define SDRAM_COL0     8
#define SDRAM_BANK40   0

	dmcr0 = ((SDRAM_ROW0-11)<<EMC_DMCR_RA_BIT) |
		((SDRAM_COL0-8)<<EMC_DMCR_CA_BIT) |
		(SDRAM_BANK40<<EMC_DMCR_BA_BIT) |
		(SDRAM_BW16<<EMC_DMCR_BW_BIT) |
		EMC_DMCR_EPIN |
		cas_latency_dmcr[((SDRAM_CASL == 3) ? 1 : 0)];

	/* Basic DMCR value */
	dmcr = ((SDRAM_ROW-11)<<EMC_DMCR_RA_BIT) |
		((SDRAM_COL-8)<<EMC_DMCR_CA_BIT) |
		(SDRAM_BANK4<<EMC_DMCR_BA_BIT) |
		(SDRAM_BW16<<EMC_DMCR_BW_BIT) |
		EMC_DMCR_EPIN |
		cas_latency_dmcr[((SDRAM_CASL == 3) ? 1 : 0)];

	/* SDRAM timimg */
	ns = 1000000000 / mem_clk;
	tmp = SDRAM_TRAS/ns;
	if (tmp < 4) tmp = 4;
	if (tmp > 11) tmp = 11;
	dmcr |= ((tmp-4) << EMC_DMCR_TRAS_BIT);
	tmp = SDRAM_RCD/ns;
	if (tmp > 3) tmp = 3;
	dmcr |= (tmp << EMC_DMCR_RCD_BIT);
	tmp = SDRAM_TPC/ns;
	if (tmp > 7) tmp = 7;
	dmcr |= (tmp << EMC_DMCR_TPC_BIT);
	tmp = SDRAM_TRWL/ns;
	if (tmp > 3) tmp = 3;
	dmcr |= (tmp << EMC_DMCR_TRWL_BIT);
	tmp = (SDRAM_TRAS + SDRAM_TPC)/ns;
	if (tmp > 14) tmp = 14;
	dmcr |= (((tmp + 1) >> 1) << EMC_DMCR_TRC_BIT);

	/* SDRAM mode value */
	sdmode = EMC_SDMR_BT_SEQ | 
		 EMC_SDMR_OM_NORMAL |
		 EMC_SDMR_BL_4 | 
		 cas_latency_sdmr[((SDRAM_CASL == 3) ? 1 : 0)];

	/* Stage 1. Precharge all banks by writing SDMR with DMCR.MRSET=0 */
	REG_EMC_DMCR = dmcr;
	REG8(EMC_SDMR0|sdmode) = 0;

	/* Wait for precharge, > 200us */
	tmp = (cpu_clk / 1000000) * 1000;
	while (tmp--);

	/* Stage 2. Enable auto-refresh */
	REG_EMC_DMCR = dmcr | EMC_DMCR_RFSH;

	tmp = SDRAM_TREF/ns;
	tmp = tmp/64 + 1;
	if (tmp > 0xff) tmp = 0xff;
	REG_EMC_RTCOR = tmp;
	REG_EMC_RTCNT = 0;
	REG_EMC_RTCSR = EMC_RTCSR_CKS_64;	/* Divisor is 64, CKO/64 */

	/* Wait for number of auto-refresh cycles */
	tmp = (cpu_clk / 1000000) * 1000;
	while (tmp--);

 	/* Stage 3. Mode Register Set */
	REG_EMC_DMCR = dmcr0 | EMC_DMCR_RFSH | EMC_DMCR_MRSET;
	REG8(EMC_SDMR0|sdmode) = 0;

        /* Set back to basic DMCR value */
	REG_EMC_DMCR = dmcr | EMC_DMCR_RFSH | EMC_DMCR_MRSET;

	/* everything is ok now */
}

void serial_setbrg_4740(void)
{
	volatile u8 *uart_lcr = (volatile u8 *)(UART_BASE + OFF_LCR);
	volatile u8 *uart_dlhr = (volatile u8 *)(UART_BASE + OFF_DLHR);
	volatile u8 *uart_dllr = (volatile u8 *)(UART_BASE + OFF_DLLR);
	u32 baud_div, tmp;

	baud_div = CFG_EXTAL / 16 / CONFIG_BAUDRATE;
	tmp = *uart_lcr;
	tmp |= UART_LCR_DLAB;
	*uart_lcr = tmp;

	*uart_dlhr = (baud_div >> 8) & 0xff;
	*uart_dllr = baud_div & 0xff;

	tmp &= ~UART_LCR_DLAB;
	*uart_lcr = tmp;
}
