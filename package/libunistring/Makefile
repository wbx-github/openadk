# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		libunistring
PKG_VERSION:=		0.9.10
PKG_RELEASE:=		1
PKG_HASH:=		eb8fb2c3e4b6e2d336608377050892b54c3c983b646c561836550863003c05d7
PKG_DESCR:=		functions for manipulating unicode strings
PKG_SECTION:=		libs/misc
PKG_URL:=		http://www.gnu.org/software/libunistring/
PKG_SITES:=		${MASTER_SITE_GNU:=libunistring/}
PKG_OPTS:=		dev

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LIBUNISTRING,libunistring,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

libunistring-install:
	${INSTALL_DIR} ${IDIR_LIBUNISTRING}/usr/lib
	${CP} ${WRKINST}/usr/lib/libunistring.so* ${IDIR_LIBUNISTRING}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
