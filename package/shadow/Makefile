# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		shadow
PKG_VERSION:=		4.14.3
PKG_RELEASE:=		1
PKG_HASH:=		6969279236fe3152768573a38c9f83cb9ca109851a5a990aec1fc672ac2cfcd2
PKG_DESCR:=		utilities to deal with user accounts
PKG_BUILDDEP_GLIBC:=	libxcrypt
PKG_SECTION:=		sys/utils
PKG_SITES:=		https://github.com/shadow-maint/shadow/releases/download/$(PKG_VERSION)/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,SHADOW,shadow,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIGURE_ARGS+=	--without-libbsd

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
