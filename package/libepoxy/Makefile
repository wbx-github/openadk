# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libepoxy
PKG_VERSION:=		1.3.1
PKG_RELEASE:=		1
PKG_HASH:=		1d8668b0a259c709899e1c4bab62d756d9002d546ce4f59c9665e2fc5f001a64
PKG_DESCR:=		opengl function pointer management
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		mesa
PKG_BUILDDEP:=		util-macros-host mesa
PKG_SITES:=		http://crux.nu/files/
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBEPOXY,libepoxy,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

libepoxy-install:
	$(INSTALL_DIR) $(IDIR_LIBEPOXY)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libepoxy*.so* \
		$(IDIR_LIBEPOXY)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
