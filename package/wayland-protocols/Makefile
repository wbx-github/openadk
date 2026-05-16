# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		wayland-protocols
PKG_VERSION:=		1.48
PKG_RELEASE:=		1
PKG_HASH:=		c563af8e2e784f9599fe23819a3fc5e7d946e76db9f90a2e3ba6c9a869a52911
PKG_DESCR:=		wayland protocols
PKG_SECTION:=		x11/libs
PKG_BUILDDEP:=		meson-host wayland-host
PKG_SITES:=		https://gitlab.freedesktop.org/wayland/wayland-protocols/-/archive/$(PKG_VERSION)/
PKG_OPTS:=		dev

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

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
