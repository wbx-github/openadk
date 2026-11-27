//
// Authors: Xiangfu Liu <xiangfu@sharism.cc>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version
// 3 of the License, or (at your option) any later version.
//

#include "jz4740.h"

void gpio_init_4740()
{
	__gpio_as_nand();
	__gpio_as_sdram_32bit();
        /* enable the TP4, TP5 as UART0 */
        REG_GPIO_PXSELS(2) = 0x80000000;
	__gpio_as_uart0();
	__gpio_as_lcd_18bit();
	__gpio_as_msc();

#define GPIO_LCD_CS		(2 * 32 + 21)
#define GPIO_KEYOUT_BASE	(2 * 32 + 10)
#define GPIO_KEYIN_BASE		(3 * 32 + 18)

	unsigned int i;
	for (i = 0; i < 7; i++){
		__gpio_as_input(GPIO_KEYIN_BASE + i);
		__gpio_enable_pull(GPIO_KEYIN_BASE + i);
	}

	for (i = 0; i < 8; i++) {
		__gpio_as_output(GPIO_KEYOUT_BASE + i);
		__gpio_clear_pin(GPIO_KEYOUT_BASE + i);
	}

	__gpio_as_output(GPIO_LCD_CS);
	__gpio_clear_pin(GPIO_LCD_CS);
}

void pll_init_4740()
{
	register unsigned int cfcr, plcr1;
	int n2FR[33] = {
		0, 0, 1, 2, 3, 0, 4, 0, 5, 0, 0, 0, 6, 0, 0, 0,
		7, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0,
		9
	};
	/* int div[5] = {1, 4, 4, 4, 4}; */ /* divisors of I:S:P:L:M */
	int nf, pllout2;

	cfcr = CPM_CPCCR_CLKOEN |
		(n2FR[1] << CPM_CPCCR_CDIV_BIT) | 
		(n2FR[ARG_PHM_DIV] << CPM_CPCCR_HDIV_BIT) | 
		(n2FR[ARG_PHM_DIV] << CPM_CPCCR_PDIV_BIT) |
		(n2FR[ARG_PHM_DIV] << CPM_CPCCR_MDIV_BIT) |
		(n2FR[ARG_PHM_DIV] << CPM_CPCCR_LDIV_BIT);

	pllout2 = (cfcr & CPM_CPCCR_PCS) ? ARG_CPU_SPEED : (ARG_CPU_SPEED / 2);

	/* Init UHC clock */
	REG_CPM_UHCCDR = pllout2 / 48000000 - 1;

	nf = ARG_CPU_SPEED * 2 / ARG_EXTAL;
	plcr1 = ((nf - 2) << CPM_CPPCR_PLLM_BIT) | /* FD */
		(0 << CPM_CPPCR_PLLN_BIT) |	/* RD=0, NR=2 */
		(0 << CPM_CPPCR_PLLOD_BIT) |    /* OD=0, NO=1 */
		(0x20 << CPM_CPPCR_PLLST_BIT) | /* PLL stable time */
		CPM_CPPCR_PLLEN;                /* enable PLL */          

	/* init PLL */
	REG_CPM_CPCCR = cfcr;
	REG_CPM_CPPCR = plcr1;
}

static void serial_setbaud()
{
	volatile u8* uart_lcr = (volatile u8*)(UART_BASE + OFF_LCR);
	volatile u8* uart_dlhr = (volatile u8*)(UART_BASE + OFF_DLHR);
	volatile u8* uart_dllr = (volatile u8*)(UART_BASE + OFF_DLLR);
	u32 baud_div, tmp;

	baud_div = ARG_EXTAL / 16 / ARG_UART_BAUD;
	tmp = *uart_lcr;
	tmp |= UART_LCR_DLAB;
	*uart_lcr = tmp;

	*uart_dlhr = (baud_div >> 8) & 0xff;
	*uart_dllr = baud_div & 0xff;

	tmp &= ~UART_LCR_DLAB;
	*uart_lcr = tmp;
}

void serial_init_4740(int uart)
{
	UART_BASE = UART0_BASE + uart * UART_OFF;

	volatile u8* uart_fcr = (volatile u8*)(UART_BASE + OFF_FCR);
	volatile u8* uart_lcr = (volatile u8*)(UART_BASE + OFF_LCR);
	volatile u8* uart_ier = (volatile u8*)(UART_BASE + OFF_IER);
	volatile u8* uart_sircr = (volatile u8*)(UART_BASE + OFF_SIRCR);

	/* Disable port interrupts while changing hardware */
	*uart_ier = 0;

	/* Disable UART unit function */
	*uart_fcr = ~UART_FCR_UUE;

	/* Set both receiver and transmitter in UART mode (not SIR) */
	*uart_sircr = ~(SIRCR_RSIRE | SIRCR_TSIRE);

	/* Set databits, stopbits and parity. (8-bit data, 1 stopbit, no parity) */
	*uart_lcr = UART_LCR_WLEN_8 | UART_LCR_STOP_1;

	/* Set baud rate */
	serial_setbaud();

	/* Enable UART unit, enable and clear FIFO */
	*uart_fcr = UART_FCR_UUE | UART_FCR_FE | UART_FCR_TFLS | UART_FCR_RFLS;
}

#define SDRAM_CASL		3	/* CAS latency: 2 or 3 */
// SDRAM Timings, unit: ns
#define SDRAM_TRAS		45	/* RAS# Active Time */
#define SDRAM_RCD		20	/* RAS# to CAS# Delay */
#define SDRAM_TPC		20	/* RAS# Precharge Time */
#define SDRAM_TRWL		7	/* Write Latency Time */
#define SDRAM_TREF	        15625	/* Refresh period: 4096 refresh cycles/64ms */

void sdram_init_4740()
{
	register unsigned int dmcr0, dmcr, sdmode, tmp, cpu_clk, mem_clk, ns;

	unsigned int cas_latency_sdmr[2] = {
		EMC_SDMR_CAS_2,
		EMC_SDMR_CAS_3,
	};
	unsigned int cas_latency_dmcr[2] = {
		1 << EMC_DMCR_TCL_BIT,	/* CAS latency is 2 */
		2 << EMC_DMCR_TCL_BIT	/* CAS latency is 3 */
	};

	int div[] = {1, 2, 3, 4, 6, 8, 12, 16, 24, 32};

	if (ARG_BUS_WIDTH_16 == 0xff)
		return;
	else 
		ARG_BUS_WIDTH_16 = 1;

	cpu_clk = ARG_CPU_SPEED;
	mem_clk = cpu_clk * div[__cpm_get_cdiv()] / div[__cpm_get_mdiv()];

	REG_EMC_BCR = 0;	/* Disable bus release */
	REG_EMC_RTCSR = 0;	/* Disable clock for counting */

	/* Fault DMCR value for mode register setting*/
#define SDRAM_ROW0    11
#define SDRAM_COL0     8
#define SDRAM_BANK40   0
#define SDRAM_BW16     1
	dmcr0 = ((SDRAM_ROW0-11)<<EMC_DMCR_RA_BIT) |
		((SDRAM_COL0-8)<<EMC_DMCR_CA_BIT) |
		(SDRAM_BANK40<<EMC_DMCR_BA_BIT) |
		(SDRAM_BW16<<EMC_DMCR_BW_BIT) |
		EMC_DMCR_EPIN |
		cas_latency_dmcr[((SDRAM_CASL == 3) ? 1 : 0)];

	/* Basic DMCR value */
	dmcr = ((ARG_ROW_ADDR-11)<<EMC_DMCR_RA_BIT) |
		((ARG_COL_ADDR-8)<<EMC_DMCR_CA_BIT) |
		(ARG_BANK_ADDR_2BIT<<EMC_DMCR_BA_BIT) |
		(ARG_BUS_WIDTH_16<<EMC_DMCR_BW_BIT) |
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

void nand_init_4740()
{
	REG_EMC_SMCR1 = 0x094c4400;
	REG_EMC_NFCSR |= EMC_NFCSR_NFE1 | EMC_NFCSR_NFCE1; //__nand_enable()
}
