# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		vte
PKG_VERSION:=		0.82.3
PKG_RELEASE:=		1
PKG_HASH:=		2674668a34b52bce3e3a500d14c9197d5c772ddd2ea9309efbaa5316ee902da1
PKG_DESCR:=		virtual terminal widget for gtk applications
PKG_DEPENDS:=		lz4
PKG_BUILDDEP:=		lz4
PKG_SECTION:=		libs/misc
PKG_SITES:=		https://gitlab.gnome.org/GNOME/vte/-/archive/0.82.3/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,VTE,vte,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

MESON_FLAGS:=		-Dgnutls=false \
			-Dgtk4=false \
			-D_systemd=false \
			-Dgir=false \
			-Dvapi=false \
			-Dicu=false

vte-install:
	$(INSTALL_DIR) $(IDIR_VTE)/usr/lib
	$(INSTALL_BIN) $(WRKINST)/usr/lib/libvte*.so* \
		$(IDIR_VTE)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
