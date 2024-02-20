# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		libtorrent
PKG_VERSION:=		0.13.8
PKG_RELEASE:=		1
PKG_HASH:=		ed115a28f4ae8cfcd33b94a597c076ca74fd549867a26e4fac9505c27288e983
PKG_DESCR:=		bittorrent library
PKG_SECTION:=		libs/net
PKG_DEPENDS:=		libsigc++ zlib libressl
PKG_BUILDDEP:=		libsigc++ zlib libressl
PKG_NEEDS:=		intl
PKG_URL:=		https://rakshasa.github.io/rtorrent/
PKG_SITES:=		https://github.com/rakshasa/rtorrent/releases/download/v0.9.8/
PKG_OPTS:=		dev

PKG_CFLINE_LIBTORRENT:=	depends on ADK_BROKEN

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LIBTORRENT,libtorrent,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIGURE_ARGS+=	--enable-aligned \
			--without-kqueue \
			--disable-instrumentation \
			--without-zlib

libtorrent-install:
	${INSTALL_DIR} ${IDIR_LIBTORRENT}/usr/lib
	${CP} ${WRKINST}/usr/lib/libtorrent.so* ${IDIR_LIBTORRENT}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
