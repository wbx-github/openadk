# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		gcr
PKG_VERSION:=		4.4.0.1
PKG_RELEASE:=		1
PKG_HASH:=		be1fd6ec369ed4eb42e309ef7933a6fb925b08296e0a04a21bb979954d5586e3
PKG_DESCR:=		gnome keyring library
PKG_SECTION:=		libs/crypto
PKG_BUILDDEP:=		p11-kit intltool-host libgtk3 meson-host
PKG_SITES:=		https://gitlab.gnome.org/GNOME/gcr/-/archive/$(PKG_VERSION)/

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,GCR,gcr,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

MESON_FLAGS+=		-Dintrospection=false \
			-Dgtk4=false \
			-Dvapi=false \
			-Dsystemd=disabled \
			-Dgtk_doc=false

gcr-install:
	$(INSTALL_DIR) $(IDIR_GCR)/usr/lib
	$(CP) $(WRKINST)/usr/lib/lib*.so* \
		$(IDIR_GCR)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
