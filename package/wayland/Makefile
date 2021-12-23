# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		wayland
PKG_VERSION:=		1.19.0
PKG_RELEASE:=		1
PKG_HASH:=		baccd902300d354581cd5ad3cc49daa4921d55fb416a5883e218750fef166d15
PKG_DESCR:=		wayland
PKG_SECTION:=		x11/libs
PKG_BUILDDEP:=		wayland-host meson-host
HOST_BUILDDEP:=		expat-host libxml2-host
PKG_SITES:=		https://wayland.freedesktop.org/releases/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,WAYLAND,wayland,$(PKG_VERSION)-${PKG_RELEASE}))
$(eval $(call PKG_template,WAYLAND,wayland,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

HOST_CONFIGURE_ARGS+=	--disable-documentation
MESON_FLAGS+=		-Ddocumentation=false \
			-Dscanner=false

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

wayland-install:
	$(INSTALL_DIR) $(IDIR_WAYLAND)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libwayland*.so* \
		$(IDIR_WAYLAND)/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
