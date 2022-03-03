# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		atk
PKG_VERSION:=		2.36.0
PKG_EXTRAVER:=		2.36
PKG_RELEASE:=		1
PKG_HASH:=		fb76247e369402be23f1f5c65d38a9639c1164d934e40f6a9cf3c9e96b652788
PKG_DESCR:=		accessibility toolkit library
PKG_SECTION:=		libs/misc
PKG_BUILDDEP:=		glib meson-host
PKG_URL:=		http://www.gnome.org/
PKG_SITES:=		$(MASTER_SITE_GNOME:=atk/$(PKG_EXTRAVER)/)
PKG_LIBNAME:=		libatk
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBATK,libatk,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

MESON_FLAGS+=		-Dintrospection=false

libatk-install:
	$(INSTALL_DIR) $(IDIR_LIBATK)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libatk-*.so* $(IDIR_LIBATK)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
