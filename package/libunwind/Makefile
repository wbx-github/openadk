# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libunwind
PKG_VERSION:=		1.8.3
PKG_RELEASE:=		1
PKG_HASH:=		be30d910e67f58d82e753231f1357f326a1a088acf126b21ff77e60aab19b90b
PKG_DESCR:=		determine the call-chain of a program
PKG_SECTION:=		libs/misc
PKG_SITES:=		https://github.com/libunwind/libunwind/releases/download/v$(PKG_VERSION)/
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBUNWIND,libunwind,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIGURE_ARGS+=	--disable-tests

libunwind-install:
	$(INSTALL_DIR) $(IDIR_LIBUNWIND)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libunwind*.so* \
		$(IDIR_LIBUNWIND)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
