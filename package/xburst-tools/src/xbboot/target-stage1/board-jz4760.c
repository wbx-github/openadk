/*
 * board.c
 *
 * Board init routines.
 *
 * Copyright (C) 2006 Ingenic Semiconductor Inc.
 *
 */
#include "common.h"
#include "jz4760.h"
#include "board-jz4760.h"

void nand_init_4760()
{
	REG_NEMC_NFCSR |= NEMC_NFCSR_NFE1 | NEMC_NFCSR_NFCE1;
}

void cpm_start_all_4760()
{
	__cpm_start_all();
}

/*
 * SD0 ~ SD7, SA0 ~ SA5, CS2#, RD#, WR#, WAIT#	
 */
#define __gpio_as_nor()							\
do {								        \
	/* SD0 ~ SD7, RD#, WR#, CS2#, WAIT# */				\
	REG_GPIO_PXFUNS(0) = 0x084300ff;				\
	REG_GPIO_PXTRGC(0) = 0x084300ff;				\
	REG_GPIO_PXSELC(0) = 0x084300ff;				\
	REG_GPIO_PXPES(0) = 0x084300ff;					\
	/* SA0 ~ SA5 */							\
	REG_GPIO_PXFUNS(1) = 0x0000003f;				\
	REG_GPIO_PXTRGC(1) = 0x0000003f;				\
	REG_GPIO_PXSELC(1) = 0x0000003f;				\
	REG_GPIO_PXPES(1) = 0x0000003f;					\
} while (0)

void gpio_init_4760()
{
	__gpio_as_uart0();
	__gpio_as_uart1();
	__gpio_as_uart2();
	__gpio_as_uart3();
	
#ifdef CONFIG_FPGA // if the delay isn't added on FPGA, the first line that uart to print will not be normal. 
	__gpio_as_nor();
	{
		volatile int i=1000;
		while(i--);
	}
#endif
	__gpio_as_nand_16bit(1);
}

#define MHZ (1000 * 1000)
static inline unsigned int pll_calc_m_n_od(unsigned int speed, unsigned int xtal)
{
	const int pll_m_max = 0x7f, pll_m_min = 4;
	const int pll_n_max = 0x0f, pll_n_min = 2;

	int od[] = {1, 2, 4, 8};
	int min_od = 0;

	unsigned int plcr_m_n_od = 0;
	unsigned int distance;
	unsigned int tmp, raw;

	int i, j, k;
	int m, n;

	distance = 0xFFFFFFFF;

	for (i = 0; i < sizeof (od) / sizeof(int); i++) {
		/* Limit: 500MHZ <= CLK_OUT * OD <= 1500MHZ */
//		if (min_od != 0)
//			break;
		if ((speed * od[i]) < 500 * MHZ || (speed * od[i]) > 1500 * MHZ)
			continue;
		for (k = pll_n_min; k <= pll_n_max; k++) {
			n = k;
			
			/* Limit: 1MHZ <= XIN/N <= 50MHZ */
			if ((xtal / n) < (1 * MHZ))
				break;
			if ((xtal / n) > (15 * MHZ))
				continue;

			for (j = pll_m_min; j <= pll_m_max; j++) {
				m = j*2;

				raw = xtal * m / n;
				tmp = raw / od[i];

				tmp = (tmp > speed) ? (tmp - speed) : (speed - tmp);

				if (tmp < distance) {
					distance = tmp;
					
					plcr_m_n_od = (j << CPM_CPPCR_PLLM_BIT) 
						| (k << CPM_CPPCR_PLLN_BIT)
						| (i << CPM_CPPCR_PLLOD_BIT);

					if (!distance) {	/* Match. */
//						serial_puts("right value");
						return plcr_m_n_od;
					}
				}
			}
			min_od = od[i];
		}
	}
	return plcr_m_n_od;
}

/* TODO: pll_init() need modification. */
void pll_init_4760()
{
	register unsigned int cfcr, plcr1;
	int n2FR[9] = {
		0, 0, 1, 2, 3, 0, 4, 0, 5
	};

	/** divisors, 
	 *  for jz4760 ,I:H:H2:P:M:S.
	 *  DIV should be one of [1, 2, 3, 4, 6, 8] like:
	 *  div[6] = {1, 2, 2, 2, 2, 2};
	 *  div[6] = {1, 3, 6, 6, 6, 6};
	 */
	int div[6] = {1, 2, 4, 4, 4, 4};

	cfcr = 	CPM_CPCCR_PCS |
		(n2FR[div[0]] << CPM_CPCCR_CDIV_BIT) | 
		(n2FR[div[1]] << CPM_CPCCR_HDIV_BIT) | 
		(n2FR[div[2]] << CPM_CPCCR_H2DIV_BIT) |
		(n2FR[div[3]] << CPM_CPCCR_PDIV_BIT) |
		(n2FR[div[4]] << CPM_CPCCR_MDIV_BIT) |
		(n2FR[div[5]] << CPM_CPCCR_SDIV_BIT);

	if (CFG_EXTAL > 16000000)
		cfcr |= CPM_CPCCR_ECS;
	else
		cfcr &= ~CPM_CPCCR_ECS;

	/* set CPM_CPCCR_MEM only for ddr1 or ddr2 */
#if defined(CONFIG_DDRC) && (defined(CONFIG_SDRAM_DDR1) || defined(CONFIG_SDRAM_DDR2))
	cfcr |= CPM_CPCCR_MEM;
#else
	cfcr &= ~CPM_CPCCR_MEM;
#endif
	cfcr |= CPM_CPCCR_CE;

	plcr1 = pll_calc_m_n_od(CFG_CPU_SPEED, CFG_EXTAL);
	plcr1 |= (0x20 << CPM_CPPCR_PLLST_BIT)	/* PLL stable time */
		| CPM_CPPCR_PLLEN;             /* enable PLL */

	/* init PLL */
	REG_CPM_CPCCR = cfcr;
	REG_CPM_CPPCR = plcr1;
	
	while(!(REG_CPM_CPPSR & (1 << 29))); 

#ifdef DEBUG
	serial_puts("REG_CPM_CPCCR = ");
	serial_put_hex(REG_CPM_CPCCR);
	serial_puts("REG_CPM_CPPCR = ");
	serial_put_hex(REG_CPM_CPPCR);
#endif
}

#if (defined(CONFIG_SDRAM_MDDR)||defined(CONFIG_SDRAM_DDR1)||defined(CONFIG_SDRAM_DDR2))
void jzmemset(void *dest,int ch,int len)
{
	unsigned int *d = (unsigned int *)dest;
	int i;
	int wd;

	wd = (ch << 24) | (ch << 16) | (ch << 8) | ch;

	for(i = 0;i < len / 32;i++)
	{
		*d++ = wd;
		*d++ = wd;
		*d++ = wd;
		*d++ = wd;
		*d++ = wd;
		*d++ = wd;
		*d++ = wd;
		*d++ = wd;
	}
}

unsigned int gen_verify_data(unsigned int i)
{
	i = i/4*0x11111111;
	return i;
	//return 0xffffffff;
} 

int initdram(int board_type)
{
	u32 ddr_cfg;
	u32 rows, cols, dw, banks;
	unsigned long size;
	ddr_cfg = REG_DDRC_CFG;
	rows = 12 + ((ddr_cfg & DDRC_CFG_ROW_MASK) >> DDRC_CFG_ROW_BIT);
	cols = 8 + ((ddr_cfg & DDRC_CFG_COL_MASK) >> DDRC_CFG_COL_BIT);
	
	dw = (ddr_cfg & DDRC_CFG_DW) ? 4 : 2;
	banks = (ddr_cfg & DDRC_CFG_BA) ? 8 : 4;
	
	size = (1 << (rows + cols)) * dw * banks;
	size *= (DDR_CS1EN + DDR_CS0EN);

	return size;
}
static int dma_check_result(void *src, void *dst, int size,int print_flag)
{
	unsigned int addr1, addr2, i, err = 0;
	unsigned int data_expect,dsrc,ddst; 
	
	addr1 = (unsigned int)src;
	addr2 = (unsigned int)dst;

	for (i = 0; i < size; i += 4) {
		data_expect = gen_verify_data(i);
		dsrc = REG32(addr1);
		ddst = REG32(addr2);
		if ((dsrc != data_expect) || (ddst != data_expect)) {
#if DEBUG
			serial_put_hex(addr2);
			serial_puts("data:");
			serial_put_hex(data_expect);
			serial_puts("src");
			serial_put_hex(dsrc);
			serial_puts("dst");
			serial_put_hex(ddst);
#endif
			err = 1;
			if(!print_flag)
				return 1;
		}

		addr1 += 4;
		addr2 += 4;
	}
	return err;
}

#if DEBUG
void dump_jz_dma_channel(unsigned int dmanr)
{

	if (dmanr > MAX_DMA_NUM)
		return;
	serial_puts("REG_DDRC_ST \t\t=");
	serial_put_hex(REG_DDRC_ST);

	serial_puts("DMA Registers, Channel ");
	serial_put_hex(dmanr);

	serial_puts("  DMACR  = ");
	serial_put_hex(REG_DMAC_DMACR(dmanr/HALF_DMA_NUM));
	serial_puts("  DSAR   = ");
	serial_put_hex(REG_DMAC_DSAR(dmanr));
	serial_puts("  DTAR   = ");
	serial_put_hex(REG_DMAC_DTAR(dmanr));
	serial_puts("  DTCR   = ");
	serial_put_hex(REG_DMAC_DTCR(dmanr));
	serial_puts("  DRSR   = ");
	serial_put_hex(REG_DMAC_DRSR(dmanr));
	serial_puts("  DCCSR  = ");
	serial_put_hex(REG_DMAC_DCCSR(dmanr));
	serial_puts("  DCMD  = ");
	serial_put_hex(REG_DMAC_DCMD(dmanr));
	serial_puts("  DDA  = ");
	serial_put_hex(REG_DMAC_DDA(dmanr));
	serial_puts("  DMADBR = ");
	serial_put_hex(REG_DMAC_DMADBR(dmanr/HALF_DMA_NUM));
}

void dma_nodesc_test_single(int dma_chan, int dma_src_addr, int dma_dst_addr, int size)
{
	int dma_src_phys_addr, dma_dst_phys_addr;

	/* Allocate DMA buffers */
	dma_src_phys_addr = dma_src_addr & (~0xa0000000);
	dma_dst_phys_addr = dma_dst_addr & (~0xa0000000);

	/* Init DMA module */
	REG_DMAC_DCCSR(dma_chan) = 0;
	REG_DMAC_DRSR(dma_chan) = DMAC_DRSR_RS_AUTO;
	REG_DMAC_DSAR(dma_chan) = dma_src_phys_addr;
	REG_DMAC_DTAR(dma_chan) = dma_dst_phys_addr;
	REG_DMAC_DTCR(dma_chan) = size;
	REG_DMAC_DCMD(dma_chan) = DMAC_DCMD_SAI | DMAC_DCMD_DAI | DMAC_DCMD_SWDH_32 | DMAC_DCMD_DWDH_32 | DMAC_DCMD_DS_32BIT;
	REG_DMAC_DCCSR(dma_chan) = DMAC_DCCSR_NDES | DMAC_DCCSR_EN;
}

static void ddrc_regs_print(void)
{
	serial_puts("\nDDRC REGS:\n");
	serial_puts("REG_DDRC_ST \t\t=");
	serial_put_hex(REG_DDRC_ST);
	serial_puts("REG_DDRC_CFG \t\t=");
		    serial_put_hex( REG_DDRC_CFG);
	serial_puts("REG_DDRC_CTRL \t\t=");
	serial_put_hex(REG_DDRC_CTRL);
	serial_puts("REG_DDRC_LMR \t\t=");
	serial_put_hex(REG_DDRC_LMR);
	serial_puts("REG_DDRC_TIMING1 \t=");
	serial_put_hex(REG_DDRC_TIMING1);
	serial_puts("REG_DDRC_TIMING2 \t=");
	serial_put_hex(REG_DDRC_TIMING2);
	serial_puts("REG_DDRC_REFCNT \t\t=");
	serial_put_hex(REG_DDRC_REFCNT);
	serial_puts("REG_DDRC_DQS \t\t=");
	serial_put_hex(REG_DDRC_DQS);
	serial_puts("REG_DDRC_DQS_ADJ \t=");
	serial_put_hex(REG_DDRC_DQS_ADJ);
	serial_puts("REG_DDRC_MMAP0 \t\t=");
	serial_put_hex(REG_DDRC_MMAP0);
	serial_puts("REG_DDRC_MMAP1 \t\t=");
	serial_put_hex(REG_DDRC_MMAP1);
	serial_puts("REG_DDRC_MDELAY \t\t=");
	serial_put_hex(REG_DDRC_MDELAY);
	serial_puts("REG_EMC_PMEMPS2 \t\t=");
	serial_put_hex(REG_EMC_PMEMPS2);
}

static int dma_memcpy_test(int channle_0, int channle_1) {
	int i, err = 0, banks;
	unsigned int addr, DDR_DMA0_SRC, DDR_DMA0_DST, DDR_DMA1_SRC, DDR_DMA1_DST;
	volatile unsigned int tmp;
	register unsigned int cpu_clk;
	long int memsize, banksize, testsize;
	int channel;

#ifndef CONFIG_DDRC
	banks = (SDRAM_BANK4 ? 4 : 2) *(CONFIG_NR_DRAM_BANKS);
#else
	banks = (DDR_BANK8 ? 8 : 4) *(DDR_CS0EN + DDR_CS1EN);
#endif
	memsize = initdram(0);

	banksize = memsize/banks;
	testsize = 4096;

	DDR_DMA0_SRC = DDR_DMA_BASE + banksize*0;
	DDR_DMA0_DST = DDR_DMA_BASE + banksize*0 + testsize;
	DDR_DMA1_SRC = DDR_DMA_BASE + banksize*(banks - 1) + testsize*2;
	DDR_DMA1_DST = DDR_DMA_BASE + banksize*(banks - 1) + testsize*3;

	cpu_clk = CFG_CPU_SPEED;

//    for(channel = 0; channel < MAX_DMA_NUM; channel++) {

	// MDMA
	REG_MDMAC_DMACR = DMAC_DMACR_DMAE;
	// COMMON DMA
	//REG_DMAC_DMACR(0) = DMAC_DMACR_DMAE; /* global DMA enable bit */
	//REG_DMAC_DMACR(1) = DMAC_DMACR_DMAE; /* global DMA enable bit */

    // Write A0
	addr = DDR_DMA0_SRC;

	for (i = 0; i < testsize; i += 4) {
		*(volatile unsigned int *)addr = (i/4*0x11111111);
		//*(volatile unsigned int *)addr = addr;
		addr += 4;
	}

	// Write A2
	addr = DDR_DMA1_SRC;
	for (i = 0; i < testsize; i += 4) {
		*(volatile unsigned int *)addr = (i/4*0x11111111);
		//*(volatile unsigned int *)addr = addr;
		addr += 4;
	}


	// MDMA
	REG_MDMAC_DMACR = 0;
	// COMMON DMA
	//REG_DMAC_DMACR(0) = 0;
	//REG_DMAC_DMACR(1) = 0;
	
    /* Init target buffer */
	jzmemset((void *)DDR_DMA0_DST, 0, testsize);
	jzmemset((void *)DDR_DMA1_DST, 0, testsize);	

	// Set DMA1 for moving data from A0 -> A1
	dma_data_move(channle_0, DDR_DMA0_SRC, DDR_DMA0_DST, testsize, DMAC_DCMD_DS_32BYTE);
	// Set DMA2 for moving data from A2 -> A3
	dma_data_move(channle_1, DDR_DMA1_SRC, DDR_DMA1_DST, testsize, DMAC_DCMD_DS_64BYTE);

	// Start DMA0
	REG_DMAC_DCCSR(0) = DMAC_DCCSR_NDES | DMAC_DCCSR_EN;
	// Wait for DMA0 finishing
	while(REG_DMAC_DTCR(0));
	
	// Start DMA1
	REG_DMAC_DCCSR(1) = DMAC_DCCSR_NDES | DMAC_DCCSR_EN;

	// Read from A1 & check
	err = check_result((void *)DDR_DMA0_SRC, (void *)DDR_DMA0_DST, testsize);
	REG_DMAC_DCCSR(0) &= ~DMAC_DCCSR_EN;  /* disable DMA */
	if (err != 0) {
		serial_puts("DMA0: err!\n");
		//return err;
	}

	// Wait for DMA1 finishing
	while(REG_DMAC_DTCR(1));

	// Read from A3 & check
	err = check_result((void *)DDR_DMA1_SRC, (void *)DDR_DMA1_DST, testsize);
	REG_DMAC_DCCSR(1) &= ~DMAC_DCCSR_EN;  /* disable DMA */
	if (err != 0) {
		serial_puts("DMA1: err!\n");
		//return err;
	}

	serial_puts("TEST PASSED\n\n");
     
	tmp = (cpu_clk / 1000000) * 1;
	while (tmp--);
//    }
	return err;
}

#endif


void dma_nodesc_test(int dma_chan, int dma_src_addr, int dma_dst_addr, int size)
{
	int dma_src_phys_addr, dma_dst_phys_addr;

	/* Allocate DMA buffers */
	dma_src_phys_addr = dma_src_addr & (~0xa0000000);
	dma_dst_phys_addr = dma_dst_addr & (~0xa0000000);

	/* Init DMA module */
	REG_DMAC_DCCSR(dma_chan) = 0;
	REG_DMAC_DRSR(dma_chan) = DMAC_DRSR_RS_AUTO;
	REG_DMAC_DSAR(dma_chan) = dma_src_phys_addr;
	REG_DMAC_DTAR(dma_chan) = dma_dst_phys_addr;
	REG_DMAC_DTCR(dma_chan) = size / 32;
	REG_DMAC_DCMD(dma_chan) = DMAC_DCMD_SAI | DMAC_DCMD_DAI | DMAC_DCMD_SWDH_32 | DMAC_DCMD_DWDH_32 | DMAC_DCMD_DS_32BYTE;
	REG_DMAC_DCCSR(dma_chan) = DMAC_DCCSR_NDES | DMAC_DCCSR_EN;
}

#define DDR_DMA_BASE  (0xa0000000)		/*un-cached*/
#define DMA_CHANNEL0_EN
//#define DMA_CHANNEL1_EN
static int ddr_dma_test(int print_flag) {
	int i, err = 0, banks;
	int times;
	unsigned int addr, DDR_DMA0_SRC, DDR_DMA0_DST, DDR_DMA1_SRC, DDR_DMA1_DST;
	volatile unsigned int tmp;
	register unsigned int cpu_clk;
	long int memsize, banksize, testsize;
	REG_DMAC_DMADCKE(0) = 0x3f;
	REG_DMAC_DMADCKE(1) = 0x3f;

#ifndef CONFIG_DDRC
	banks = (SDRAM_BANK4 ? 4 : 2) *(CONFIG_NR_DRAM_BANKS);
#else
	banks = (DDR_BANK8 ? 8 : 4) *(DDR_CS0EN + DDR_CS1EN);
#endif
	memsize = initdram(0);

	banksize = memsize/banks;
	testsize = 4096;

for(times = 0; times < banks; times++) {
#if 0
	DDR_DMA0_SRC = DDR_DMA_BASE + banksize*0;
	DDR_DMA0_DST = DDR_DMA_BASE + banksize*(banks - 2) + testsize;
	DDR_DMA1_SRC = DDR_DMA_BASE + banksize*(banks - 1) + testsize;
	DDR_DMA1_DST = DDR_DMA_BASE + banksize*1;
#else
	DDR_DMA0_SRC = DDR_DMA_BASE + banksize*times;
	DDR_DMA0_DST = DDR_DMA_BASE + banksize*(times+1) - testsize;
	DDR_DMA1_SRC = DDR_DMA_BASE + banksize*(banks - 1) + testsize*2;
	DDR_DMA1_DST = DDR_DMA_BASE + banksize*(banks - 1) + testsize*3;
#endif

	cpu_clk = CFG_CPU_SPEED;

#ifdef DMA_CHANNEL0_EN
	addr = DDR_DMA0_SRC;

	for (i = 0; i < testsize; i += 4) {
		*(volatile unsigned int *)(addr + i) = gen_verify_data(i);		
	}
#endif
#ifdef DMA_CHANNEL1_EN
	addr = DDR_DMA1_SRC;
	for (i = 0; i < testsize; i += 4) {
   		
		*(volatile unsigned int *)addr = gen_verify_data(i);
		
		addr += 4;
	}
#endif

	REG_DMAC_DMACR(0) = 0;
//	REG_DMAC_DMACR(1) = 0;
	/* Init target buffer */
#ifdef DMA_CHANNEL0_EN
	jzmemset((void *)DDR_DMA0_DST, 0, testsize);
	dma_nodesc_test(0, DDR_DMA0_SRC, DDR_DMA0_DST, testsize);
#endif
#ifdef DMA_CHANNEL1_EN
	jzmemset((void *)DDR_DMA1_DST, 0, testsize);
	dma_nodesc_test(1, DDR_DMA1_SRC, DDR_DMA1_DST, testsize);
#endif

	REG_DMAC_DMACR(0) = DMAC_DMACR_DMAE; /* global DMA enable bit */
//	REG_DMAC_DMACR(1) = DMAC_DMACR_DMAE; /* global DMA enable bit */
//	while(REG_DMAC_DTCR(0) || REG_DMAC_DTCR(1));
	while(REG_DMAC_DTCR(0));
	tmp = (cpu_clk / 1000000) * 1;
	while (tmp--);

#ifdef DMA_CHANNEL0_EN
	err = dma_check_result((void *)DDR_DMA0_SRC, (void *)DDR_DMA0_DST, testsize,print_flag);

	REG_DMAC_DCCSR(0) &= ~DMAC_DCCSR_EN;  /* disable DMA */

	if(err == 0) {
		serial_puts("passed:");
	        serial_put_hex(times);
	} else {
	        serial_put_hex(times);
	}

	if (err != 0) {
#ifdef DMA_CHANNEL1_EN
		REG_DMAC_DCCSR(1) &= ~DMAC_DCCSR_EN;  /* disable DMA */
#endif
		return err;
	}

#endif

#ifdef DMA_CHANNEL1_EN
	//err += dma_check_result((void *)DDR_DMA1_SRC, (void *)DDR_DMA1_DST, testsize);
	//REG_DMAC_DCCSR(1) &= ~DMAC_DCCSR_EN;  /* disable DMA */
#endif
}
	return err;
}

void ddr_mem_init(int msel, int hl, int tsel, int arg)
{
	volatile int tmp_cnt;
	register unsigned int cpu_clk, ddr_twr;
	register unsigned int ddrc_cfg_reg=0, init_ddrc_mdelay=0;

	cpu_clk = CFG_CPU_SPEED;

#if defined(CONFIG_SDRAM_DDR2) // ddr2
	ddrc_cfg_reg = DDRC_CFG_TYPE_DDR2 | (DDR_ROW-12)<<10
		| (DDR_COL-8)<<8 | DDR_CS1EN<<7 | DDR_CS0EN<<6
		| ((DDR_CL-1) | 0x8)<<2 | DDR_BANK8<<1 | DDR_DW32;
#elif defined(CONFIG_SDRAM_DDR1) // ddr1
	ddrc_cfg_reg = DDRC_CFG_BTRUN |DDRC_CFG_TYPE_DDR1
		| (DDR_ROW-12)<<10 | (DDR_COL-8)<<8 | DDR_CS1EN<<7 | DDR_CS0EN<<6
		| ((DDR_CL_HALF?(DDR_CL&~0x8):((DDR_CL-1)|0x8))<<2)
		| DDR_BANK8<<1 | DDR_DW32;
#else // mobile ddr
	ddrc_cfg_reg = DDRC_CFG_TYPE_MDDR
		| (DDR_ROW-12)<<10 | (DDR_COL-8)<<8 | DDR_CS1EN<<7 | DDR_CS0EN<<6
		| ((DDR_CL-1) | 0x8)<<2 | DDR_BANK8<<1 | DDR_DW32;
#endif

	ddrc_cfg_reg |= DDRC_CFG_MPRT;

#if defined(CONFIG_FPGA)
	init_ddrc_mdelay= tsel<<18 | msel<<16 | hl<<15;
#else
	init_ddrc_mdelay= tsel<<18 | msel<<16 | hl<<15 | arg << 14;
#endif
	ddr_twr = ((REG_DDRC_TIMING1 & DDRC_TIMING1_TWR_MASK) >> DDRC_TIMING1_TWR_BIT) + 1;
	REG_DDRC_CFG     = ddrc_cfg_reg;

	REG_DDRC_MDELAY = init_ddrc_mdelay  | 1 << 6;
	/***** init ddrc registers & ddr memory regs ****/
	/* AR: auto refresh */
	REG_DDRC_LMR = DDRC_LMR_CMD_AUREF | DDRC_LMR_START; //0x11;
	/* Wait for DDR_tRP */
	tmp_cnt = (cpu_clk / 1000000) * 1;
	while (tmp_cnt--);

	/* Wait for number of auto-refresh cycles */
	tmp_cnt = (cpu_clk / 1000000) * 10;
	while (tmp_cnt--);

#if defined(CONFIG_SDRAM_DDR2) // ddr1 and mddr

	/* Set CKE High */
	REG_DDRC_CTRL = DDRC_CTRL_CKE; // ?

	/* Wait for number of auto-refresh cycles */
	tmp_cnt = (cpu_clk / 1000000) * 1;
	while (tmp_cnt--);

	/* PREA */
	REG_DDRC_LMR =  DDRC_LMR_CMD_PREC | DDRC_LMR_START; //0x1;

	/* Wait for DDR_tRP */
	tmp_cnt = (cpu_clk / 1000000) * 1;
	while (tmp_cnt--);

	/* EMR2: extend mode register2 */
	REG_DDRC_LMR = DDRC_LMR_BA_EMRS2 | DDRC_LMR_CMD_LMR | DDRC_LMR_START;//0x221;

	/* EMR3: extend mode register3 */
	REG_DDRC_LMR = DDRC_LMR_BA_EMRS3 | DDRC_LMR_CMD_LMR | DDRC_LMR_START;//0x321;

	/* EMR1: extend mode register1 */
	REG_DDRC_LMR = (DDR_EMRS1_DQS_DIS << 16) | DDRC_LMR_BA_EMRS1 | DDRC_LMR_CMD_LMR | DDRC_LMR_START;

	/* wait DDR_tMRD */
	tmp_cnt = (cpu_clk / 1000000) * 1;
	while (tmp_cnt--);

	/* MR - DLL Reset A1A0 burst 2 */
	REG_DDRC_LMR = ((ddr_twr-1)<<9 | DDR2_MRS_DLL_RST | DDR_CL<<4 | DDR_MRS_BL_4)<< 16
		| DDRC_LMR_BA_MRS | DDRC_LMR_CMD_LMR | DDRC_LMR_START;

	/* wait DDR_tMRD */
	tmp_cnt = (cpu_clk / 1000000) * 1;
	while (tmp_cnt--);

	/* PREA */
	REG_DDRC_LMR =  DDRC_LMR_CMD_PREC | DDRC_LMR_START; //0x1;

	/* Wait for DDR_tRP */
	tmp_cnt = (cpu_clk / 1000000) * 1;
	while (tmp_cnt--);

	/* AR: auto refresh */
	REG_DDRC_LMR = DDRC_LMR_CMD_AUREF | DDRC_LMR_START; //0x11;
	/* Wait for DDR_tRP */
	tmp_cnt = (cpu_clk / 1000000) * 1;
	while (tmp_cnt--);

	REG_DDRC_LMR = DDRC_LMR_CMD_AUREF | DDRC_LMR_START; //0x11;

	/* Wait for DDR_tRP */
	tmp_cnt = (cpu_clk / 1000000) * 1;
	while (tmp_cnt--);

	/* MR - DLL Reset End */
	REG_DDRC_LMR = ((ddr_twr-1)<<9 | DDR_CL<<4 | DDR_MRS_BL_4)<< 16
		| DDRC_LMR_BA_MRS | DDRC_LMR_CMD_LMR | DDRC_LMR_START;

	/* wait 200 tCK */
	tmp_cnt = (cpu_clk / 1000000) * 2;
	while (tmp_cnt--);

	/* EMR1 - OCD Default */
	REG_DDRC_LMR = (DDR_EMRS1_DQS_DIS | DDR_EMRS1_OCD_DFLT) << 16
		| DDRC_LMR_BA_EMRS1 | DDRC_LMR_CMD_LMR | DDRC_LMR_START;

	/* EMR1 - OCD Exit */
	REG_DDRC_LMR = (DDR_EMRS1_DQS_DIS << 16) | DDRC_LMR_BA_EMRS1 | DDRC_LMR_CMD_LMR | DDRC_LMR_START;

	/* wait DDR_tMRD */
	tmp_cnt = (cpu_clk / 1000000) * 1;
	while (tmp_cnt--);

#elif defined(CONFIG_SDRAM_DDR1) // ddr1 and mddr
	/* set cke high */
	REG_DDRC_CTRL = DDRC_CTRL_CKE; // ?

	/* Nop command */
	tmp_cnt = (cpu_clk / 1000000) * 1;
	while (tmp_cnt--);

	/* PREA  all */
//	REG_DDRC_LMR =  DDRC_LMR_CMD_PREC | DDRC_LMR_START; //0x1;

	/* Wait for DDR_tRP */
	tmp_cnt = (cpu_clk / 1000000) * 1;
	while (tmp_cnt--);

	/* EMR: extend mode register: enable DLL */
	REG_DDRC_LMR = (DDR1_EMRS_OM_NORMAL | DDR1_EMRS_DS_FULL | DDR1_EMRS_DLL_EN) << 16
		| DDRC_LMR_BA_N_EMRS | DDRC_LMR_CMD_LMR | DDRC_LMR_START;

	/* MR DLL reset */
	REG_DDRC_LMR = (DDR1_MRS_OM_DLLRST | (DDR_CL_HALF?(DDR_CL|0x4):DDR_CL)<<4 | DDR_MRS_BL_4)<< 16
		| DDRC_LMR_BA_N_MRS | DDRC_LMR_CMD_LMR | DDRC_LMR_START;

	/* wait DDR_tXSRD, 200 tCK */
	tmp_cnt = (cpu_clk / 1000000) * 2;
	while (tmp_cnt--);
	/* PREA all */
	REG_DDRC_LMR =  DDRC_LMR_CMD_PREC | DDRC_LMR_START; //0x1;
	REG_DDRC_LMR = DDRC_LMR_CMD_AUREF | DDRC_LMR_START; //0x11;
	REG_DDRC_LMR = DDRC_LMR_CMD_AUREF | DDRC_LMR_START; //0x11;
	tmp_cnt = (cpu_clk / 1000000) * 15;
	while (tmp_cnt--);
	/* EMR: extend mode register, clear dll en */
	REG_DDRC_LMR = (DDR1_EMRS_OM_NORMAL | DDR1_EMRS_DS_FULL) << 16
		| DDRC_LMR_BA_N_EMRS | DDRC_LMR_CMD_LMR | DDRC_LMR_START;
	/* wait DDR_tMRD */
	tmp_cnt = (cpu_clk / 1000000) * 1;
	while (tmp_cnt--);

#elif defined(CONFIG_SDRAM_MDDR) // ddr1 and mddr
	REG_DDRC_CTRL = DDRC_CTRL_CKE; // ?

	/* Wait for number of auto-refresh cycles */
	tmp_cnt = (cpu_clk / 1000000) * 20;
	while (tmp_cnt--);

	/* PREA */
	REG_DDRC_LMR =  DDRC_LMR_CMD_PREC | DDRC_LMR_START; //0x1;

	/* Wait for DDR_tRP */
	tmp_cnt = (cpu_clk / 1000000) * 1;
	while (tmp_cnt--);

	/* AR: auto refresh */
	REG_DDRC_LMR = DDRC_LMR_CMD_AUREF | DDRC_LMR_START; //0x11;

	/* wait DDR_tRFC */
	tmp_cnt = (cpu_clk / 1000000) * 1;
	while (tmp_cnt--);

	/* AR: auto refresh */
	REG_DDRC_LMR = DDRC_LMR_CMD_AUREF | DDRC_LMR_START; //0x11;
	/* wait DDR_tRFC */
	tmp_cnt = (cpu_clk / 1000000) * 1;
	while (tmp_cnt--);

	/* MR */
	REG_DDRC_LMR = (DDR_CL<<4 | DDR_MRS_BL_4)<< 16
		| DDRC_LMR_BA_M_MRS | DDRC_LMR_CMD_LMR | DDRC_LMR_START;

	/* wait DDR_tMRD */
	tmp_cnt = (cpu_clk / 1000000) * 1;
	while (tmp_cnt--);

	/* EMR: extend mode register */
	REG_DDRC_LMR = (DDR_EMRS_DS_HALF | DDR_EMRS_PRSR_ALL) << 16
		| DDRC_LMR_BA_M_EMRS | DDRC_LMR_CMD_LMR | DDRC_LMR_START;

	/* wait DDR_tMRD */
	tmp_cnt = (cpu_clk / 1000000) * 1;
	while (tmp_cnt--);

#endif
}
void testallmem()
{
	unsigned int i,d;
	unsigned int *dat;
	dat = (unsigned int *)0xa0000000;
	for(i = 0; i < 64*1024*1024;i+=4)
	{
		*dat = i;
		dat++;
	}
	
	dat = (unsigned int *)0xa0000000;
	for(i = 0; i < 64*1024*1024;i+=4)
	{
		d = *dat;
		if(d != i)
		{
			serial_puts("errdata:\n");
			serial_puts("expect:\n");
			serial_put_hex(i);
			serial_put_hex(d);
		}
		dat++;
	}

}

#define DDR_DMA_BASE  (0xa0000000)		/*un-cached*/

void dma_data_move(int dma_chan, int dma_src_addr, int dma_dst_addr, int size, int burst)
{
	int dma_src_phys_addr, dma_dst_phys_addr;

	/* set addr to uncached */
	dma_src_phys_addr = dma_src_addr & ~0xa0000000;
	dma_dst_phys_addr = dma_dst_addr & ~0xa0000000;

	/* Init DMA module */

	REG_DMAC_DCCSR(dma_chan) = 0;
	REG_DMAC_DRSR(dma_chan) = DMAC_DRSR_RS_AUTO;
	REG_DMAC_DSAR(dma_chan) = dma_src_phys_addr;
	REG_DMAC_DTAR(dma_chan) = dma_dst_phys_addr;
	REG_DMAC_DTCR(dma_chan) = size / 32;
	REG_DMAC_DCMD(dma_chan) = DMAC_DCMD_SAI | DMAC_DCMD_DAI | DMAC_DCMD_SWDH_32 | DMAC_DCMD_DWDH_32 | burst;
//	REG_DMAC_DCCSR(dma_chan) = DMAC_DCCSR_NDES | DMAC_DCCSR_EN;
}

static int check_result(void *src, void *dst, int size)
{
	unsigned int addr1, addr2, i, err = 0;

	addr1 = (unsigned int)src;
	addr2 = (unsigned int)dst;

	for (i = 0; i < size; i += 4) {
		if ((*(volatile unsigned int *)addr1 != *(volatile unsigned int *)addr2)
		    || (*(volatile unsigned int *)addr1 != (i/4*0x11111111))) {
#ifdef DEBUG
			err++;
			if (err < 10){
				serial_puts("wrong data at");serial_put_hex(addr2);
				serial_puts("data");serial_put_hex(i/4*0x11111111);
				serial_puts("src");serial_put_hex(*(volatile unsigned int *)addr1);
				serial_puts("dst");serial_put_hex(*(volatile unsigned int *)addr2);
			}
#else
			return 1;
#endif
		}

		addr1 += 4;
		addr2 += 4;
	}
	return err;
}

#endif

#if (defined(CONFIG_SDRAM_MDDR) || defined(CONFIG_SDRAM_DDR1) || defined(CONFIG_SDRAM_DDR2))
#define DEF_DDR_CVT 0
#define DDR_USE_FIRST_ARGS 0
unsigned int testall = 0;
/* DDR sdram init */
void sdram_init_4760(void)
{
	//add driver power
	REG_EMC_PMEMPS2 |= (3 << 18);

	REG_DMAC_DMADCKE(0) = 0x3f;
	REG_DMAC_DMADCKE(1) = 0x3f;
	int i, num = 0, tsel = 0, msel, hl;
	volatile unsigned int tmp_cnt;
	register unsigned int tmp, cpu_clk, mem_clk, ddr_twr, ns, ns_int;
	register unsigned int ddrc_timing1_reg=0, ddrc_timing2_reg=0;
	register unsigned int init_ddrc_refcnt=0, init_ddrc_dqs=0, init_ddrc_ctrl=0;

	register unsigned int memsize, ddrc_mmap0_reg, ddrc_mmap1_reg;
	register unsigned int mem_base0, mem_base1, mem_mask0, mem_mask1;

#if defined(CONFIG_FPGA)
	int cvt = DEF_DDR_CVT, cvt_cnt0 = 0, cvt_cnt1 = 1;
	int max = 0, max0 = 0, max1 = 0, min0 = 0, min1 = 0;
	int tsel0 = 0, tsel1 = 0;
	struct ddr_delay_sel_t ddr_delay_sel[] = {
		{0, 1}, {0, 0},	{1, 1}, {1, 0},
		{2, 1}, {2, 0},	{3, 1}, {3, 0}
	};
#endif

	testall = 0; 
	cpu_clk = CFG_CPU_SPEED;

#ifdef DEBUG
	ddrc_regs_print();
#endif

#if defined(CONFIG_FPGA)
	mem_clk = CFG_EXTAL / CFG_DIV;
	ns = 7;
#else
	mem_clk = __cpm_get_mclk();
	ns = 1000000000 / mem_clk; /* ns per tck ns <= real value */
#endif

#ifdef DEBUG
	serial_puts("mem_clk = ");
	serial_put_hex(mem_clk);
#endif

	/* ACTIVE to PRECHARGE command period */
	tmp = (DDR_tRAS%ns == 0) ? (DDR_tRAS/ns) : (DDR_tRAS/ns+1);
	if (tmp < 1) tmp = 1;
	if (tmp > 31) tmp = 31;
	ddrc_timing1_reg = ((tmp/2) << DDRC_TIMING1_TRAS_BIT);

	/* READ to PRECHARGE command period. */
	tmp = (DDR_tRTP%ns == 0) ? (DDR_tRTP/ns) : (DDR_tRTP/ns+1);
	if (tmp < 1) tmp = 1;
	if (tmp > 4) tmp = 4;
	ddrc_timing1_reg |= ((tmp-1) << DDRC_TIMING1_TRTP_BIT);
	
	/* PRECHARGE command period. */
	tmp = (DDR_tRP%ns == 0) ? DDR_tRP/ns : (DDR_tRP/ns+1);
	if (tmp < 1) tmp = 1;
	if (tmp > 8) tmp = 8;
	ddrc_timing1_reg |= ((tmp-1) << DDRC_TIMING1_TRP_BIT);

	/* ACTIVE to READ or WRITE command period. */
	tmp = (DDR_tRCD%ns == 0) ? DDR_tRCD/ns : (DDR_tRCD/ns+1);
	if (tmp < 1) tmp = 1;
	if (tmp > 8) tmp = 8;
	ddrc_timing1_reg |= ((tmp-1) << DDRC_TIMING1_TRCD_BIT);

	/* ACTIVE to ACTIVE command period. */
	tmp = (DDR_tRC%ns == 0) ? DDR_tRC/ns : (DDR_tRC/ns+1);
	if (tmp < 3) tmp = 3;
	if (tmp > 31) tmp = 31;
	ddrc_timing1_reg |= ((tmp/2) << DDRC_TIMING1_TRC_BIT);

	/* ACTIVE bank A to ACTIVE bank B command period. */
	tmp = (DDR_tRRD%ns == 0) ? DDR_tRRD/ns : (DDR_tRRD/ns+1);
	if (tmp < 2) tmp = 2;
	if (tmp > 4) tmp = 4;
	ddrc_timing1_reg |= ((tmp-1) << DDRC_TIMING1_TRRD_BIT);


	/* WRITE Recovery Time defined by register MR of DDR2 memory */
	tmp = (DDR_tWR%ns == 0) ? DDR_tWR/ns : (DDR_tWR/ns+1);
	tmp = (tmp < 1) ? 1 : tmp;
	tmp = (tmp < 2) ? 2 : tmp;
	tmp = (tmp > 6) ? 6 : tmp;
	ddrc_timing1_reg |= ((tmp-1) << DDRC_TIMING1_TWR_BIT);
	ddr_twr = tmp; 

	/* WRITE to READ command delay. */ 
	tmp = (DDR_tWTR%ns == 0) ? DDR_tWTR/ns : (DDR_tWTR/ns+1);
	if (tmp > 4) tmp = 4;
	ddrc_timing1_reg |= ((tmp-1) << DDRC_TIMING1_TWTR_BIT);


	/* WRITE to READ command delay. */ 
	tmp = DDR_tWTR/ns;
	if (tmp < 1) tmp = 1;
	if (tmp > 4) tmp = 4;
	ddrc_timing1_reg |= ((tmp-1) << DDRC_TIMING1_TWTR_BIT);

	/* AUTO-REFRESH command period. */
	tmp = (DDR_tRFC%ns == 0) ? DDR_tRFC/ns : (DDR_tRFC/ns+1);
	if (tmp > 31) tmp = 31;
	ddrc_timing2_reg = ((tmp/2) << DDRC_TIMING2_TRFC_BIT);

	/* Minimum Self-Refresh / Deep-Power-Down time */
	tmp = DDR_tMINSR/ns;
	if (tmp < 9) tmp = 9;
	if (tmp > 129) tmp = 129;
	ddrc_timing2_reg |= (((tmp-1)/8-1) << DDRC_TIMING2_TMINSR_BIT);
	ddrc_timing2_reg |= (DDR_tXP-1)<<4 | (DDR_tMRD-1);

	init_ddrc_refcnt = DDR_CLK_DIV << 1 | DDRC_REFCNT_REF_EN;

	ns_int = (1000000000%mem_clk == 0) ?
		(1000000000/mem_clk) : (1000000000/mem_clk+1);
	tmp = DDR_tREFI/ns_int;
	tmp = tmp / (16 * (1 << DDR_CLK_DIV)) - 1;
	if (tmp > 0xfff)
		tmp = 0xfff;
	if (tmp < 1)
		tmp = 1;

	init_ddrc_refcnt |= tmp << DDRC_REFCNT_CON_BIT;
	init_ddrc_dqs = DDRC_DQS_AUTO | DDRC_DQS_DET;

	/* precharge power down, disable power down */
	/* precharge power down, if set active power down, |= DDRC_CTRL_ACTPD */
	init_ddrc_ctrl = DDRC_CTRL_PDT_DIS | DDRC_CTRL_PRET_8 | DDRC_CTRL_UNALIGN | DDRC_CTRL_CKE;
	/* Add Jz4760 chip here. Jz4760 chip have no cvt */
#define MAX_TSEL_VALUE 4
#define MAX_DELAY_VALUES 16 /* quars (2) * hls (2) * msels (4) */
	int j, index, quar;
	int mem_index[MAX_DELAY_VALUES];
#if 0 // probe
	jzmemset(mem_index, 0, MAX_DELAY_VALUES);
	for (i = 1; i < MAX_TSEL_VALUE; i ++) {
		tsel = i;
		for (j = 0; j < MAX_DELAY_VALUES; j++) {
			msel = j/4;
			hl = ((j/2)&1)^1;
			quar = j&1;

			/* reset ddrc_controller */
			REG_DDRC_CTRL = DDRC_CTRL_RESET;

			/* Wait for precharge, > 200us */
			tmp_cnt = (cpu_clk / 1000000) * 200;
			while (tmp_cnt--);
			
			REG_DDRC_CTRL = 0x0;
			REG_DDRC_TIMING1 = ddrc_timing1_reg;
			REG_DDRC_TIMING2 = ddrc_timing2_reg;
			
			ddr_mem_init(msel, hl, tsel, quar);
				
			memsize = initdram(0);
			mem_base0 = DDR_MEM_PHY_BASE >> 24;
			mem_base1 = (DDR_MEM_PHY_BASE + memsize / (DDR_CS1EN + DDR_CS0EN)) >> 24;
			mem_mask1 = mem_mask0 = 0xff &
				~(((memsize/(DDR_CS1EN+DDR_CS0EN) >> 24)
				   - 1) & DDRC_MMAP_MASK_MASK);
			
			ddrc_mmap0_reg = mem_base0 << DDRC_MMAP_BASE_BIT | mem_mask0;
			ddrc_mmap1_reg = mem_base1 << DDRC_MMAP_BASE_BIT | mem_mask1;

			REG_DDRC_MMAP0 = ddrc_mmap0_reg;
			REG_DDRC_MMAP1 = ddrc_mmap1_reg;

			REG_DDRC_REFCNT = init_ddrc_refcnt;

			/* Enable DLL Detect */
			REG_DDRC_DQS    = init_ddrc_dqs;

			while(!(REG_DDRC_DQS &( DDRC_DQS_ERROR | DDRC_DQS_READY)));
			/* Set CKE High */
			REG_DDRC_CTRL = init_ddrc_ctrl;

			/* Wait for number of auto-refresh cycles */
			tmp_cnt = (cpu_clk / 1000000) * 10;
			while (tmp_cnt--);

			/* Auto Refresh */
			REG_DDRC_LMR = DDRC_LMR_CMD_AUREF | DDRC_LMR_START; //0x11;

			/* Wait for number of auto-refresh cycles */
			tmp_cnt = (cpu_clk / 1000000) * 10;
			while (tmp_cnt--);

			tmp_cnt = (cpu_clk / 1000000) * 10;
			while (tmp_cnt--);

			{
				int result = 0;
				result = ddr_dma_test(0);
				if(result != 0)
					serial_puts("FAIL!\n");
#if DEBUG
				serial_puts("result:");
				serial_put_hex(result);
				serial_put_hex(num);
#endif

				if(result != 0) {
					if (num > 0)
						break;
					else
						continue;
				} else { /* test pass */

					mem_index[num] = j;
					num++;
				}
			}
		}
		
		if (num > 0)
			break;
	}
	if (tsel == 3 && num == 0) 
		serial_puts("DDR INIT ERROR\n"); /* can't find a suitable mask delay. */
	index = 0;
	for (i = 0; i < num; i++) {
		index += mem_index[i];
		serial_put_hex(mem_index[i]);
	}

#ifdef DEBUG
	serial_puts("index-1:");
	serial_put_hex(index);
#endif
	
	if (num)
		index /= num;
#endif

	msel = index/4;
	hl = ((index/2)&1)^1;
	quar = index&1;

#ifdef DEBUG
	serial_puts("tsel");
	serial_put_hex(tsel);
	serial_puts("num");
	serial_put_hex(num);
	serial_puts("index-2:");
	serial_put_hex(index);
#endif

	/* reset ddrc_controller */
	REG_DDRC_CTRL = DDRC_CTRL_RESET;
	
	/* Wait for precharge, > 200us */
	tmp_cnt = (cpu_clk / 1000000) * 200;
	while (tmp_cnt--);
	
	REG_DDRC_CTRL = 0x0;
	REG_DDRC_TIMING1 = ddrc_timing1_reg;
	REG_DDRC_TIMING2 = ddrc_timing2_reg;

	ddr_mem_init(msel, hl, tsel, quar);

	memsize = initdram(0);
	mem_base0 = DDR_MEM_PHY_BASE >> 24;
	mem_base1 = (DDR_MEM_PHY_BASE + memsize / (DDR_CS1EN + DDR_CS0EN)) >> 24;
	mem_mask1 = mem_mask0 = 0xff &
		~(((memsize/(DDR_CS1EN+DDR_CS0EN) >> 24)
		   - 1) & DDRC_MMAP_MASK_MASK);
	
	ddrc_mmap0_reg = mem_base0 << DDRC_MMAP_BASE_BIT | mem_mask0;
	ddrc_mmap1_reg = mem_base1 << DDRC_MMAP_BASE_BIT | mem_mask1;

	REG_DDRC_MMAP0 = ddrc_mmap0_reg;
	REG_DDRC_MMAP1 = ddrc_mmap1_reg;
	REG_DDRC_REFCNT = init_ddrc_refcnt;

	/* Enable DLL Detect */
	REG_DDRC_DQS    = init_ddrc_dqs;
			
	/* Set CKE High */
	REG_DDRC_CTRL = init_ddrc_ctrl;

	/* Wait for number of auto-refresh cycles */
	tmp_cnt = (cpu_clk / 1000000) * 10;
	while (tmp_cnt--);
	
	/* Auto Refresh */
	REG_DDRC_LMR = DDRC_LMR_CMD_AUREF | DDRC_LMR_START; //0x11;
	
	/* Wait for number of auto-refresh cycles */
	tmp_cnt = (cpu_clk / 1000000) * 10;
	while (tmp_cnt--);
	if(testall)
		testallmem();
}
#else
void sdram_init_4760(void)
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
#endif

static void serial_setbrg(void)
{
	volatile u8 *uart_lcr = (volatile u8 *)(UART_BASE + OFF_LCR);
	volatile u8 *uart_dlhr = (volatile u8 *)(UART_BASE + OFF_DLHR);
	volatile u8 *uart_dllr = (volatile u8 *)(UART_BASE + OFF_DLLR);
	u32 baud_div, tmp;

	baud_div = (CFG_EXTAL / 16 / 57600);
	tmp = *uart_lcr;
	tmp |= UART_LCR_DLAB;
	*uart_lcr = tmp;

	*uart_dlhr = (baud_div >> 8) & 0xff;
	*uart_dllr = baud_div & 0xff;

	tmp &= ~UART_LCR_DLAB;
	*uart_lcr = tmp;
}

void serial_init_4760(int uart)
{
	UART_BASE = UART0_BASE + uart * UART_OFF;

	volatile u8 *uart_fcr = (volatile u8 *)(UART_BASE + OFF_FCR);
	volatile u8 *uart_lcr = (volatile u8 *)(UART_BASE + OFF_LCR);
	volatile u8 *uart_ier = (volatile u8 *)(UART_BASE + OFF_IER);
	volatile u8 *uart_sircr = (volatile u8 *)(UART_BASE + OFF_SIRCR);

	/* Disable port interrupts while changing hardware */
	*uart_ier = 0;

	/* Disable UART unit function */
	*uart_fcr = ~UART_FCR_UUE;

	/* Set both receiver and transmitter in UART mode (not SIR) */
	*uart_sircr = ~(SIRCR_RSIRE | SIRCR_TSIRE);

	/* Set databits, stopbits and parity. (8-bit data, 1 stopbit, no parity) */
	*uart_lcr = UART_LCR_WLEN_8 | UART_LCR_STOP_1;

	/* Set baud rate */
	serial_setbrg();

	/* Enable UART unit, enable and clear FIFO */
	*uart_fcr = UART_FCR_UUE | UART_FCR_FE | UART_FCR_TFLS | UART_FCR_RFLS;
}
