# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		netperf
PKG_VERSION:=		2.7.0
PKG_RELEASE:=		1
PKG_HASH:=		9170c4758463bc5342dcdbfc88a40b586fcc9d7ccca048ecbb3b2d49387a28b9
PKG_DESCR:=		network performance measurement tools
PKG_SECTION:=		net/perf
PKG_URL:=		http://www.netperf.org/netperf/
PKG_SITES:=		ftp://ftp.netperf.org/netperf/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,NETPERF,netperf,${PKG_VERSION}${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_CFLAGS+=		-fcommon
# uClibc setpgrp does not take arguments
CONFIGURE_ENV+=		ac_cv_func_setpgrp_void=yes

netperf-install:
	${INSTALL_DIR} ${IDIR_NETPERF}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/netperf ${IDIR_NETPERF}/usr/bin/
	${INSTALL_BIN} ${WRKINST}/usr/bin/netserver ${IDIR_NETPERF}/usr/bin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
