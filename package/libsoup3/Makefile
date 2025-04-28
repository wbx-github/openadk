# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libsoup3
PKG_VERSION:=		3.6.5
PKG_RELEASE:=		1
PKG_HASH:=		6891765aac3e949017945c3eaebd8cc8216df772456dc9f460976fbdb7ada234
PKG_DESCR:=		http client/server library
PKG_SECTION:=		libs/net
PKG_DEPENDS:=		libsqlite glib libpsl nghttp2
PKG_BUILDDEP:=		sqlite glib libpsl nghttp2
PKG_SITES:=		http://ftp.gnome.org/pub/GNOME/sources/libsoup/3.6/
PKG_OPTS:=		dev

DISTFILES:=		libsoup-$(PKG_VERSION).tar.xz
WRKDIST=		$(WRKDIR)/libsoup-$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBSOUP3,libsoup3,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

MESON_FLAGS:=		-Dtests=false \
			-Dtls_check=false \
			-Dsysprof=disabled
CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

libsoup3-install:
	$(INSTALL_DIR) $(IDIR_LIBSOUP3)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libsoup*.so* \
		$(IDIR_LIBSOUP3)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
