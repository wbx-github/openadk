# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libdisplay-info
PKG_VERSION:=		0.2.0
PKG_RELEASE:=		1
PKG_HASH:=		f7331fcaf5527251b84c8fb84238d06cd2f458422ce950c80e86c72927aa8c2b
PKG_DESCR:=		edid and displayid library
PKG_SECTION:=		libs/misc
PKG_BUILDDEP:=		hwdata meson-host
PKG_SITES:=		https://gitlab.freedesktop.org/emersion/libdisplay-info/-/archive/$(PKG_VERSION)/
PKG_OPTS:=		dev

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBDISPLAY_INFO,libdisplay-info,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

libdisplay-info-install:
	$(INSTALL_DIR) $(IDIR_LIBDISPLAY_INFO)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libdisplay-info*.so* \
		$(IDIR_LIBDISPLAY_INFO)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
