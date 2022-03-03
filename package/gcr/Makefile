# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		gcr
PKG_VERSION:=		3.40.0
PKG_EXTRAVER:=		3.40
PKG_RELEASE:=		1
PKG_HASH:=		b9d3645a5fd953a54285cc64d4fc046736463dbd4dcc25caf5c7b59bed3027f5
PKG_DESCR:=		gnome keyring library
PKG_SECTION:=		libs/crypto
PKG_BUILDDEP:=		p11-kit intltool-host libgtk3 meson-host
PKG_URL:=		https://wiki.gnome.org/action/show/Projects/GnomeKeyring
PKG_SITES:=		http://ftp.acc.umu.se/pub/gnome/sources/gcr/$(PKG_EXTRAVER)/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,GCR,gcr,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

MESON_FLAGS+=		-Dintrospection=false \
			-Dgtk_doc=false

gcr-install:
	$(INSTALL_DIR) $(IDIR_GCR)/usr/lib
	$(CP) $(WRKINST)/usr/lib/lib*.so* \
		$(IDIR_GCR)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
