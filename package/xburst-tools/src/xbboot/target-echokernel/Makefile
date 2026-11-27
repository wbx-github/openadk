#
# Authors: Wolfgang Spraul <wolfgang@sharism.cc>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version
# 3 of the License, or (at your option) any later version.
#

ifeq ($(CROSS_COMPILE),)
$(error CROSS_COMPILE variable not set, should point to .../mipsel-openwrt-linux-)
endif

CC	= $(CROSS_COMPILE)gcc
AR	= $(CROSS_COMPILE)ar rcsv
LD	= $(CROSS_COMPILE)ld
OBJCOPY	= $(CROSS_COMPILE)objcopy
NM	= $(CROSS_COMPILE)nm
OBJDUMP	= $(CROSS_COMPILE)objdump

DEBUG_CFLAGS = -g -Wa,-a=$(basename $@).lst
# Wolfgang saw data corruptions in stage2 when dealing with ECC data on random writes
# to NAND. Disabling the unit-at-a-time optimization reproducibly fixed the bug.
# The compiler may be optimizing in a way that conflicts with how the hardware ECC
# registers work. Since other register accesses might be affected too it seems the best
# is to disable this optimization right now.
CFLAGS	= -mips32 -O2 -fno-exceptions -fno-unit-at-a-time -fno-zero-initialized-in-bss \
	-ffunction-sections -fomit-frame-pointer -msoft-float -G 0 $(DEBUG_CFLAGS) -fPIC
LDFLAGS	= -nostdlib -T target.ld $(CFLAGS)
LIBS	= -lstdc++ -lc -lm -lgcc
VPATH   = ../target-common

OBJS	= echo-kernel.o serial.o

all: echo-kernel.elf
	$(OBJCOPY) -O binary echo-kernel.elf echo-kernel.bin
	$(OBJDUMP) -D echo-kernel.elf > echo-kernel.dump
	$(NM) echo-kernel.elf | sort > echo-kernel.sym
	$(OBJDUMP) -h echo-kernel.elf > echo-kernel.map

echo-kernel.elf: head.o $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<
.cpp.o:
	$(CC) $(CFLAGS) -fno-rtti -fvtable-gc -o $@ -c $<
.S.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(addprefix echo-kernel., bin dump elf map sym)
	rm -f head.o head.lst $(OBJS) $(OBJS:.o=.lst)
