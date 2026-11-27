#!/bin/sh
# Generate debian/xburst_stage1.bin, debian/xburst_stage2.bin,
# and debian/changelog.upstream.
#
# Uses debian/changelog and the git revision log.
#
# Requires a mipsel-openwrt-linux- toolchain on the $PATH.

set -e

dpkg-parsechangelog --format rfc822 --all |
	awk -f debian/changelog.upstream.awk

debian/rules firmware
cp -f usbboot/xburst_stage1/xburst_stage1.bin debian/
cp -f usbboot/xburst_stage2/xburst_stage2.bin debian/
cp -f xbboot/target-stage1/stage1.bin debian/
