#!/usr/bin/env bash
#-
# Copyright © 2010, 2011, 2012
#	Thorsten Glaser <tg@mirbsd.org>
# Copyright © 2010-2023
#	Waldemar Brodkorb <wbx@openadk.org>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un‐
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# This work is provided “AS IS” and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person’s immediate fault when using the work as intended.
#
# Alternatively, this work may be distributed under the Terms of the
# General Public License, any version as published by the Free Soft‐
# ware Foundation.
#-
# Create a hard disc image, bootable using GNU GRUB2, with an ext2fs
# root partition and an OpenADK cfgfs partition.

ADK_TOPDIR=$(pwd)
HOST=$(gcc -dumpmachine)
me=$0

case :$PATH: in
(*:$ADK_TOPDIR/host_$HOST/usr/bin:*) ;;
(*) export PATH=$PATH:$ADK_TOPDIR/host_$HOST/usr/bin ;;
esac

test -n "$KSH_VERSION" || exec mksh "$me" "$@"
if test -z "$KSH_VERSION"; then
	echo >&2 Fatal error: could not run myself with mksh!
	exit 255
fi

### run with mksh from here onwards ###

me=${me##*/}

ADK_TOPDIR=$(realpath .)
ostype=$(uname -s)

function usage {
	cat >&2 <<EOF
Syntax: $me [-c cfgfssize] [+g] [-i imagesize] [-p panictime]
    [-s serialspeed] [-t] [-T imagetype] [+U] target.ima source.tgz
Explanation/Defaults:
	-c: minimum 0, maximum 5, default 1 (MiB)
	-g: enable installing GNU GRUB 2
	-i: total image, default 2048 (MiB; max. approx. 2 TiB)
	-p: default 10 (seconds; 0 disables; max. 300)
	-s: default 115200 (bps, others: 9600 19200 38400 57600)
	-t: enable serial console (+t disables it, default)
	-T: image type (default raw, others: vdi)
EOF
	exit ${1:-1}
}

cfgfs=1
usegrub=0
tgtmib=2048
panicreboot=10
speed=115200
serial=0
tgttype=raw

while getopts "c:ghi:p:s:tT:" ch; do
	case $ch {
	(c)	if (( (cfgfs = OPTARG) < 0 || cfgfs > 5 )); then
			print -u2 "$me: -c $OPTARG out of bounds"
			usage
		fi ;;
	(g)	usegrub=1 ;;
	(h)	usage 0 ;;
	(i)	if (( (tgtmib = OPTARG) < 7 || tgtmib > 2097150 )); then
			print -u2 "$me: -i $OPTARG out of bounds"
			usage
		fi ;;
	(p)	if (( (panicreboot = OPTARG) < 0 || panicreboot > 300 )); then
			print -u2 "$me: -p $OPTARG out of bounds"
			usage
		fi ;;
	(s)	if [[ $OPTARG != @(96|192|384|576|1152)00 ]]; then
			print -u2 "$me: serial speed $OPTARG invalid"
			usage
		fi
		speed=$OPTARG ;;
	(t)	serial=1 ;;
	(+t)	serial=0 ;;
	(T)	if [[ $OPTARG != @(raw|vdi) ]]; then
			print -u2 "$me: image type $OPTARG invalid"
			usage
		fi
		tgttype=$OPTARG ;;
	(*)	usage 1 ;;
	}
done
shift $((OPTIND - 1))

(( $# == 2 )) || usage 1

f=0
tools='bc genext2fs'
[[ $tgttype = vdi ]] && tools="$tools VBoxManage"
for tool in $tools; do
	print -n Checking if $tool is installed...
	if whence -p $tool >/dev/null; then
		print " okay"
	else
		print " failed"
		f=1
	fi
done
(( f )) && exit 1
if bc --help >/dev/null 2>&1; then
	# GNU bc shows a “welcome message” which irritates scripts
	bc='bc -q'
else
	bc=bc
fi

tgt=$1
[[ $tgt = /* ]] || tgt=$PWD/$tgt
src=$2

if [[ ! -f $src ]]; then
	print -u2 "'$src' is not a file, exiting"
	exit 1
fi
if ! T=$(mktemp -d /tmp/openadk.XXXXXXXXXX); then
	print -u2 Error creating temporary directory.
	exit 1
fi
print "Installing $src on $tgt."

cyls=$tgtmib
heads=64
secs=32
if stat -qs .>/dev/null 2>&1; then
	statcmd='stat -f %z'	# BSD stat (or so we assume)
else
	statcmd='stat -c %s'	# GNU stat
fi

if (( usegrub )); then
	tar -xOJf "$src" boot/grub/core.img >"$T/core.img"
	integer coreimgsz=$($statcmd "$T/core.img")
	if (( coreimgsz < 1024 )); then
		print -u2 core.img is probably too small: $coreimgsz
		rm -rf "$T"
		exit 1
	fi
	if (( coreimgsz > 65024 )); then
		print -u2 core.img is larger than 64K-512: $coreimgsz
		rm -rf "$T"
		exit 1
	fi
else
	# fake it
	integer coreimgsz=1
fi
(( coreendsec = (coreimgsz + 511) / 512 ))
corestartsec=1
corepatchofs=$((0x414))
# partition offset: at least coreendsec+1 but aligned on a multiple of secs
(( partofs = ((coreendsec / secs) + 1) * secs ))
# calculate size of ext2fs in KiB as image size minus cfgfs minus firsttrack
((# partfssz = ((cyls - cfgfs) * 64 * 32 - partofs) / 2 ))

if (( usegrub )); then
	print Preparing MBR and GRUB2...
else
	print Preparing partition table...
fi
dd if=/dev/zero of="$T/firsttrack" count=$partofs 2>/dev/null
echo $corestartsec $coreendsec | mksh "$ADK_TOPDIR/scripts/bootgrub.mksh" \
    -A -g $((cyls - cfgfs)):$heads:$secs -M 1:0x83 -O $partofs | \
    dd of="$T/firsttrack" conv=notrunc 2>/dev/null
if (( usegrub )); then
	dd if="$T/core.img" of="$T/firsttrack" conv=notrunc \
	    seek=$corestartsec 2>/dev/null
	# set partition where it can find /boot/grub
	print -n '\0\0\0\0' | \
	    dd of="$T/firsttrack" conv=notrunc bs=1 seek=$corepatchofs \
	    2>/dev/null
fi

# create cfgfs partition (mostly taken from bootgrub.mksh)
set -A thecode
typeset -Uui8 thecode
mbrpno=0
set -A g_code $cyls $heads $secs
(( pssz = cfgfs * g_code[1] * g_code[2] ))
(( pofs = (cyls - cfgfs) * g_code[1] * g_code[2] ))
set -A o_code	# g_code equivalent for partition offset
(( o_code[2] = pofs % g_code[2] + 1 ))
(( o_code[1] = pofs / g_code[2] ))
(( o_code[0] = o_code[1] / g_code[1] + 1 ))
(( o_code[1] = o_code[1] % g_code[1] + 1 ))
# boot flag; C/H/S offset
thecode[mbrpno++]=0x00
(( thecode[mbrpno++] = o_code[1] - 1 ))
(( cylno = o_code[0] > 1024 ? 1023 : o_code[0] - 1 ))
(( thecode[mbrpno++] = o_code[2] | ((cylno & 0x0300) >> 2) ))
(( thecode[mbrpno++] = cylno & 0x00FF ))
# partition type; C/H/S end
(( thecode[mbrpno++] = 0x88 ))
(( thecode[mbrpno++] = g_code[1] - 1 ))
(( cylno = g_code[0] > 1024 ? 1023 : g_code[0] - 1 ))
(( thecode[mbrpno++] = g_code[2] | ((cylno & 0x0300) >> 2) ))
(( thecode[mbrpno++] = cylno & 0x00FF ))
# partition offset, size (LBA)
(( thecode[mbrpno++] = pofs & 0xFF ))
(( thecode[mbrpno++] = (pofs >> 8) & 0xFF ))
(( thecode[mbrpno++] = (pofs >> 16) & 0xFF ))
(( thecode[mbrpno++] = (pofs >> 24) & 0xFF ))
(( thecode[mbrpno++] = pssz & 0xFF ))
(( thecode[mbrpno++] = (pssz >> 8) & 0xFF ))
(( thecode[mbrpno++] = (pssz >> 16) & 0xFF ))
(( thecode[mbrpno++] = (pssz >> 24) & 0xFF ))
# write partition table entry
ostr=
curptr=0
while (( curptr < 16 )); do
	ostr=$ostr\\0${thecode[curptr++]#8#}
done
print -n "$ostr" | \
    dd of="$T/firsttrack" conv=notrunc bs=1 seek=$((0x1CE)) 2>/dev/null

print Extracting installation archive...
mkdir "$T/src"
xz -dc "$src" | (cd "$T/src"; tar -xpf -)
cd "$T/src"
rnddev=/dev/urandom
[[ -c /dev/arandom ]] && rnddev=/dev/arandom
dd if=$rnddev bs=16 count=1 >>etc/.rnd 2>/dev/null
print Fixing up permissions...
chmod 1777 tmp
[[ -f usr/bin/sudo ]] && chmod 4755 usr/bin/sudo

if (( usegrub )); then
	print Configuring GRUB2 bootloader...
	mkdir -p boot/grub
	(
		print set default=0
		print set timeout=1
		if (( serial )); then
			print serial --unit=0 --speed=$speed
			print terminal_output serial
			print terminal_input serial
			consargs="console=ttyS0,$speed console=tty0"
		else
			print terminal_output console
			print terminal_input console
			consargs="console=tty0"
		fi
		print
		print 'menuentry "GNU/Linux (OpenADK)" {'
		linuxargs="root=/dev/sda1 $consargs"
		(( panicreboot )) && linuxargs="$linuxargs panic=$panicreboot"
		print "\tlinux /boot/kernel $linuxargs"
		print '}'
	) >boot/grub/grub.cfg
fi

print "Creating ext2fs filesystem image..."
cd "$T"
f=0
genext2fs -U -N 65536 -b $((partfssz)) -d src fsimg || f=1
if (( !f )); then
	# use bc(1): this may be over the shell’s 32-bit arithmetics
	wantsz=$($bc <<<"$((partfssz))*1024")
	gotsz=$($statcmd fsimg)
	if [[ $wantsz != "$gotsz" ]]; then
		print -u2 "Error: want $wantsz bytes, got $gotsz bytes!"
		f=1
	fi
fi
if (( f )); then
	print -u2 "Error creating ext2fs filesystem image"
	cd /
	rm -rf "$T"
	exit 1
fi
# delete source tree, to save disc space
rm -rf src

if [[ $tgttype = raw ]]; then
	tgttmp=$tgt
else
	tgttmp=$T/dst.ima
fi
print "Putting together raw output image $tgttmp..."
dd if=/dev/zero bs=1048576 count=$cfgfs 2>/dev/null | \
    cat firsttrack fsimg - >"$tgttmp"
# use bc(1): this may be over the shell’s 32-bit arithmetics
wantsz=$($bc <<<"$tgtmib*1048576")
gotsz=$($statcmd "$tgttmp")
if [[ $wantsz != "$gotsz" ]]; then
	print -u2 "Error: want $wantsz bytes, got $gotsz bytes!"
	cd /
	rm -rf "$T"
	exit 1
fi

case $tgttype {
(raw)
	;;
(vdi)
	print "Converting raw image to VDI..."
	VBoxManage convertdd dst.ima dst.vdi
	rm dst.ima
	print "Moving VDI image to $tgt.vdi..."
	mv -f dst.vdi "$tgt".vdi
	;;
}

print Finishing up...
cd "$ADK_TOPDIR"
rm -rf "$T"
exit 0
