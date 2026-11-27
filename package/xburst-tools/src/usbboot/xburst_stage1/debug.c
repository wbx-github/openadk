/*
 * device board 
 *
 * Copyright 2009 (C) Qi Hardware Inc.,
 * Author: Xiangfu Liu <xiangfu@sharism.cc>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 3 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA
 */

#include "target/jz4760.h"
#include "target/configs.h"
#include "usb_boot_defines.h"

extern struct fw_args *fw_args;

unsigned int check_sdram(unsigned int saddr, unsigned int size)
{
	 unsigned int addr,err = 0;

	serial_puts("\nCheck SDRAM ... \n");
	saddr += 0xa0000000;
	size += saddr;
	serial_put_hex(saddr);
	serial_put_hex(size);
	saddr &= 0xfffffffc;      /* must word align */
	for (addr = saddr; addr < size; addr += 4)
	{
		*(volatile unsigned int *)addr = addr;
		if (*(volatile unsigned int *)addr != addr)
		{
			serial_put_hex(addr);
			err = addr;
		}
	}
	if (err)
		serial_puts("Check SDRAM fail!\n");
	else
		serial_puts("Check SDRAM pass!\n");
	return err;
}

void gpio_test(unsigned char ops, unsigned char pin)
{
	__gpio_as_output(pin);
	if (ops)
	{
		serial_puts("\nGPIO set ");
		serial_put_hex(pin);
		__gpio_set_pin(pin);
	}
	else
	{
		serial_puts("\nGPIO clear ");
		serial_put_hex(pin);
		__gpio_clear_pin(pin);
	}
	/* __gpio_as_input(pin); */
}

void do_debug()
{
	switch (fw_args->debug_ops) {
	case 1:      /* sdram check */
		switch (CPU_ID) {
		case 0x4740:
			gpio_init_4740();
			serial_init();
			sdram_init_4740();
			break;
		case 0x4760:
			gpio_init_4760();
			serial_init();
			sdram_init_4760();
			break;
		default:
			;
		}
		REG8(USB_REG_INDEX) = 1;
		REG32(USB_FIFO_EP1) = check_sdram(fw_args->start, fw_args->size);
		REG32(USB_FIFO_EP1) = 0x0;
		REG8(USB_REG_INCSR) |= USB_INCSR_INPKTRDY;
		break;
	case 2:      /* set gpio */
		gpio_test(1, fw_args->pin_num);
		break;
	case 3:      /* clear gpio */
		gpio_test(0, fw_args->pin_num);
		break;
	}
}
