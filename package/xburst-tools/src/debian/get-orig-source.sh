#!/bin/sh
# Build a tarball from the latest upstream version, with a nice
# version number.
#
# Requires tar.

set -e

: ${VERSION=201007}

[ -f xburst-tools_${VERSION}.tar.bz2 ] || \
	wget http://projects.qi-hardware.com/media/upload/xburst-tools/files/xburst-tools_${VERSION}.tar.bz2

mv xburst-tools_${VERSION}.tar.bz2 ../xburst-tools_${VERSION}.orig.tar.bz2
