AM_CFLAGS = -Wall -W -std=gnu99 -DDATADIR=\"$(pkgdatadir)\"

bin_PROGRAMS = xbboot
xbboot_SOURCES = host_main.c

pkgdatadir = $(datadir)/xburst-tools/

if COND_FIRMWARE
pkgdata_DATA = ../target-stage1/stage1.bin
endif

EXTRA_DIST = $(pkgdatadir)

../target-stage1/stage1.bin:
	$(MAKE) CROSS_COMPILE=$(CROSS_COMPILE) -C ../target-stage1

clean-local:
	$(MAKE) CROSS_COMPILE=$(CROSS_COMPILE) -C ../target-stage1 clean
