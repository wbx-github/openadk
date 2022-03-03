# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libepoxy
PKG_VERSION:=		1.5.9
PKG_RELEASE:=		1
PKG_HASH:=		d168a19a6edfdd9977fef1308ccf516079856a4275cf876de688fb7927e365e4
PKG_DESCR:=		opengl function pointer management
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		mesa
PKG_BUILDDEP:=		util-macros-host mesa meson-host
PKG_SITES:=		https://github.com/anholt/libepoxy/releases/download/$(PKG_VERSION)/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBEPOXY,libepoxy,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson


libepoxy-install:
	$(INSTALL_DIR) $(IDIR_LIBEPOXY)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libepoxy*.so* \
		$(IDIR_LIBEPOXY)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
