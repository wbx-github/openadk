# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libwnck
PKG_VERSION:=		43.0
PKG_RELEASE:=		1
PKG_HASH:=		905bcdb85847d6b8f8861e56b30cd6dc61eae67ecef4cd994a9f925a26a2c1fe
PKG_DESCR:=		window navigator construction kit
PKG_SECTION:=		libs/misc
PKG_SITES:=		https://download.gnome.org/sources/libwnck/43/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBWNCK,libwnck,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

MESON_FLAGS+=		-Dintrospection=disabled

libwnck-install:
	$(INSTALL_DIR) $(IDIR_LIBWNCK)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libwnck*.so* \
		$(IDIR_LIBWNCK)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
