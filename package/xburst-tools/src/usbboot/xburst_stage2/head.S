/*
 * head.S
 *
 * Entry point of the firmware.
 * The firmware code are executed in the ICache.
 * Do not edit!
 * Copyright (C) 2006 Ingenic Semiconductor Inc.
 *
 */

	.text
	.extern c_main
		
	.globl _start
	.set noreorder
_start:
	b	real_start
	nop
	.word	0x0                  //	its address == start address + 8
	.word	0x0
	.word	0x0
	.word	0x0
	.word	0x0
	.word	0x0
	.word	0x0
	.word	0x0

real_start:	
	/* setup stack, jump to C code */
	add	$29, $20, 0x3ffff0 // sp locate at start address offset 0x2ffff0
	add	$25, $20, 0x40     // t9 = usb_main()
	j	$25
	nop

	.set reorder
