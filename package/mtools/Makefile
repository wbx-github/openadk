# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		mtools
PKG_VERSION:=		4.0.18
PKG_RELEASE:=		1
PKG_HASH:=		30d408d039b4cedcd04fbf824c89b0ff85dcbb6f71f13d2d8d65abb3f58cacc3
PKG_DESCR:=		utilities to access fat filesystems
PKG_SECTION:=		sys/fs
PKG_URL:=		https://www.gnu.org/software/mtools/intro.html
PKG_SITES:=		ftp://ftp.gnu.org/gnu/mtools/

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,MTOOLS,mtools,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,MTOOLS,mtools,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ENV+=		ac_cv_func_setpgrp_void=yes

mtools-install:
	${INSTALL_DIR} ${IDIR_MTOOLS}/usr/bin
	${CP} ${WRKINST}/usr/bin/m* ${IDIR_MTOOLS}/usr/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
