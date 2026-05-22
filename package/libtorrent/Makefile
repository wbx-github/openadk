# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		libtorrent
PKG_VERSION:=		0.16.11
PKG_RELEASE:=		1
PKG_HASH:=		620b2892972e8c9d476c995dd52d82cbe86f36733ae3ce5d97e2ca7fc284dea1
PKG_DESCR:=		bittorrent library
PKG_SECTION:=		libs/net
PKG_DEPENDS:=		libsigc++ zlib libopenssl
PKG_BUILDDEP:=		libsigc++ zlib openssl
PKG_NEEDS:=		intl
PKG_URL:=		https://rtorrent.net/
PKG_SITES:=		https://github.com/rakshasa/rtorrent-archive/raw/master/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LIBTORRENT,libtorrent,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIGURE_ARGS+=	--enable-aligned \
			--without-kqueue \
			--disable-instrumentation

libtorrent-install:
	${INSTALL_DIR} ${IDIR_LIBTORRENT}/usr/lib
	${CP} ${WRKINST}/usr/lib/libtorrent.so* ${IDIR_LIBTORRENT}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
