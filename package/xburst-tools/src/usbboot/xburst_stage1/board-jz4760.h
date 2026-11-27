/*
 * JZ4760 board definitions.
 *
 * Copyright (c) 2005-2008 Ingenic Semiconductor Inc.
 */
#ifndef __BOARD_JZ4760_H__
#define __BOARD_JZ4760_H__

//#define DEBUG
//#define CONFIG_FPGA
//#define CFG_DIV	2	/* for FPGA */

#define CFG_EXTAL               12000000
#define CFG_CPU_SPEED           144000000       /* CPU clock */

#define CONFIG_DDRC
#define CONFIG_SDRAM_DDR2
//#define CONFIG_SDRAM_MDDR
//#define CONFIG_SDRAM_DDR1
//#define CONFIG_MOBILE_SDRAM

#if (!defined(CONFIG_SDRAM_MDDR) && !defined(CONFIG_SDRAM_DDR1) && !defined(CONFIG_SDRAM_DDR2))
/*-----------------------------------------------------------------------
 * SDRAM Info.
 */
#define CONFIG_NR_DRAM_BANKS	1  /* SDRAM BANK Number: 1, 2*/

#ifndef CONFIG_MOBILE_SDRAM
// SDRAM paramters
#define SDRAM_BW16		0	/* Data bus width: 0-32bit, 1-16bit */
#define SDRAM_BANK4		1	/* Banks each chip: 0-2bank, 1-4bank */
#define SDRAM_ROW		13	/* Row address: 11 to 13 */
#define SDRAM_COL		9	/* Column address: 8 to 12 */
#define SDRAM_CASL		2	/* CAS latency: 2 or 3 */

// SDRAM Timings, unit: ns
#define SDRAM_TRAS		45	/* RAS# Active Time */
#define SDRAM_RCD		20	/* RAS# to CAS# Delay */
#define SDRAM_TPC		20	/* RAS# Precharge Time */
#define SDRAM_TRWL		7	/* Write Latency Time */
#define SDRAM_TREF	        7812	/* Refresh period: 4096 refresh cycles/64ms */

#else /* Mobile SDRAM */
// SDRAM paramters
#define SDRAM_BW16		0	/* Data bus width: 0-32bit, 1-16bit */
#define SDRAM_BANK4		1	/* Banks each chip: 0-2bank, 1-4bank */
#define SDRAM_ROW		13	/* Row address: 11 to 13 */
#define SDRAM_COL		9	/* Column address: 8 to 12 */
#define SDRAM_CASL		3	/* CAS latency: 2 or 3 */

// SDRAM Timings, unit: ns
#define SDRAM_TRAS		50	/* RAS# Active Time */
#define SDRAM_RCD		18	/* RAS# to CAS# Delay */
#define SDRAM_TPC		20	/* RAS# Precharge Time */
#define SDRAM_TRWL		7	/* Write Latency Time */
#define SDRAM_TREF	        7812	/* Refresh period: 4096 refresh cycles/64ms */
#endif /* CONFIG_MOBILE_SDRAM */

#else /* CONFIG_DDRC */

/*--------------------------------------------------------------------------------
 * DDR2 info
 */
/* Chip Select */
#define DDR_CS1EN 0 // CSEN : whether a ddr chip exists 0 - un-used, 1 - used
#define DDR_CS0EN 1
#define DDR_DW32 1 /* 0 - 16-bit data width, 1 - 32-bit data width */

/* SDRAM paramters */
#if defined(CONFIG_SDRAM_DDR2) // ddr2
#define DDR_ROW 13 /* ROW : 12 to 14 row address */
#define DDR_COL 10 /* COL :  8 to 10 column address */
#define DDR_BANK8 1 /* Banks each chip: 0-4bank, 1-8bank */
#define DDR_CL 3 /* CAS latency: 1 to 7 */

/*
 * ddr2 controller timing1 register
 */
#define DDR_tRAS 45 /*tRAS: ACTIVE to PRECHARGE command period to the same bank. */
#define DDR_tRTP 8 /* 7.5ns READ to PRECHARGE command period. */
#define DDR_tRP 42 /* tRP: PRECHARGE command period to the same bank */
#define DDR_tRCD 42 /* ACTIVE to READ or WRITE command period to the same bank. */
#define DDR_tRC 60 /* ACTIVE to ACTIVE command period to the same bank.*/
#define DDR_tRRD 8   /* ACTIVE bank A to ACTIVE bank B command period. */
#define DDR_tWR 15 /* WRITE Recovery Time defined by register MR of DDR2 memory */
#define DDR_tWTR 2 /* unit: tCK. WRITE to READ command delay. */

/*
 * ddr2 controller timing2 register
 */
#define DDR_tRFC 128 /* ns,  AUTO-REFRESH command period. */
#define DDR_tMINSR 6 /* Minimum Self-Refresh / Deep-Power-Down */
#define DDR_tXP 2 /* EXIT-POWER-DOWN to next valid command period: 1 to 8 tCK. */
#define DDR_tMRD 2 /* unit: tCK. Load-Mode-Register to next valid command period: 1 to 4 tCK */

/*
 * ddr2 controller refcnt register
 */
#define DDR_tREFI	        7800	/* Refresh period: ns */

#elif defined(CONFIG_SDRAM_MDDR) // ddr1 and mddr
#define DDR_ROW 14 /* ROW : 12 to 14 row address */
#define DDR_COL 10 /* COL :  8 to 10 column address */
#define DDR_BANK8 0 /* Banks each chip: 0-4bank, 1-8bank */
#define DDR_CL 3 /* CAS latency: 1 to 7 */
/*
 * ddr2 controller timing1 register
 */
#define DDR_tRAS 40 /*tRAS: ACTIVE to PRECHARGE command period to the same bank. */
#define DDR_tRTP 12 /* 7.5ns READ to PRECHARGE command period. */
#define DDR_tRP 15 /* tRP: PRECHARGE command period to the same bank */
#define DDR_tRCD 20 /* ACTIVE to READ or WRITE command period to the same bank. */
#define DDR_tRC 55 /* ACTIVE to ACTIVE command period to the same bank.*/
#define DDR_tRRD 10   /* ACTIVE bank A to ACTIVE bank B command period. */
#define DDR_tWR 15 /* WRITE Recovery Time defined by register MR of DDR2 memory */
#define DDR_tWTR 2 /* WRITE to READ command delay. */
/*
 * ddr2 controller timing2 register
 */
#define DDR_tRFC 90 /* ns,  AUTO-REFRESH command period. */
#define DDR_tMINSR 6 /* Minimum Self-Refresh / Deep-Power-Down */
#define DDR_tXP 1 /* EXIT-POWER-DOWN to next valid command period: 1 to 8 tCK. */
#define DDR_tMRD 2 /* unit: tCK Load-Mode-Register to next valid command period: 1 to 4 tCK */
/*
 * ddr2 controller refcnt register
 */
#define DDR_tREFI	        7800	/* Refresh period: 4096 refresh cycles/64ms */

#elif defined(CONFIG_SDRAM_DDR1) // ddr1 and mddr
#define DDR_ROW 13 /* ROW : 12 to 14 row address */
#define DDR_COL 10  /* COL :  8 to 10 column address */
#define DDR_BANK8 0 /* Banks each chip: 0-4bank, 1-8bank */
#define DDR_CL 3 /* CAS latency: 1 to 7 */
#define DDR_CL_HALF 0 /*Only for DDR1, Half CAS latency: 0 or 1 */
/*
 * ddr2 controller timing1 register
 */
#define DDR_tRAS 40 /*tRAS: ACTIVE to PRECHARGE command period to the same bank. */
#define DDR_tRTP 12 /* 7.5ns READ to PRECHARGE command period. */
#define DDR_tRP 15 /* tRP: PRECHARGE command period to the same bank */
#define DDR_tRCD 15 /* ACTIVE to READ or WRITE command period to the same bank. */
#define DDR_tRC 55 /* ACTIVE to ACTIVE command period to the same bank.*/
#define DDR_tRRD 10   /* ACTIVE bank A to ACTIVE bank B command period. */
#define DDR_tWR 15 /* WRITE Recovery Time defined by register MR of DDR2 memory */
#define DDR_tWTR 2 /* WRITE to READ command delay 2*tCK */
/*
 * ddr2 controller timing2 register
 */
#define DDR_tRFC 70 /* ns,  AUTO-REFRESH command period. */
#define DDR_tMINSR 6 /* Minimum Self-Refresh / Deep-Power-Down */
#define DDR_tXP 2 /* EXIT-POWER-DOWN to next valid command period: 1 to 8 tCK. */
#define DDR_tMRD 2 /* unit: tCK. Load-Mode-Register to next valid command period: 1 to 4 tCK */
/*
 * ddr2 controller refcnt register
 */
#define DDR_tREFI	        7800	/* Refresh period: 4096 refresh cycles/64ms */

#endif

#define DDR_CLK_DIV 1    /* Clock Divider. auto refresh
			  * cnt_clk = memclk/(16*(2^DDR_CLK_DIV))
			  */
#endif /* CONFIG_DDRC */

#endif /* __BOARD_JZ4760_H__ */
