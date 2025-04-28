# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libxkbcommon
PKG_VERSION:=		1.7.0
PKG_RELEASE:=		1
PKG_HASH:=		65782f0a10a4b455af9c6baab7040e2f537520caa2ec2092805cdfd36863b247
PKG_DESCR:=		library for handling of keyboard descriptions
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		wayland
PKG_BUILDDEP:=		meson-host wayland wayland-protocols
PKG_SITES:=		https://xkbcommon.org/download/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBXKBCOMMON,libxkbcommon,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

MESON_FLAGS+=		-Denable-docs=false \
			-Denable-wayland=true \
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
