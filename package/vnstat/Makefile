# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		vnstat
PKG_VERSION:=		2.12
PKG_RELEASE:=		1
PKG_HASH:=		b7386b12fc1fc6f47fab31f208b12eda61862e63e229e84e95a6fa80406d2852
PKG_DESCR:=		console-based network traffic monitor
PKG_SECTION:=		net/perf
PKG_SITES:=		http://humdi.net/vnstat/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,VNSTAT,vnstat,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

ALL_TARGET:=		vnstat

vnstat-install:
	${INSTALL_DIR} ${IDIR_VNSTAT}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/vnstat ${IDIR_VNSTAT}/usr/bin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
