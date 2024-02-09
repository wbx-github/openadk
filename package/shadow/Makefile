# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		shadow
PKG_VERSION:=		4.13
PKG_RELEASE:=		1
PKG_HASH:=		9afe245d79a2e7caac5f1ed62519b17416b057ec89df316df1c3935502f9dd2c
PKG_DESCR:=		utilities to deal with user accounts
PKG_BUILDDEP_GLIBC:=	libxcrypt
PKG_SECTION:=		sys/utils
PKG_SITES:=		https://github.com/shadow-maint/shadow/releases/download/4.13/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,SHADOW,shadow,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

shadow-install:
	$(INSTALL_DIR) $(IDIR_SHADOW)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/* \
		$(IDIR_SHADOW)/usr/bin
	$(INSTALL_DIR) $(IDIR_SHADOW)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/* \
		$(IDIR_SHADOW)/usr/sbin
	$(INSTALL_DIR) $(IDIR_SHADOW)/lib
	$(CP) $(WRKINST)/lib/*.so* \
		$(IDIR_SHADOW)/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
