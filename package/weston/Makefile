# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		weston
PKG_VERSION:=		15.0.1
PKG_RELEASE:=		1
PKG_HASH:=		dbcedc27f880d1f10a9edc010a9ea044a6a2861269f2aa3c8647cc557a3fd73a
PKG_DESCR:=		wayland compositor
PKG_SECTION:=		x11/drivers
PKG_DEPENDS:=		wayland libxkbcommon libinput libpng libjpeg-turbo libseat mesa libexpat
PKG_DEPENDS+=		libwebp pam libxcursor libudev xkeyboard-config cairo libffi libdrm seatd
PKG_DEPENDS+=		libdisplay-info neatvnc
PKG_BUILDDEP:=		wayland wayland-protocols libxkbcommon libinput libpng libjpeg-turbo expat
PKG_BUILDDEP+=		libwebp pam libXcursor eudev cairo libseat libffi libdrm libdisplay-info mesa
PKG_BUILDDEP+=		neatvnc
PKG_SITES:=		https://gitlab.freedesktop.org/wayland/weston/-/archive/$(PKG_VERSION)/

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,WESTON,weston,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

MESON_FLAGS+=		-Dsystemd=false \
			-Dbackend-rdp=false \
			-Dcolor-management-lcms=false \
			-Dremoting=false \
			-Dpipewire=false \
			-Dbackend-pipewire=false \
			-Dxwayland=false \
			-Dtest-junit-xml=false \
			-Ddemo-clients=false \
			-Dshell-lua=false \
			-Drenderer-gl=true \
			-Drenderer-vulkan=false

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
	$(CP) $(WRKINST)/usr/lib/libweston-15 \
		$(IDIR_WESTON)/usr/lib/
	$(CP) $(WRKINST)/usr/lib/*so* \
		$(IDIR_WESTON)/usr/lib/
	$(INSTALL_DIR) $(IDIR_WESTON)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/* \
		$(IDIR_WESTON)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
