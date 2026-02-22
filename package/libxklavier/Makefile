# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libxklavier
PKG_VERSION:=		5.3
PKG_RELEASE:=		1
PKG_HASH:=		ebec3bc54b5652838502b96223152fb1cd8fcb14ace5cb02d718fc3276bbd404
PKG_DESCR:=		library providing high-level api for x keyboard extension
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		iso-codes
PKG_BUILDDEP:=		iso-codes
PKG_URL:=		https://www.freedesktop.org/wiki/Software/LibXklavier
PKG_SITES:=		https://download.gnome.org/sources/libxklavier/5.3/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBXKLAVIER,libxklavier,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

libxklavier-install:
	$(INSTALL_DIR) $(IDIR_LIBXKLAVIER)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libxklavier*.so* \
		$(IDIR_LIBXKLAVIER)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
