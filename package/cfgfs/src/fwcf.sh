#!/bin/sh
# Copyright (c) 2006-2007
#	Thorsten Glaser <tg@mirbsd.de>
# Copyright (c) 2009-2024
#	Waldemar Brodkorb <wbx@openadk.org>
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un-
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person's immediate fault when using the work as intended.

# Possible return values:
# 0 - everything ok
# 1 - syntax error
# 1 - no 'cfgfs' mtd/cf/nand partition found
# 1 - cfgfs erase: failed
# 1 - cfgfs setup: already run
# 3 - cfgfs setup: mount --bind problems
# 4 - cfgfs setup: can't create or write to temporary filesystem
# 5 - cfgfs setup: can't bind the tmpfs to /etc
# 6 - cfgfs commit: cannot write to partition
# 6 - cfgfs restore: cannot write to partition
# 7 - cfgfs commit: won't write to flash because of unclean setup
# 8 - cfgfs status: differences found
# 9 - cfgfs status: old status file not found
# 10 - cfgfs dump: failed
# 11 - cfgfs commit: cfgfs setup not yet run (use -f to force)
# 11 - cfgfs status: cfgfs setup not yet run
# 12 - cfgfs restore: cannot read the backup
# 255 - cfgfs erase: failed
# 255 - internal error

export PATH=/bin:/sbin:/usr/bin:/usr/sbin
wd=$(pwd)
cd /
what='Configuration Filesystem Utility (cfgfs), Version 1.12'

who=$(id -u)
if [ $who -ne 0 ]; then
	echo 'Exit. Configuration Filesystem Utility must be run as root.'
	exit 1
fi

usage() {
	cat >&2 <<EOF
$what
Usage:
	{ halt | poweroff | reboot } [-Ffn] [-d delay]
	cfgfs { commit | erase | setup | status | diff | dump | restore } [flags]
EOF
	exit 1
}

case $0 in
(*cfgfs*)	me=cfgfs ;;
(*halt*)	me=halt ;;
(*poweroff*)	me=poweroff ;;
(*reboot*)	me=reboot ;;
(*)		usage ;;
esac

if [[ $me != cfgfs ]]; then
	dval=
	dflag=0
	fflag=0
	nocfgfs=0
	nflag=0
	while getopts ":d:Ffn" ch; do
		case $ch in
		(d)	dflag=1; dval=$OPTARG ;;
		(F)	nocfgfs=1 ;;
		(f)	fflag=1 ;;
		(n)	nflag=1 ;;
		(*)	usage ;;
		esac
	done
	shift $((OPTIND - 1))

	[[ $nocfgfs -eq 0 ]] && [[ $fflag -eq 0 ]] && if ! cfgfs status -q; then
		echo "error: will not $me: unsaved changes in /etc found!"
		echo "Either run 'cfgfs commit' before trying to $me"
		echo "or retry with '$me -F${*+ }$*' to force a ${me}."
		echo "Run 'cfgfs status' to see which files are changed."
		exit 2
	fi

	[[ $fflag -eq 1 ]] && me="$me -f"
	[[ $nflag -eq 1 ]] && me="$me -n"
	[[ $dflag -eq 1 ]] && me="$me -d '$dval'"
	eval exec busybox $me
fi

case $1 in
(commit|erase|setup|status|diff|dump|restore) ;;
(*)	cat >&2 <<EOF
$what
Syntax:
	$0 commit [-f]
	$0 erase
	$0 setup [-N]
	$0 status [-rq]
	$0 diff [<diff options>]
	$0 { dump | restore } [<filename>]
EOF
	exit 1 ;;
esac

mtd=0
if [ -x /sbin/nand ];then
	mtdtool=/sbin/nand
fi

if [ -x /sbin/mtd ];then
	mtdtool=/sbin/mtd
fi

# find backend device, first try to find partition with ID 88
rootdisk=$(rdev|cut -f 1 -d\ )
# strip partitions (f.e. mmcblk0p2, sda2, ..)
rootdisk=${rootdisk%p*}
# do not cut 1-9 from mmcblk device names
echo $rootdisk|grep mmcblk >/dev/null 2>&1
if [ $? -ne 0 ]; then
  rootdisk=${rootdisk%[1-9]}
fi
# find last partition with an 88 id
part=$(fdisk -l $rootdisk 2>/dev/null|awk '{if ($2=="*")  { print $1" "$9} else {print $1" "$8}}'|grep '^/dev.*88.*'|tail -1|awk '{ print $1 }')
if [ -f .cfgfs ]; then
  . /.cfgfs
fi
if [ -z $part ]; then
	part=$(fdisk -l /dev/sda 2>/dev/null|awk '{if ($2=="*")  { print $1" "$9} else {print $1" "$8}}'|grep '^/dev.*88.*'|tail -1|awk '{ print $1 }')
	# find GPT partition
	if [ -z $part ]; then
		partnum=$(gdisk -l $rootdisk 2>/dev/null|fgrep "cfgfs"|awk '{ print $1 }')
		if [ ! -z $partnum ]; then
			echo $rootdisk|grep mmcblk >/dev/null 2>&1
			if [ $? -eq 0 ]; then
				part=${rootdisk}p${partnum}
			else
				part=${rootdisk}${partnum}
			fi
		fi
	fi
	if [ -z $part ]; then
		# otherwise search for MTD device with name cfgfs
		part=/dev/mtd$(fgrep '"cfgfs"' /proc/mtd 2>/dev/null | sed 's/^mtd\([^:]*\):.*$/\1/')ro
		mtd=1
	fi
fi

if [[ ! -e $part ]]; then
	echo 'cfgfs: fatal error: no "cfgfs" partition found!'
	exit 1
fi

if test $1 = erase; then
	dd if="$part" 2>&1 | md5sum 2>&1 >/dev/urandom
	if [ $mtd -eq 1 ]; then
		cfgfs.helper -Me | eval $mtdtool -F write - cfgfs
	else
		cfgfs.helper -Me | cat > $part
	fi
	exit $?
fi

if test $1 = setup; then
	if test -e /tmp/.cfgfs; then
		echo 'cfgfs: error: "cfgfs setup" already run!'
		exit 1
	fi
	mkdir /tmp/.cfgfs
	if test ! -d /tmp/.cfgfs; then
		echo 'cfgfs: error: cannot create temporary directory!'
		exit 4
	fi
	chown 0:0 /tmp/.cfgfs
	chmod 700 /tmp/.cfgfs
	mkdir /tmp/.cfgfs/root
	mount --bind /etc /tmp/.cfgfs/root
	mkdir /tmp/.cfgfs/temp
	mount -t tmpfs none /tmp/.cfgfs/temp
	(cd /tmp/.cfgfs/root; tar cf - .) | (cd /tmp/.cfgfs/temp; tar xpf - 2>/dev/null)
	unclean=0
	if [[ $1 = -N ]]; then
		unclean=2
	else
		x=$(dd if="$part" bs=4 count=1 2>/dev/null)
		[[ "$x" = "FWCF" ]] || \
			if [ $mtd -eq 1 ]; then
				cfgfs.helper -Me | eval $mtdtool -F write - cfgfs
			else
				cfgfs.helper -Me | cat > $part
			fi
		if ! cfgfs.helper -U /tmp/.cfgfs/temp <"$part"; then
			unclean=1
			echo 'cfgfs: error: cannot extract'
			echo unclean startup | logger -t 'cfgfs setup'
		fi
		if test -e /tmp/.cfgfs/temp/.cfgfs_deleted; then
			while IFS= read -r file; do
				rm -f "/tmp/.cfgfs/temp/$file"
			done </tmp/.cfgfs/temp/.cfgfs_deleted
			rm -f /tmp/.cfgfs/temp/.cfgfs_deleted
		fi
	fi
	test $unclean = 0 || echo -n >/tmp/.cfgfs/temp/.cfgfs_unclean
	rm -f /tmp/.cfgfs/temp/.cfgfs_done
	if test -e /tmp/.cfgfs/temp/.cfgfs_done; then
		echo 'cfgfs: fatal: this is not Kansas any more'
		umount /tmp/.cfgfs/temp
		umount /tmp/.cfgfs/root
		rm -rf /tmp/.cfgfs
		exit 3
	fi
	echo -n >/tmp/.cfgfs/temp/.cfgfs_done
	if test ! -e /tmp/.cfgfs/temp/.cfgfs_done; then
		echo 'cfgfs: fatal: cannot write to tmpfs'
		umount /tmp/.cfgfs/temp
		umount /tmp/.cfgfs/root
		rm -rf /tmp/.cfgfs
		exit 4
	fi
	chmod 755 /tmp/.cfgfs/temp
	mount --bind /tmp/.cfgfs/temp /etc
	if test ! -e /etc/.cfgfs_done; then
		umount /etc
		echo 'cfgfs: fatal: binding to /etc failed'
		if test $unclean = 0; then
			echo 'cfgfs: configuration is preserved' \
			    in /tmp/.cfgfs/temp
		else
			umount /tmp/.cfgfs/temp
		fi
		exit 5
	fi
	umount /tmp/.cfgfs/temp
	echo complete, unclean=$unclean | logger -t 'cfgfs setup'
	cd /etc
	rm -f .rnd
	find . -type f | grep -v -e '^./.cfgfs' -e '^./.rnd$' | sort | \
	    xargs md5sum | sed 's!  ./! !' | \
	    cfgfs.helper -Z - /tmp/.cfgfs/status.asz
	exit 0
fi

if test $1 = commit; then
	umount /tmp/.cfgfs/temp >/dev/null 2>&1
	if test ! -e /tmp/.cfgfs; then
		cat >&2 <<-EOF
			cfgfs: error: not yet initialised
			explanation: "cfgfs setup" was not yet run
		EOF
		[[ $1 = -f ]] || exit 11
	fi
	if test -e /etc/.cfgfs_unclean; then
		cat >&2 <<-EOF
			cfgfs: error: unclean startup (or setup run with -N)!
			explanation: during boot, the cfgfs filesystem could not
			    be extracted; saving the current /etc to flash will
			    result in data loss; to override this check, remove
			    the file /etc/.cfgfs_unclean and try again.
		EOF
		[[ $1 = -f ]] || exit 7
	fi
	mount -t tmpfs none /tmp/.cfgfs/temp
	(cd /etc; tar cf - .) | (cd /tmp/.cfgfs/temp; tar xpf - 2>/dev/null)
	cd /tmp/.cfgfs/temp
	find . -type f | grep -v -e '^./.cfgfs' -e '^./.rnd$' | sort | \
	    xargs md5sum | sed 's!  ./! !' | \
	    cfgfs.helper -Z - /tmp/.cfgfs/status.asz
	cd /tmp/.cfgfs/root
	rm -f /tmp/.cfgfs/temp/.cfgfs_* /tmp/.cfgfs/temp/.rnd
	find . -type f | while read f; do
		f=${f#./}
		if [[ ! -e /tmp/.cfgfs/temp/$f ]]; then
			[[ $f = .rnd ]] && continue
			printf '%s\n' "$f" >>/tmp/.cfgfs/temp/.cfgfs_deleted
			continue
		fi
		x=$(md5sum "$f" 2>/dev/null)
		y=$(cd ../temp; md5sum "$f" 2>/dev/null)
		[[ "$x" = "$y" ]] && rm "../temp/$f"
	done
	find /tmp/.cfgfs/temp -type d -empty -delete
	rv=0
	if [ $mtd -eq 1 ]; then
		if ! ( cfgfs.helper -M /tmp/.cfgfs/temp | eval $mtdtool -F write - cfgfs ); then
			echo 'cfgfs: error: cannot write to $part!'
			rv=6
		fi
	else
		if ! ( cfgfs.helper -M /tmp/.cfgfs/temp | cat > $part ); then
			echo 'cfgfs: error: cannot write to $part!'
			rv=6
		fi
	fi
	umount /tmp/.cfgfs/temp
	exit $rv
fi

if test $1 = status; then
	if test ! -e /tmp/.cfgfs; then
		cat >&2 <<-EOF
			cfgfs: error: not yet initialised
			explanation: "cfgfs setup" was not yet run
		EOF
		[[ $1 = -f ]] || exit 11
	fi
	rm -f /tmp/.cfgfs/*_status /tmp/.cfgfs/*_files
	rflag=0
	q=printf	# or : (true) if -q
	shift
	while getopts "rq" ch; do
		case $ch in
		(r)	rflag=1 ;;
		(q)	q=: ;;
		esac
	done
	shift $((OPTIND - 1))
	if test $rflag = 1; then
		f=/tmp/.cfgfs/rom_status
		cd /tmp/.cfgfs/root
		find . -type f | grep -v -e '^./.cfgfs' -e '^./.rnd$' | sort | \
		    xargs md5sum | sed 's!  ./! !' >$f
	else
		f=/tmp/.cfgfs/status
		cfgfs.helper -Zd $f.asz $f || rm -f $f
	fi
	if [[ ! -e $f ]]; then
		echo 'cfgfs: error: old status file not found'
		exit 9
	fi
	cd /etc
	find . -type f | grep -v -e '^./.cfgfs' -e '^./.rnd$' | sort | \
	    xargs md5sum | sed 's!  ./! !' >/tmp/.cfgfs/cur_status || exit 255
	cd /tmp/.cfgfs
	sed 's/^[0-9a-f]* //' <$f >old_files
	sed 's/^[0-9a-f]* //' <cur_status >cur_files
	# make *_status be of exactly the same length, for benefit of the
	# while ... read <old, read <new loop below, and sort it
	comm -23 old_files cur_files | while read name; do
		echo "<NULL> $name" >>cur_status
	done
	comm -13 old_files cur_files | while read name; do
		echo "<NULL> $name" >>$f
	done
	# this implementation of sort -o sucks: doesn't do in-place edits
	# workaround a busybox bug?
	touch sold_status snew_status
	sort -k2 -o sold_status $f
	sort -k2 -o snew_status cur_status
	gotany=0
	while :; do
		IFS=' ' read oldsum oldname <&3 || break
		IFS=' ' read newsum newname <&4 || exit 255
		[[ "$oldname" = "$newname" ]] || exit 255
		[[ "$oldsum" = "$newsum" ]] && continue
		[[ $gotany = 0 ]] && $q '%-32s %-32s %s\n' \
		    'MD5 hash of old file' 'MD5 hash of new file' 'filename'
		gotany=8
		test $q = : && break
		$q '%32s %32s %s\n' "$oldsum" "$newsum" "$oldname"
	done 3<sold_status 4<snew_status
	rm -f /tmp/.cfgfs/*_status /tmp/.cfgfs/*_files
	exit $gotany
fi

if test $1 = dump; then
	fn=$2
	[[ -n $fn ]] || fn=-
	rm -rf /tmp/.cfgfs.dump
	mkdir -m 0700 /tmp/.cfgfs.dump
	cd /tmp/.cfgfs.dump
	if ! cat "$part" | cfgfs.helper -UD dump; then
		cd /
		rm -rf /tmp/.cfgfs.dump
		exit 10
	fi
	dd if=/dev/urandom of=seed bs=256 count=1 >/dev/null 2>&1
	tar -cf - dump seed | (cd "$wd"; cfgfs.helper -Z - $fn)
	cd /
	rm -rf /tmp/.cfgfs.dump
	case $fn in
	(-)	echo "cfgfs: dump to standard output complete."
		;;
	(*)	echo "cfgfs: dump to '$fn' complete."
		ls -l "$fn" >&2
		;;
	esac
	exit 0
fi

if test $1 = restore; then
	if test -e /tmp/.cfgfs; then
		echo 'cfgfs: warning: "cfgfs setup" already run!'
		echo 'please reboot after restoring; in no event'
		echo 'run "cfgfs commit" to prevent data loss'
		echo -n >/etc/.cfgfs_unclean
	fi
	fn=$2
	[[ -n $fn ]] || fn=-
	rm -rf /tmp/.cfgfs.restore
	mkdir -m 0700 /tmp/.cfgfs.restore
	cd /tmp/.cfgfs.restore
	if ! (cd "$wd"; cfgfs.helper -Zd "$fn") | tar -xf -; then
		cd /
		rm -rf /tmp/.cfgfs.restore
		exit 12
	fi
	dd if=seed of=/dev/urandom bs=256 count=1 >/dev/null 2>&1
	if test ! -e dump; then
		echo 'cfgfs: error: invalid backup'
		cd /
		rm -rf /tmp/.cfgfs.restore
		exit 12
	fi
	if [ $mtd -eq 1 ]; then
		if ! ( cfgfs.helper -MD dump | eval $mtdtool -F write - cfgfs ); then
			echo 'cfgfs: error: cannot write to $part!'
			exit 6
		fi
	else
		if ! ( cfgfs.helper -MD dump | cat > $part ); then
			echo 'cfgfs: error: cannot write to $part!'
			exit 6
		fi
	fi
	cd /
	rm -rf /tmp/.cfgfs.restore
	case $fn in
	(-)	echo "cfgfs: restore from standard output complete."
		;;
	(*)	echo "cfgfs: restore from '$fn' complete."
		ls -l "$fn" >&2
		;;
	esac
	exit 0
fi

if test $1 = diff; then
	if test ! -e /tmp/.cfgfs; then
		cat >&2 <<-EOF
			cfgfs: error: not yet initialised
			explanation: "cfgfs setup" was not yet run
		EOF
		[[ $1 = -f ]] || exit 11
	fi
	shift
	tempd=/tmp/.cfgfs/temp
	mount -t tmpfs none $tempd
	(cd /tmp/.cfgfs/root; tar cf - .) | (cd $tempd; tar xpf - 2>/dev/null)
	x=$(dd if="$part" bs=4 count=1 2>/dev/null)
	[[ "$x" = "FWCF" ]] && cfgfs.helper -U $tempd <"$part"

	if test -e $tempd/.cfgfs_deleted; then
		while IFS= read -r file; do
			rm -f "$tempd/$file"
		done <$tempd/.cfgfs_deleted
		rm -f $tempd/.cfgfs_deleted
	fi
	(cd /etc; find . -type f; \
	 cd $tempd; find . -type f \
	) | grep -v -e '^./.cfgfs' -e '^./.rnd$' | sort -u | while read f; do
		f=${f#./}
		if [ ! -e "/etc/$f" ]; then
			echo "Deleted: /etc/$f"
		elif [ ! -e "$tempd/$f" ]; then
			echo "New: /etc/$f"
		else
			diff "$@" "$tempd/$f" "/etc/$f"
		fi
	done
	umount $tempd
	exit 0
fi

echo 'cfgfs: cannot be reached...'
exit 255
