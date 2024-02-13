# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		sysstat
PKG_VERSION:=		12.7.5
PKG_RELEASE:=		1
PKG_HASH:=		a4d30e37c0c894214b941b51184723e19d492118c946cfdeac74b6d1f0068016
PKG_DESCR:=		system monitoring and performance analysis
PKG_SECTION:=		sys/utils
PKG_SITES:=		https://github.com/sysstat/sysstat/archive/refs/tags/

DISTFILES:=		v$(PKG_VERSION).tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,SYSSTAT,sysstat,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ENV+=		sa_lib_dir=/usr/lib/sa

sysstat-install:
	${INSTALL_DIR} ${IDIR_SYSSTAT}/usr/lib/sa
	${INSTALL_DIR} ${IDIR_SYSSTAT}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/lib/sa/{sa1,sa2,sadc} \
		${IDIR_SYSSTAT}/usr/lib/sa
	${INSTALL_BIN} ${WRKINST}/usr/bin/{sar,sadf,iostat,mpstat} \
		${IDIR_SYSSTAT}/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
