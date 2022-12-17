#!/usr/bin/env bash
#-
# Copyright © 2010-2022
#	Waldemar Brodkorb <wbx@openadk.org>
#	Thorsten Glaser <tg@mirbsd.org>
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
# Alternatively, this work may be distributed under the terms of the
# General Public License, any version, as published by the Free Soft-
# ware Foundation.
#-
# Prepare a USB stick or CF/SD/MMC card or hard disc for installation
# of OpenADK

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

if (( USER_ID )); then
	print -u2 Installation is only possible as root!
	exit 1
fi

ADK_TOPDIR=$(realpath .)
ostype=$(uname -s)

fs=ext4
cfgfs=1
datafssz=0
noformat=0
quiet=0
serial=0
speed=115200
panicreboot=10
keep=0
grub=0
paragon_ext=0
datapartcontent=""

function usage {
cat >&2 <<EOF
Syntax: $me [-f filesystem] [-c cfgfssize] [-d datafssize] [-D datafscontent] [-k] [-n] [-g]
    [-p panictime] [±q] [-s serialspeed] [±t] <target> <device> <archive>
Partition sizes are in MiB. Filesystem type is currently ignored (ext4).
To keep filesystem on data partition use -k.
Use -n to not format boot/root partition.
Defaults: -c 1 -p 10 -s 115200; -t = enable serial console
EOF
	exit $1
}
while getopts "c:d:D:ef:ghknp:qs:tx:" ch; do
	case $ch {
	(c)	if (( (cfgfs = OPTARG) < 0 || cfgfs > 16 )); then
			print -u2 "$me: -c $OPTARG out of bounds"
			exit 1
		fi ;;
	(d)	if (( (datafssz = OPTARG) < 0 )); then
			print -u2 "$me: -d $OPTARG out of bounds"
			exit 1
		fi ;;
	(e)	paragon_ext=1 ;;
	(f)	if [[ $OPTARG != @(ext2|ext3|ext4|xfs) ]]; then
			print -u2 "$me: filesystem $OPTARG invalid"
			exit 1
		fi
		fs=$OPTARG ;;
	(h)	usage 0 ;;
	(k)	keep=1 ;;
	(g)	grub=1 ;;
	(p)	if (( (panicreboot = OPTARG) < 0 || panicreboot > 300 )); then
			print -u2 "$me: -p $OPTARG out of bounds"
			exit 1
		fi ;;
	(q)	quiet=1 ;;
	(+q)	quiet=0 ;;
	(s)	if [[ $OPTARG != @(96|192|384|576|1152)00 ]]; then
			print -u2 "$me: serial speed $OPTARG invalid"
			exit 1
		fi
		speed=$OPTARG ;;
	(n)	noformat=1 ;;
	(t)	serial=1 ;;
	(+t)	serial=0 ;;
        (D)	if [[ ! -d $OPTARG ]]; then
			print -u2 "$me: -D $OPTARG must be an existing directory"
			exit 1
		fi
                datapartcontent=$OPTARG;;
	(*)	usage 1 ;;
	}
done
shift $((OPTIND - 1))

(( $# == 3 )) || usage 1

f=0
case $ostype {
(Linux)
	tools="bc mkfs.ext4 mkfs.vfat tune2fs partprobe"
	;;
(Darwin)
	tools="bc diskutil"
	if [[ $paragon_ext == 0 ]]; then
	    export PATH=/usr/local/opt/e2fsprogs/sbin:/usr/local/opt/e2fsprogs/bin:$PATH
	    tools="$tools fuse-ext2 umount mkfs.ext4 tune2fs"
	fi
	;;
(*)
	print -u2 Sorry, not ported to the OS "'$ostype'" yet.
	exit 1
	;;
}
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

target=$1
tgt=$2
src=$3

case $target {
(banana-pro|banana-pro-zero|orange-pi0|pcengines-apu|phytec-imx6|phytec-wega|raspberry-pi|raspberry-pi0|raspberry-pi2|raspberry-pi3|raspberry-pi3-64|raspberry-pi4|raspberry-pi4-64|rockpi4-plus|solidrun-imx6|solidrun-clearfog|imgtec-ci20|default) ;;
(*)
	print -u2 "Unknown target '$target', exiting"
	exit 1 ;;
}
if [[ ! -b $tgt ]]; then
	print -u2 "'$tgt' is not a block device, exiting"
	exit 1
fi
if [[ ! -f $src ]]; then
	print -u2 "'$src' is not a file, exiting"
	exit 1
fi
(( quiet )) || print "Installing $src on $tgt."

case $ostype {
(Darwin)
	R=/Volumes/ADKROOT; diskutil unmount $R || umount $R
	B=/Volumes/ADKBOOT; diskutil unmount $B || umount $B
	D=/Volumes/ADKDATA; diskutil unmount $D || umount $D
	basedev=$tgt
	rootpart=${basedev}s1
	datapart=${basedev}s2
	if [[ $target = raspberry-pi || $target = raspberry-pi0 || $target = raspberry-pi2 || $target = raspberry-pi3 || $target = raspberry-pi3-64 || $target = raspberry-pi4 || $target = raspberry-pi4-64 || $target = phytec-wega ]]; then
		bootpart=${basedev}s1
		rootpart=${basedev}s2
		datapart=${basedev}s3
	fi
	match=\'${basedev}\''?(s+([0-9]))'
	function mount_fs {
	    if [[ $paragon_ext == 0 && $3 = ext4 ]]; then
		mkdir -p $2
		fuse-ext2 "$1" "$2" -o rw+
	    fi
	}
	function umount_fs {
		(( quiet )) || print "Unmounting filesystem on ${1}..."
	    if [[ $paragon_ext == 0 ]]; then
		umount "$1" || diskutil unmount "$1" || true
		rmdir $2 || true
	    else
		diskutil unmount "$1"
	    fi
	}
	function create_fs {
		(( quiet )) || printf "Creating filesystem on ${1}"
	    if [[ $paragon_ext == 0 && $3 = ext4 ]]; then
			mkfs.ext4 -L "$2" "$1"
	    else
			if [[ $3 = ext4 ]]; then
				fstype=UFSD_EXTFS4
			fi
			if [[ $3 = vfat ]]; then
				fstype=fat32
			fi
			diskutil eraseVolume $fstype "$2" "$1"
	    fi
	}
	function tune_fs {
	    if [[ $paragon_ext == 0 && $3 = ext4 ]]; then
			tune2fs -c 0 -i 0 "$1"
	    fi
	}
	;;
(Linux)
	basedev=$tgt
	partitionsep=""
	if [[ $basedev = /dev/loop* ]]; then
		(( quiet )) || print "${tgt} is a loop device"
		partitionsep=p
	fi

	rootpart=${basedev}${partitionsep}1
	datapart=${basedev}${partitionsep}2
	if [[ $target = raspberry-pi || $target = raspberry-pi0 || $target = raspberry-pi2 || $target = raspberry-pi3 || $target = raspberry-pi3-64 || $target = raspberry-pi4 || $target = raspberry-pi4-64 ]]; then
		bootpart=${basedev}${partitionsep}1
		rootpart=${basedev}${partitionsep}2
		datapart=${basedev}${partitionsep}3
	fi

	match=\'${basedev}${partitionsep}\''+([0-9])'
	function mount_fs {
		(( quiet )) || print "Mounting filesystem on ${1}..."
		mount -t "$3" "$1" "$2"
	}
	function umount_fs {
		(( quiet )) || print "Unmounting filesystem on ${1}..."
		umount "$1"
	}
	function create_fs {
		(( quiet )) || print "Creating filesystem on ${1}..."
		mkfs.$3 "$1"
	}
	function tune_fs {
		tune2fs -c 0 -i 0 "$1"
	}
	;;
}

mount |&
while read -p dev rest; do
	eval [[ \$dev = $match ]] || continue
	print -u2 "Block device $tgt is in use, please umount first."
	exit 1
done

if (( !quiet )); then
	print "WARNING: This will overwrite $basedev - type Yes to continue!"
	read x
	[[ $x = Yes ]] || exit 0
fi

if ! T=$(mktemp -d /tmp/openadk.XXXXXXXXXX); then
	print -u2 Error creating temporary directory.
	exit 1
fi
if [[ $ostype != Darwin ]]; then
	R=$T/rootmnt
	B=$T/bootmnt
	D=$T/datamnt
	mkdir -p "$R" "$B" "$D"
fi

# get disk size
dksz=$(dkgetsz "$tgt")

# partition layouts:
# n̲a̲m̲e̲		p̲a̲r̲t̲#̲0̲		p̲̲a̲r̲t̲#̲1̲		p̲̲a̲r̲t̲#̲2̲		p̲̲a̲r̲t̲#̲3̲
# default:	0x83(system)	0x83(?data)	-(unused)	0x88(cfgfs)
# raspberry:	0x0B(boot)	0x83(system)	0x83(?data)	0x88(cfgfs)

syspartno=0

# sizes:
# boot(raspberry) - fixed (100 MiB)
# cfgfs - fixed (parameter, max. 16 MiB)
# data - flexible (parameter)
# system - everything else

if [[ $target = raspberry-pi || $target = raspberry-pi0 || $target = raspberry-pi2 || $target = raspberry-pi3 || $target = raspberry-pi3-64 || $target = raspberry-pi4 || $target = raspberry-pi4-64 || $target = phytec-wega ]]; then
	syspartno=1
	bootfssz=100
	if (( grub )); then
		print -u2 "Cannot combine GRUB with $target"
		rm -rf "$T"
		exit 1
	fi
else
	bootfssz=0
fi

heads=64
secs=32
(( cyls = dksz / heads / secs ))
if (( cyls < (bootfssz + cfgfs + datafssz + 2) )); then
	print -u2 "Size of $tgt is $dksz, this looks fishy?"
	rm -rf "$T"
	exit 1
fi

if stat -qs .>/dev/null 2>&1; then
	statcmd='stat -f %z'	# BSD stat (or so we assume)
else
	statcmd='stat -c %s'	# GNU stat
fi

if (( grub )); then
	tar -xOf "$src" boot/grub/core.img >"$T/core.img"
	integer coreimgsz=$($statcmd "$T/core.img")
else
	coreimgsz=65024
fi
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
(( coreendsec = (coreimgsz + 511) / 512 ))
if [[ $basedev = /dev/svnd+([0-9]) ]]; then
	# BSD svnd0 mode: protect sector #1
	corestartsec=2
	(( ++coreendsec ))
	corepatchofs=$((0x614))
else
	corestartsec=1
	corepatchofs=$((0x414))
fi
# partition offset: at least coreendsec+1 but aligned on a multiple of secs
#(( partofs = ((coreendsec / secs) + 1) * secs ))
# we just use 2048 all the time, since some loaders are longer
partofs=2048
if [[ $target = raspberry-pi || $target = raspberry-pi0 || $target = raspberry-pi2 || $target = raspberry-pi3 || $target = raspberry-pi3-64 || $target = raspberry-pi4 || $target = raspberry-pi4-64 || $target = phytec-wega || $target = rockpi4-plus ]]; then
	(( spartofs = partofs + (100 * 2048) ))
else
	spartofs=$partofs
fi

(( quiet )) || if (( grub )); then
	print Preparing MBR and GRUB2...
else
	print Preparing MBR...
fi
dd if=/dev/zero of="$T/firsttrack" count=$partofs 2>/dev/null
# add another MiB to clear the first partition
dd if=/dev/zero bs=1048576 count=1 >>"$T/firsttrack" 2>/dev/null
echo $corestartsec $coreendsec | mksh "$ADK_TOPDIR/scripts/bootgrub.mksh" \
    -A -g $((cyls - bootfssz - cfgfs - datafssz)):$heads:$secs -M 1:0x83 \
    -O $spartofs | dd of="$T/firsttrack" conv=notrunc 2>/dev/null
(( grub )) && dd if="$T/core.img" of="$T/firsttrack" conv=notrunc \
    seek=$corestartsec 2>/dev/null
# set partition where it can find /boot/grub
(( grub )) && print -n '\0\0\0\0' | \
    dd of="$T/firsttrack" conv=notrunc bs=1 seek=$corepatchofs 2>/dev/null

# create cfgfs partition (mostly taken from bootgrub.mksh)
set -A thecode
typeset -Uui8 thecode
mbrpno=0
set -A g_code $cyls $heads $secs
(( psz = g_code[0] * g_code[1] * g_code[2] ))
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
(( pssz = psz - pofs ))
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
    dd of="$T/firsttrack" conv=notrunc bs=1 seek=$((0x1EE)) 2>/dev/null

if (( datafssz )); then
	# create data partition (copy of the above :)
	set -A thecode
	typeset -Uui8 thecode
	mbrpno=0
	set -A g_code $cyls $heads $secs
	(( psz = (cyls - cfgfs) * g_code[1] * g_code[2] ))
	(( pofs = (cyls - cfgfs - datafssz) * g_code[1] * g_code[2] ))
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
	(( thecode[mbrpno++] = 0x83 ))
	(( thecode[mbrpno++] = g_code[1] - 1 ))
	(( cylno = (g_code[0] - cfgfs) > 1024 ? 1023 : g_code[0] - cfgfs - 1 ))
	(( thecode[mbrpno++] = g_code[2] | ((cylno & 0x0300) >> 2) ))
	(( thecode[mbrpno++] = cylno & 0x00FF ))
	# partition offset, size (LBA)
	(( thecode[mbrpno++] = pofs & 0xFF ))
	(( thecode[mbrpno++] = (pofs >> 8) & 0xFF ))
	(( thecode[mbrpno++] = (pofs >> 16) & 0xFF ))
	(( thecode[mbrpno++] = (pofs >> 24) & 0xFF ))
	(( pssz = psz - pofs ))
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
fi

if [[ $target = raspberry-pi || $target = raspberry-pi0 || $target = raspberry-pi2 || $target = raspberry-pi3 || $target = raspberry-pi3-64 || $target = raspberry-pi4 || $target = raspberry-pi4-64 || $target = phytec-wega ]]; then
	# move system and data partition from #0/#1 to #1/#2
	dd if="$T/firsttrack" bs=1 skip=$((0x1BE)) count=32 of="$T/x" 2>/dev/null
	dd of="$T/firsttrack" conv=notrunc bs=1 seek=$((0x1CE)) if="$T/x" 2>/dev/null
	# create boot partition (copy of the above :)
	set -A thecode
	typeset -Uui8 thecode
	mbrpno=0
	set -A g_code $cyls $heads $secs
	psz=$spartofs
	pofs=$partofs
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
	(( thecode[mbrpno++] = 0x0B ))
	(( thecode[mbrpno++] = g_code[1] - 1 ))
	(( cylno = (spartofs / 2048) > 1024 ? 1023 : (spartofs / 2048) - 1 ))
	(( thecode[mbrpno++] = g_code[2] | ((cylno & 0x0300) >> 2) ))
	(( thecode[mbrpno++] = cylno & 0x00FF ))
	# partition offset, size (LBA)
	(( thecode[mbrpno++] = pofs & 0xFF ))
	(( thecode[mbrpno++] = (pofs >> 8) & 0xFF ))
	(( thecode[mbrpno++] = (pofs >> 16) & 0xFF ))
	(( thecode[mbrpno++] = (pofs >> 24) & 0xFF ))
	(( pssz = psz - pofs ))
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
	    dd of="$T/firsttrack" conv=notrunc bs=1 seek=$((0x1BE)) 2>/dev/null
fi

# disk signature
rnddev=/dev/urandom
[[ -c /dev/arandom ]] && rnddev=/dev/arandom
dd if=$rnddev bs=4 count=1 2>/dev/null | \
    dd of="$T/firsttrack" conv=notrunc bs=1 seek=$((0x1B8)) 2>/dev/null
print -n '\0\0' | \
    dd of="$T/firsttrack" conv=notrunc bs=1 seek=$((0x1BC)) 2>/dev/null
partuuid=$(dd if="$T/firsttrack" bs=1 count=4 skip=$((0x1B8)) 2>/dev/null | \
    hexdump -e '1/4 "%08x"')-0$((syspartno+1))

((keep)) || if (( datafssz )); then
	(( quiet )) || print Cleaning out data partition...
	dd if=/dev/zero of="$tgt" bs=1048576 count=1 seek=$((cyls - cfgfs - datafssz)) > /dev/null 2>&1
fi
(( quiet )) || print Cleaning out root partition...
dd if=/dev/zero bs=1048576 of="$tgt" count=1 seek=$((spartofs / 2048)) > /dev/null 2>&1

(( quiet )) || if (( grub )); then
	print Writing MBR and GRUB2 to target device... system PARTUUID=$partuuid
else
	print Writing MBR to target device... system PARTUUID=$partuuid
fi
dd if="$T/firsttrack" of="$tgt" > /dev/null 2>&1

if [[ $ostype = Linux ]]; then
  echo partprobe $tgt
  partprobe -s $tgt
  sync
  fdisk -l $tgt
  ls -la ${tgt}*
fi

fwdir=$(dirname "$src")

case $target {
(rockpi4-plus)
	dd if="$fwdir/idbloader.img" of="$tgt" bs=512 seek=64 > /dev/null 2>&1
	dd if="$fwdir/u-boot.itb" of="$tgt" bs=512 seek=16384 > /dev/null 2>&1
	;;
(imgtec-ci20)
	dd if="$fwdir/u-boot-spl.bin" of="$tgt" obs=512 seek=1 > /dev/null 2>&1
	dd if="$fwdir/u-boot-dtb.img" of="$tgt" obs=1k seek=14 > /dev/null 2>&1
	;;
(banana-pro|banana-pro-zero|orange-pi0)
	dd if="$fwdir/u-boot-sunxi-with-spl.bin" of="$tgt" bs=1024 seek=8 > /dev/null 2>&1
	;;
(solidrun-clearfog)
	dd if="$fwdir/u-boot-spl.kwb" of="$tgt" bs=512 seek=1 > /dev/null 2>&1
	;;
(solidrun-imx6|phytec-imx6)
	dd if="$fwdir/SPL" of="$tgt" bs=1024 seek=1 > /dev/null 2>&1
	dd if="$fwdir/u-boot.img" of="$tgt" bs=1024 seek=69 > /dev/null 2>&1
	;;
(raspberry-pi|raspberry-pi0|raspberry-pi2|raspberry-pi3|raspberry-pi3-64|raspberry-pi4|raspberry-pi4-64)
	(( noformat )) || create_fs "$bootpart" ADKBOOT vfat
	;;
(phytec-wega)
	(( noformat )) || create_fs "$bootpart" ADKBOOT ext4
	;;
}

(( noformat )) || create_fs "$rootpart" ADKROOT ext4
(( noformat )) || tune_fs "$rootpart"

(( quiet )) || print Extracting installation archive...
mount_fs "$rootpart" "$R" ext4
xz -dc "$src" | (cd "$R"; tar -xpf -)

if (( datafssz )); then
	mkdir -m0755 "$R"/data
	((keep)) || create_fs "$datapart" ADKDATA ext4
	((keep)) || tune_fs "$datapart"
	case $target {
	(raspberry-pi|raspberry-pi0|raspberry-pi2|raspberry-pi3|raspberry-pi3-64|raspberry-pi4|raspberry-pi4-64|phytec-wega)
		echo "/dev/mmcblk0p3	/data	ext4	rw	0	0" >> "$R"/etc/fstab 
	;;
	(banana-pro|orange-pi0|solidrun-clearfog)
		echo "/dev/mmcblk0p2	/data	ext4	rw	0	0" >> "$R"/etc/fstab
	;;
	(solidrun-imx6|phytec-imx6)
		echo "/dev/mmcblk1p2	/data	ext4	rw	0	0" >> "$R"/etc/fstab
	;;
	}
        if [[ -d $datapartcontent ]]; then
            mount_fs "$datapart" "$D" ext4
            # strip trailing slash
            case $datapartcontent in
                *[!/]*/) datapartcontent=${datapartcontent%"${x##*[!/]}"};;
            esac
            cp -R $datapartcontent/* "$D"
        fi
fi

(( quiet )) || print Finishing up with bootloader and kernel ...
case $target {
(raspberry-pi|raspberry-pi0|raspberry-pi2|raspberry-pi3|raspberry-pi3-64|raspberry-pi4|raspberry-pi4-64)
	mount_fs "$bootpart" "$B" vfat
	for x in "$R"/boot/*; do
		[[ -e "$x" ]] && mv -f "$R"/boot/* "$B/"
		break
	done
	for x in "$fwdir"/*.dtb; do
		[[ -e "$x" ]] && cp "$fwdir"/*.dtb "$B/"
		break
	done
        # use static dtoverlay, rename to *.dtb
	mkdir "$B/"overlays
	for x in "$fwdir"/overlays/*.dtbo; do
		y=$(basename ${x} .dtbo)
		[[ -e "$x" ]] && cp "$fwdir"/overlays/${y}.dtbo "$B/"overlays/${y}.dtb
	done
	umount_fs "$B"
	;;
(phytec-wega)
	mount_fs "$bootpart" "$B" ext4
	for x in "$R"/boot/*; do
		[[ -e "$x" ]] && mv -f "$R"/boot/* "$B/"
		break
	done
	for x in "$fwdir"/*.dtb; do
		[[ -e "$x" ]] && cp "$fwdir"/*.dtb "$B/"
		break
	done
	umount_fs "$B"
	;;
(rockpi4-plus)
	for x in "$fwdir"/*.dtb; do
		[[ -e "$x" ]] && cp "$fwdir"/*.dtb "$R/boot/"
		break
	done
	;;
(solidrun-clearfog)
	for x in "$fwdir"/*.dtb; do
		[[ -e "$x" ]] && cp "$fwdir"/*.dtb "$R/boot/"
		break
	done
	mkimage -A arm -O linux -T script -C none -a 0 -e 0 \
		-n "SolidrunClearfog" \
		-d $fwdir/boot.script.clearfog $R/boot/boot.scr.uimg
	;;
(solidrun-imx6)
	for x in "$fwdir"/*.dtb; do
		[[ -e "$x" ]] && cp "$fwdir"/*.dtb "$R/boot/"
		break
	done
	mkimage -A arm -O linux -T script -C none -a 0 -e 0 \
		-n "SolidrunImx6" \
		-d $fwdir/boot.script.imx6 $R/boot/boot.scr.uimg
	;;
(phytec-imx6)
	for x in "$fwdir"/*.dtb; do
		[[ -e "$x" ]] && cp "$fwdir"/*.dtb "$R/boot/"
		break
	done
	mkimage -A arm -O linux -T script -C none -a 0 -e 0 \
		-n "PhytecImx6" \
		-d $fwdir/boot.script.phytec $R/boot/boot.scr.uimg
	;;
(orange-pi0)
	for x in "$fwdir"/*.dtb; do
		[[ -e "$x" ]] && cp "$fwdir"/*.dtb "$R/boot/"
		break
	done
	mkimage -A arm -O linux -T script -C none -a 0 -e 0 \
		-n "OrangePI Zero" \
		-d $fwdir/boot.script.opi $R/boot/boot.scr.uimg
	;;
(banana-pro)
	for x in "$fwdir"/*.dtb; do
		[[ -e "$x" ]] && cp "$fwdir"/*.dtb "$R/boot/"
		break
	done
	mkimage -A arm -O linux -T script -C none -a 0 -e 0 \
		-n "BananaPro" \
		-d $fwdir/boot.script.bpi $R/boot/boot.scr.uimg
	;;
(banana-pro-zero)
	for x in "$fwdir"/*.dtb; do
		[[ -e "$x" ]] && cp "$fwdir"/*.dtb "$R/boot/"
		break
	done
	mkimage -A arm -O linux -T script -C none -a 0 -e 0 \
		-n "BananaProZero" \
		-d $fwdir/boot.script.bpizero $R/boot/boot.scr.uimg
	;;
}

cd "$R"
dd if=$rnddev bs=16 count=1 >>etc/.rnd 2>/dev/null
(( quiet )) || print Fixing up permissions...
chown 0:0 tmp
chmod 1777 tmp
[[ -f usr/bin/sudo ]] && chmod 4755 usr/bin/sudo

if (( grub )); then
	(( quiet )) || print Configuring GRUB2 bootloader...
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
		linuxargs="root=PARTUUID=$partuuid $consargs rootwait"
		(( panicreboot )) && linuxargs="$linuxargs panic=$panicreboot"
		print "\tlinux /boot/kernel $linuxargs"
		print '}'
	) >boot/grub/grub.cfg
fi

(( quiet )) || print Finishing up...
cd "$ADK_TOPDIR"
umount_fs "$R"
if (( datafssz )); then
    umount_fs $datapart
fi
rm -rf "$T"
exit 0
