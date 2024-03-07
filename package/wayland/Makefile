# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		wayland
PKG_VERSION:=		1.22.0
PKG_RELEASE:=		1
PKG_HASH:=		1540af1ea698a471c2d8e9d288332c7e0fd360c8f1d12936ebb7e7cbc2425842
PKG_DESCR:=		wayland
PKG_SECTION:=		x11/libs
PKG_BUILDDEP:=		wayland-host
HOST_BUILDDEP:=		meson-host expat-host libxml2-host libffi-host
PKG_SITES:=		https://gitlab.freedesktop.org/wayland/wayland/-/releases/$(PKG_VERSION)/downloads/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,WAYLAND,wayland,$(PKG_VERSION)-${PKG_RELEASE}))
$(eval $(call PKG_template,WAYLAND,wayland,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

HOST_MESON_FLAGS+=	-Ddocumentation=false \
			-Dtests=false \
			-Dscanner=true
MESON_FLAGS+=		-Ddocumentation=false \
			-Dtests=false \
			-Dlibraries=true \
			-Dscanner=false

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

HOST_STYLE:=		meson
CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

hostpost-install:
	$(INSTALL_DIR) $(STAGING_HOST_DIR)/usr/bin
	$(INSTALL_BIN) $(WRKBUILD)/src/wayland-scanner \
		$(STAGING_HOST_DIR)/usr/bin
	$(INSTALL_DIR) $(STAGING_HOST_DIR)/usr/lib/pkgconfig
	$(CP) $(WRKBUILD)/meson-private/wayland-scanner.pc \
		$(STAGING_HOST_DIR)/usr/lib/pkgconfig


wayland-install:
	$(INSTALL_DIR) $(IDIR_WAYLAND)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libwayland*.so* \
		$(IDIR_WAYLAND)/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
