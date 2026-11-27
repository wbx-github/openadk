//
// Authors: Wolfgang Spraul <wolfgang@sharism.cc>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version
// 3 of the License, or (at your option) any later version.
//

#include "../target-common/serial.h"
#include "../target-common/common.h"

void pre_main(void)
{
	volatile unsigned int start_addr, got_start, got_end, addr, offset;

	/* get absolute start address  */
	__asm__ __volatile__(			
		"move %0, $20\n\t"
		: "=r"(start_addr)
		: 
		);			

	/* get related GOT address  */
	__asm__ __volatile__(			
		"la $4, _GLOBAL_OFFSET_TABLE_\n\t"
		"move %0, $4\n\t"
		"la $5, _got_end\n\t"
		"move %1, $5\n\t"
		: "=r"(got_start),"=r"(got_end)
		: 
		);			

	/* calculate offset and correct GOT*/
	offset = start_addr - 0x80000000;	
 	got_start += offset;
	got_end  += offset;

	for ( addr = got_start + 8; addr < got_end; addr += 4 )
		*((volatile unsigned int *)(addr)) += offset; // add offset to correct all GOT

//	fw_args = (struct fw_args *)(start_addr + 0x8);       //get the fw args from memory
	UART_BASE = 0xB0030000 + 0x1000;
	serial_puts("Start address is:");
	serial_put_hex(start_addr);
	serial_puts("Address offset is:");
	serial_put_hex(start_addr - 0x80000000);
	serial_puts("GOT corrected to:");
	serial_put_hex(got_start);
	c_main();
}

void c_main()
{
	// start infinite 'echo' kernel
	while (1) {
		if (serial_tstc()) {
			int c = serial_getc();
			serial_putc(c);
			if (c == '\r')
				serial_putc('\n');
		}
	}
}
