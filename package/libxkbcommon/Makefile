# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libxkbcommon
PKG_VERSION:=		1.5.0
PKG_RELEASE:=		1
PKG_HASH:=		560f11c4bbbca10f495f3ef7d3a6aa4ca62b4f8fb0b52e7d459d18a26e46e017
PKG_DESCR:=		library for handling of keyboard descriptions
PKG_SECTION:=		libs/misc
PKG_BUILDDEP:=		meson-host
PKG_SITES:=		https://xkbcommon.org/download/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBXKBCOMMON,libxkbcommon,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

MESON_FLAGS+=		-Denable-docs=false \
			-Denable-wayland=false \
			-Dxkb-config-root=/usr/share/X11/xkb

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

libxkbcommon-install:
	$(INSTALL_DIR) $(IDIR_LIBXKBCOMMON)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libxkbcommon*.so* \
		$(IDIR_LIBXKBCOMMON)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
