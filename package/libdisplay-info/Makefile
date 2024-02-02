# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libdisplay-info
PKG_VERSION:=		0.1.1
PKG_RELEASE:=		1
PKG_HASH:=		0d8731588e9f82a9cac96324a3d7c82e2ba5b1b5e006143fefe692c74069fb60
PKG_DESCR:=		edid and displayid library
PKG_SECTION:=		libs/misc
PKG_BUILDDEP:=		hwdata
PKG_SITES:=		https://gitlab.freedesktop.org/emersion/libdisplay-info/-/releases/0.1.1/downloads/
PKG_OPTS:=		dev

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
