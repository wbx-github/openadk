# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libsecret
PKG_VERSION:=		0.21.7
PKG_RELEASE:=		1
PKG_HASH:=		944d8a6072b6f285db40b8e9927dbe4dde81dcc7d177f84271fb167ccc297f65
PKG_DESCR:=		library for storing and retrieving passwords
PKG_SECTION:=		libs/crypto
PKG_DEPENDS:=		libgcrypt glib
PKG_BUILDDEP:=		intltool-host libgcrypt glib
PKG_NEEDS:=		intl
PKG_SITES:=		https://gitlab.gnome.org/GNOME/libsecret/-/archive/$(PKG_VERSION)/
PKG_OPTS:=		dev

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBSECRET,libsecret,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

MESON_FLAGS+=		-Dintrospection=false \
			-Dmanpage=false \
			-Dgtk_doc=false

libsecret-install:
	$(INSTALL_DIR) $(IDIR_LIBSECRET)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libsecret*.so* \
		$(IDIR_LIBSECRET)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
