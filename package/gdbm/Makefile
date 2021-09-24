# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		gdbm
PKG_VERSION:=		1.21
PKG_RELEASE:=		1
PKG_HASH:=		b0b7dbdefd798de7ddccdd8edf6693a30494f7789777838042991ef107339cc2
PKG_DESCR:=		disk file format database
PKG_SECTION:=		libs/db
PKG_URL:=		http://www.gnu.org/software/gdbm/
PKG_SITES:=		${MASTER_SITE_GNU:=gdbm/}
PKG_LIBNAME:=		libgdbm
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LIBGDBM,libgdbm,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

XAKE_FLAGS+=		BINOWN=`id -u` \
			BINGRP=`id -g` \
			INSTALL_ROOT="${WRKINST}"

libgdbm-install:
	${INSTALL_DIR} ${IDIR_LIBGDBM}/usr/lib
	${CP} ${WRKINST}/usr/lib/libgdbm.so* ${IDIR_LIBGDBM}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
