# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libwpe
PKG_VERSION:=		1.16.2
PKG_RELEASE:=		1
PKG_HASH:=		960bdd11c3f2cf5bd91569603ed6d2aa42fd4000ed7cac930a804eac367888d7
PKG_DESCR:=		general purpose library for wpe
PKG_SECTION:=		libs/misc
PKG_URL:=		https://wpewebkit.org
PKG_SITES:=		https://wpewebkit.org/releases/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBWPE,libwpe,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIG_STYLE:=		cmake
CMAKE_FLAGS+=		-DCMAKE_POLICY_VERSION_MINIMUM=3.5

libwpe-install:
	$(INSTALL_DIR) $(IDIR_LIBWPE)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libwpe*.so* \
		$(IDIR_LIBWPE)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
