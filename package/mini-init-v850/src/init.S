/*
 * Minimal /init for bringing up v850 before its C library works:
 * write one line through the Linux system call and then wait.
 * System call: number in r12, arguments in r6..r9, trap 0.
 * The message address is loaded the way gcc does it, with a 32-bit
 * immediate, so elf2flt and binfmt_flat have a relocation to process.
 */
	.section .rodata
msg:	.ascii	"Hello from the v850 userland (mini-init)\n"
	.equ	msglen, . - msg

	.text
	.globl _start
_start:
	mov	1, r6			# fd 1
	mov	hilo(msg), r7		# buffer
	movea	msglen, r0, r8		# length
	mov	4, r12			# __NR_write
	trap	0
1:	mov	29, r12			# __NR_pause
	trap	0
	br	1b
