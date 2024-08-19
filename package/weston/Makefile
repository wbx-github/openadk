# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		weston
PKG_VERSION:=		13.0.3
PKG_RELEASE:=		1
PKG_HASH:=		e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
PKG_DESCR:=		wayland compositor
PKG_SECTION:=		x11/drivers
PKG_DEPENDS:=		wayland libxkbcommon libinput libpng libjpeg-turbo libseat
PKG_DEPENDS+=		libwebp pam libxcursor libudev xkeyboard-config cairo libffi libdrm
PKG_BUILDDEP:=		wayland wayland-protocols libxkbcommon libinput libpng libjpeg-turbo
PKG_BUILDDEP+=		libwebp pam libXcursor eudev cairo libseat libffi libdrm libdisplay-info mesa
PKG_SITES:=		https://gitlab.freedesktop.org/wayland/weston/-/releases/$(PKG_VERSION)/downloads/

PKG_CFLINE_WESTON:=	select ADK_PACKAGE_CAIRO_WITH_PNG@

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,WESTON,weston,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

MESON_FLAGS+=		-Dsystemd=false \
			-Dbackend-drm-screencast-vaapi=false \
			-Dbackend-rdp=false \
			-Dcolor-management-lcms=false \
			-Dremoting=false \
			-Dpipewire=false \
			-Dbackend-pipewire=false \
			-Dxwayland=false \
			-Dtest-junit-xml=false \
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
	$(CP) $(WRKINST)/usr/lib/libweston-13 \
		$(IDIR_WESTON)/usr/lib/
	$(CP) $(WRKINST)/usr/lib/libweston*so* \
		$(IDIR_WESTON)/usr/lib/
	$(INSTALL_DIR) $(IDIR_WESTON)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/weston \
		$(IDIR_WESTON)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
