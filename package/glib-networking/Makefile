# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		glib-networking
PKG_VERSION:=		2.80.1
PKG_RELEASE:=		1
PKG_HASH:=		35ca3d6ca638493765a7dc11c5f46b816dbc407ec939c1f69682960b6cfb76c9
PKG_DESCR:=		low-level core library for networking
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		glib
PKG_BUILDDEP:=		glib
PKG_SITES:=		https://gitlab.gnome.org/GNOME/glib-networking/-/archive/2.80.1/

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,GLIB_NETWORKING,glib-networking,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

MESON_FLAGS+=		-Dlibproxy=disabled \
			-Dgnome_proxy=disabled \
			-Dgnutls=disabled \
			-Dopenssl=enabled

glib-networking-install:
	$(INSTALL_DIR) $(IDIR_GLIB_NETWORKING)/usr/lib/gio/modules
	$(CP) $(WRKINST)/usr/lib/gio/modules/*.so \
		$(IDIR_GLIB_NETWORKING)/usr/lib/gio/modules

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
