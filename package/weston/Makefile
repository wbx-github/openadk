# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		weston
PKG_VERSION:=		9.0.0
PKG_RELEASE:=		1
PKG_HASH:=		82b17ab1766f13557fc620c21e3c89165342d3a3ead79ba01181b4f7d2144487
PKG_DESCR:=		wayland compositor
PKG_SECTION:=		x11/drivers
PKG_DEPENDS:=		wayland libxkbcommon libinput libpng libjpeg-turbo
PKG_DEPENDS+=		libwebp pam libxcursor libudev xkeyboard-config cairo
PKG_BUILDDEP:=		wayland libxkbcommon libinput libpng libjpeg-turbo
PKG_BUILDDEP+=		libwebp pam libXcursor eudev cairo
PKG_SITES:=		https://github.com/wayland-project/weston/archive/refs/tags/

PKG_CFLINE_WESTON:=	select ADK_PACKAGE_CAIRO_WITH_PNG@

DISTFILES:=             $(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,WESTON,weston,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

MESON_FLAGS+=		-Dlauncher-logind=false \
			-Dsystemd=false \
			-Dbackend-drm-screencast-vaapi=false \
			-Dbackend-rdp=false \
			-Dcolor-management-lcms=false \
			-Dcolor-management-colord=false \
			-Dremoting=false \
			-Dpipewire=false \
			-Ddemo-clients=false 

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

weston-install:
	$(INSTALL_DIR) $(IDIR_WESTON)/usr/share
	$(CP) $(WRKINST)/usr/share/* \
		$(IDIR_WESTON)/usr/share/
	$(INSTALL_DIR) $(IDIR_WESTON)/usr/libexec
	$(CP) $(WRKINST)/usr/libexec/* \
		$(IDIR_WESTON)/usr/libexec/
	$(INSTALL_DIR) $(IDIR_WESTON)/usr/lib
	$(CP) $(WRKINST)/usr/lib/weston \
		$(IDIR_WESTON)/usr/lib/
	$(CP) $(WRKINST)/usr/lib/libweston-9 \
		$(IDIR_WESTON)/usr/lib/
	$(CP) $(WRKINST)/usr/lib/libweston*so* \
		$(IDIR_WESTON)/usr/lib/
	$(INSTALL_DIR) $(IDIR_WESTON)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/weston \
		$(IDIR_WESTON)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
