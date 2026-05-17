# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		tcsh
PKG_VERSION:=		6.24.16
PKG_RELEASE:=		1
PKG_HASH:=		4208cf4630fb64d91d81987f854f9570a5a0e8a001a92827def37d0ed8f37364
PKG_DESCR:=		alternative csh
PKG_SECTION:=		base/shells
PKG_DEPENDS:=		libncurses
PKG_BUILDDEP:=		ncurses
PKG_URL:=		http://www.tcsh.org/Welcome
PKG_SITES:=		https://astron.com/pub/tcsh/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,TCSH,tcsh,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ENV+=		ac_cv_func_setpgrp_void=yes

tcsh-install:
	$(INSTALL_DIR) $(IDIR_TCSH)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/tcsh $(IDIR_TCSH)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
