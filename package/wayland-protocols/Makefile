# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		wayland-protocols
PKG_VERSION:=		1.31
PKG_RELEASE:=		1
PKG_HASH:=		a07fa722ed87676ec020d867714bc9a2f24c464da73912f39706eeef5219e238
PKG_DESCR:=		wayland protocols
PKG_SECTION:=		x11/libs
PKG_BUILDDEP:=		meson-host wayland-host
PKG_SITES:=		https://gitlab.freedesktop.org/wayland/wayland-protocols/-/releases/$(PKG_VERSION)/downloads/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,WAYLAND_PROTOCOLS,wayland-protocols,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

MESON_FLAGS+=		-Dtests=false

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

wayland-protocols-install:
	$(INSTALL_DIR) $(IDIR_WAYLAND_PROTOCOLS)/usr/share/wayland-protocols
	$(CP) $(WRKINST)/usr/share/wayland-protocols/* \
		$(IDIR_WAYLAND_PROTOCOLS)/usr/share/wayland-protocols/

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
