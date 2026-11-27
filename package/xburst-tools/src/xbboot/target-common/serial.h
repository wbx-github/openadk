//
// Authors: Wolfgang Spraul <wolfgang@sharism.cc>
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version
// 3 of the License, or (at your option) any later version.
//

#ifndef _SERIAL_H_
#define _SERIAL_H_

void serial_putc(char c);
void serial_puts(const char *s);
void serial_put_hex(unsigned int v);
int serial_getc();
int serial_tstc();

#endif
