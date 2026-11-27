//
// Authors: Wolfgang Spraul <wolfgang@sharism.cc>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version
// 3 of the License, or (at your option) any later version.
//

	.text
	.extern pre_main
		
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
	add	$25, $20, 0x40     // t9 = pre_main()
	j	$25
	nop

	.set reorder
