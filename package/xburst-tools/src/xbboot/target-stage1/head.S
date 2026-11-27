//
// Authors: Wolfgang Spraul <wolfgang@sharism.cc>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version
// 3 of the License, or (at your option) any later version.
//

	.text
	.extern c_main
	.globl _start
	.set noreorder

_start:
	b	real_start
	nop
	// 8 words for firmware parameters (0x80002008)
	.word	0x0
	.word	0x0
	.word	0x0
	.word	0x0
	.word	0x0
	.word	0x0
	.word	0x0
	.word	0x0

real_start:		
	li $8, 0x0040FC04
	mtc0 $8, $12 // CP0_STATUS

	li $9, 0x00800000
	mtc0 $9, $13 // CP0_CAUSE 

	la	$29, 0x80004000	// setup stack (sp)
	j	c_main
	nop

	.set reorder
