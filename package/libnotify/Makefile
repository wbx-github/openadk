# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libnotify
PKG_VERSION:=		0.8.6
PKG_RELEASE:=		1
PKG_HASH:=		c5540aaefb60e1d63b1c587c05f2284ebe72ece7d0c0e5e4a778cfd5844b6b58
PKG_DESCR:=		notify library
PKG_SECTION:=		libs/misc
PKG_BUILDDEP:=		libgtk3 dbus-glib
PKG_NEEDS:=		c++
PKG_SITES:=		https://download.gnome.org/sources/libnotify/0.8/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBNOTIFY,libnotify,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

MESON_FLAGS+=		-Dtests=false \
			-Dman=false \
			-Dgtk_doc=false \
			-Ddocbook_docs=disabled \
			-Dintrospection=disabled

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

libnotify-install:
	$(INSTALL_DIR) $(IDIR_LIBNOTIFY)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libnotify*.so* \
		$(IDIR_LIBNOTIFY)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
