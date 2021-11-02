#!/usr/bin/env bash
#
# Patch sources using git-am, aligning things to use git-format-patch for
# update-patches.
#
# (c) 2021 Phil Sutter <phil@nwl.cc>
#
# Based on the classic patch.sh, written by:
#
# (c) 2006, 2007 Thorsten Glaser <tg@freewrt.org>
# (c) 2002 Erik Andersen <andersen@codepoet.org>

[[ -n $BASH_VERSION ]] && shopt -s extglob

# Set directories from arguments, or use defaults.
targetdir=${1-.}
patchdir=${2-../patches}
patchpattern=${3-*}

if [ ! -d "${targetdir}" ] ; then
    echo "Aborting.  '${targetdir}' is not a directory."
    exit 1
fi
if [ ! -d "${patchdir}" ] ; then
    echo "Aborting.  '${patchdir}' is not a directory."
    exit 0
fi

wd=$(pwd)

cd "${targetdir}"
if [ ! -d .git ]; then
    # drop leftover .gitignores in non-git sources, they
    # might prevent us from patching 'temporary' files
    # which are still present in the tarball.
    find . -name .gitignore -delete
    git init
    git add .
elif [ -e .git/rebase-apply ]; then
    git am --abort
fi

i=0
patch_tmp=$(printf ".git/patch_tmp/%04d" $i)
while [ -d $patch_tmp ]; do
	let "i++"
	patch_tmp=$(printf ".git/patch_tmp/%04d" $i)
done
mkdir -p $patch_tmp
patch_series=$(printf "%04d" $i)

git commit --allow-empty --no-signoff --no-gpg-sign \
    --author="OpenADK <wbx@openadk.org>" \
    -m "OpenADK patch marker: $patch_series"

cd $wd
cd $patchdir
for i in $(eval echo ${patchpattern}); do
    test -e "$i" || continue
    i=$patchdir/$i
    cd $wd
    case $i in
	*.gz)
	type="gzip"; uncomp="gunzip -dc"; ;;
	*.bz)
	type="bzip"; uncomp="bunzip -dc"; ;;
	*.bz2)
	type="bzip2"; uncomp="bunzip2 -dc"; ;;
	*.zip)
	type="zip"; uncomp="unzip -d"; ;;
	*.Z)
	type="compress"; uncomp="uncompress -c"; ;;
	*)
	type="plaintext"; uncomp="cat"; ;;
    esac
    [ -d "${i}" ] && echo "Ignoring subdirectory ${i}" && continue
    echo "$(basename $i)" >>${targetdir}/${patch_tmp}/__patchfiles__
    patchname="$(basename -s .gz -s .bz -s .bz2 -s .zip -s .Z -s .patch $i)"
    {
        if ! grep -q '^Subject: ' ${i}; then
            echo "From: OpenADK <wbx@openadk.org>"
            echo "Subject: [PATCH] ${patchname#[0-9]*-}"
            echo ""
        fi
        ${uncomp} ${i}
    } >${targetdir}/${patch_tmp}/${patchname}.patch
    cd $patchdir
done

# no patches to apply? bail out
[ -e ${targetdir}/${patch_tmp}/__patchfiles__ ] || {
	rmdir ${targetdir}/${patch_tmp}
	exit 0
}

# provide backwards compatibility to old style using 'patch' program
# XXX: this is unsafe and should be dropped at some point
am_opts="-C1"

cd ${wd}
realpath $patchdir >${targetdir}/${patch_tmp}/__patchdir__
cd ${targetdir}
git am $am_opts ${patch_tmp}/*.patch
if [ $? != 0 ] ; then
    echo "git-am failed! Please fix patches!"
    exit 1
fi
