/* This file is based on code by Ingenic Semiconductor Co., Ltd. */

#ifndef __INGENIC__H__
#define __INGENIC__H__

#include <stdint.h>

#define VR_GET_CPU_INFO		0x00
#define VR_SET_DATA_ADDRESS	0x01
#define VR_SET_DATA_LENGTH	0x02
#define VR_FLUSH_CACHES		0x03
#define VR_PROGRAM_START1	0x04
#define VR_PROGRAM_START2	0x05
#define VR_NOR_OPS		0x06
#define VR_NAND_OPS		0x07
#define VR_SDRAM_OPS		0x08
#define VR_CONFIGRATION		0x09
#define VR_GET_NUM		0x0a

#define CMDSET_SPL	1
#define CMDSET_USBBOOT	2

#define INGENIC_STAGE1	1
#define INGENIC_STAGE2	2

#define STAGE1_DEBUG_BOOT		0
#define STAGE1_DEBUG_MEMTEST		1
#define STAGE1_DEBUG_GPIO_SET		2
#define STAGE1_DEBUG_GPIO_CLEAR		3

#define STAGE1_BASE	0x2000
#define STAGE2_CODESIZE	0x400000
#define SDRAM_BASE	0x80000000

#define STAGE2_IOBUF (2048 * 128)

#define DS_flash_info 0
#define DS_hand	1

#define SDRAM_LOAD	0

#define NAND_QUERY	0
#define NAND_INIT	1
#define NAND_MARK_BAD	2
#define NAND_READ_OOB	3
#define NAND_READ_RAW	4
#define NAND_ERASE	5
#define NAND_READ	6
#define NAND_PROGRAM	7
#define NAND_READ_TO_RAM	8

#define OOB_ECC	0
#define OOB_NO_ECC	1
#define NO_OOB	2
#define NAND_RAW	(1 << 7)

#define PROGRESS_INIT	0
#define PROGRESS_UPDATE	1
#define PROGRESS_FINI	2

typedef struct {
	/* debug args */
	uint8_t debug_ops;
	uint8_t pin_num;
	uint32_t start;
	uint32_t size;
} __attribute__((packed)) ingenic_stage1_debug_t;

typedef struct {
	/* CPU ID */
	uint32_t cpu_id;

	/* PLL args */
	uint8_t ext_clk;
	uint8_t cpu_speed;
	uint8_t phm_div;
	uint8_t use_uart;
	uint32_t baudrate;

	/* SDRAM args */
	uint8_t bus_width;
	uint8_t bank_num;
	uint8_t row_addr;
	uint8_t col_addr;
	uint8_t is_mobile;
	uint8_t is_busshare;

	ingenic_stage1_debug_t debug;
} __attribute__((packed)) firmware_config_t;

typedef struct {
	/* nand flash info */
	uint32_t cpuid; /* cpu type */
	uint32_t nand_bw;		/* bus width */
	uint32_t nand_rc;		/* row cycle */
	uint32_t nand_ps;		/* page size */
	uint32_t nand_ppb;		/* page number per block */
	uint32_t nand_force_erase;
	uint32_t nand_pn;		/* page number in total */
	uint32_t nand_os;		/* oob size */
	uint32_t nand_eccpos;
	uint32_t nand_bbpage;
	uint32_t nand_bbpos;
	uint32_t nand_plane;
	uint32_t nand_bchbit;
	uint32_t nand_wppin;
	uint32_t nand_bpc;		/* block number per chip */
} nand_config_t;

typedef struct {
	uint8_t	vid;
	uint8_t	pid;
	uint8_t	chip;
	uint8_t	page;
	uint8_t	plane;
} nand_info_t;


typedef struct {
	void (*cmdset_change)(uint32_t cmdset, void *arg);
	void (*progress)(int action, int value, int max, void *arg);
} ingenic_callbacks_t;

void *ingenic_open(void *usb_hndl);
void ingenic_close(void *hndl);
void ingenic_set_callbacks(void *hndl, const ingenic_callbacks_t *callbacks, void *arg);

int ingenic_redetect(void *hndl);
int ingenic_cmdset(void *hndl);
int ingenic_type(void *hndl);
uint32_t ingenic_sdram_size(void *hndl);

int ingenic_rebuild(void *hndl);
int ingenic_loadstage(void *hndl, int id, const char *filename);
int ingenic_stage1_debugop(void *device, const char *filename, uint32_t op, uint32_t pin, uint32_t base, uint32_t size);
int ingenic_memtest(void *hndl, const char *filename, uint32_t base, uint32_t size, uint32_t *fail);

int ingenic_configure_stage2(void *hndl);
int ingenic_load_sdram(void *hndl, void *data, uint32_t base, uint32_t size);
int ingenic_load_sdram_file(void *hndl, uint32_t base, const char *filename);
int ingenic_go(void *hndl, uint32_t address);

int ingenic_query_nand(void *hndl, int cs, nand_info_t *info);
int ingenic_dump_nand(void *hndl, int cs, int start, int pages, int type, const char *filename);
int ingenic_program_nand(void *hndl, int cs, int start, int type, const char *filename);
int ingenic_erase_nand(void *hndl, int cs, int start, int blocks);
int ingenic_load_nand(void *hndl, int cs, int start, int pages, uint32_t base);

#endif
