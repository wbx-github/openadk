# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		xwayland
PKG_VERSION:=		24.1.6
PKG_RELEASE:=		1
PKG_HASH:=		737e612ca36bbdf415a911644eb7592cf9389846847b47fa46dc705bd754d2d7
PKG_DESCR:=		wayland server
PKG_SECTION:=		x11/drivers
PKG_DEPENDS:=		wayland wayland-protocols libepoxy libtirpc
PKG_DEPENDS+=		pixman libxkbfile libxfont2 font-util libopenssl
PKG_DEPENDS+=		libxdmcp libxshmfence libx11 libxcb libxext
PKG_DEPENDS+=		libxau libfreetype libfontenc
PKG_BUILDDEP:=		wayland wayland-protocols libepoxy libtirpc
PKG_BUILDDEP+=		pixman xorgproto libxkbfile libXfont2 font-util
PKG_BUILDDEP+=		openssl libXdmcp libxshmfence libX11 libxcb
PKG_BUILDDEP+=		libXext libXau freetype libfontenc
PKG_URL:=		https://xorg.freedesktop.org/
PKG_SITES:=		https://www.x.org/releases/individual/xserver/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,XWAYLAND,xwayland,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson


xwayland-install:
	$(INSTALL_DIR) $(IDIR_XWAYLAND)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/Xwayland \
		$(IDIR_XWAYLAND)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
