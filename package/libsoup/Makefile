# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libsoup
PKG_VERSION:=		2.74.3
PKG_RELEASE:=		1
PKG_HASH:=		e4b77c41cfc4c8c5a035fcdc320c7bc6cfb75ef7c5a034153df1413fa1d92f13
PKG_DESCR:=		http client/server library
PKG_SECTION:=		libs/net
PKG_DEPENDS:=		libsqlite glib libpsl
PKG_BUILDDEP:=		sqlite glib libpsl
PKG_SITES:=		http://ftp.gnome.org/pub/GNOME/sources/libsoup/2.74/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBSOUP,libsoup,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

MESON_FLAGS:=		-Dtests=false \
			-Dtls_check=false \
			-Dsysprof=disabled
CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

libsoup-install:
	$(INSTALL_DIR) $(IDIR_LIBSOUP)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libsoup*.so* \
		$(IDIR_LIBSOUP)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
