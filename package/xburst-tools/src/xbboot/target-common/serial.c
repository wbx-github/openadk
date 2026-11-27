//
// Authors: Wolfgang Spraul <wolfgang@sharism.cc>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version
// 3 of the License, or (at your option) any later version.
//

#include "jz4740.h"
#include "serial.h"

void serial_putc(char c)
{
	volatile u8* uart_lsr = (volatile u8*)(UART_BASE + OFF_LSR);
	volatile u8* uart_tdr = (volatile u8*)(UART_BASE + OFF_TDR);

	if (c == '\n') serial_putc ('\r');

	/* Wait for fifo to shift out some bytes */
	while ( !((*uart_lsr & (UART_LSR_TDRQ | UART_LSR_TEMT)) == 0x60) );

	*uart_tdr = (u8) c;
}

void serial_puts(const char *s)
{
	while (*s) serial_putc(*s++);
}

void serial_put_hex(unsigned int v)
{
	unsigned char c[12];
	char i;
	for(i = 0; i < 8;i++)
	{
		c[i] = (v >> ((7 - i) * 4)) & 0xf;
		if(c[i] < 10)
			c[i] += 0x30;
		else
			c[i] += (0x41 - 10);
	}
	c[8] = '\n';
	c[9] = 0;
	serial_puts(c);
}

int serial_getc()
{
	volatile u8* uart_rdr = (volatile u8*)(UART_BASE + OFF_RDR);
	while (!serial_tstc());
	return *uart_rdr;
}

int serial_tstc()
{
	volatile u8* uart_lsr = (volatile u8*)(UART_BASE + OFF_LSR);
	if (*uart_lsr & UART_LSR_DR) {
		/* Data in rfifo */
		return 1;
	}
	return 0;
}
