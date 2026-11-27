#
# Authors: Wolfgang Spraul <wolfgang@sharism.cc>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version
# 3 of the License, or (at your option) any later version.
#

ifeq ($(CROSS_COMPILE),)
$(warning CROSS_COMPILE variable not set, should point to .../mipsel-openwrt-linux-)
endif

INCPATH = -I. -I../target-common/
CFLAGS	= -O2 -fno-unit-at-a-time -fno-zero-initialized-in-bss -mips32 -fno-pic \
	  -mno-abicalls $(INCPATH)
LDFLAGS	= -nostdlib -EL -T target.ld 
VPATH   = ../target-common

OBJS	= head.o stage1.o serial.o board-jz4740.o board-jz4760.o

all: stage1.bin

stage1.bin: stage1.elf
	$(CROSS_COMPILE)objcopy -O binary $< $@+
	$(CROSS_COMPILE)objdump -D $< > stage1.dump
	$(CROSS_COMPILE)objdump -h $< > stage1.map
	$(CROSS_COMPILE)nm -n $< > System.map
	chmod -x $@+
	mv -f $@+ $@

stage1.elf: $(OBJS)
	$(CROSS_COMPILE)ld $(LDFLAGS) $(OBJS) -o $@
.c.o:
	$(CROSS_COMPILE)gcc $(CFLAGS) -c $< -o $@
.S.o:
	$(CROSS_COMPILE)gcc $(CFLAGS) -c $< -o $@
clean:
	rm -f stage1.bin stage1.elf stage1.dump stage1.map
	rm -f $(OBJS)
	rm -f System.map
