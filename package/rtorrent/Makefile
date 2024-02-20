# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		rtorrent
PKG_VERSION:=		0.9.6
PKG_RELEASE:=		1
PKG_HASH:=		1e69c24f1f26f8f07d58d673480dc392bfc4317818c1115265b08a7813ff5b0e
PKG_DESCR:=		console torrent application
PKG_SECTION:=		app/p2p
PKG_DEPENDS:=		libncurses libtorrent libcurl
PKG_BUILDDEP:=		ncurses libtorrent curl
PKG_NEEDS:=		c++
PKG_URL:=		https://rakshasa.github.io/rtorrent/
PKG_SITES:=		http://rtorrent.net/downloads/

PKG_CFLINE_RTORRENT:=	depends on ADK_BROKEN

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

AUTOTOOL_STYLE:=	autoreconf
TARGET_LDFLAGS+=	-lpthread -ltinfo

$(eval $(call PKG_template,RTORRENT,rtorrent,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

rtorrent-install:
	${INSTALL_DIR} ${IDIR_RTORRENT}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/rtorrent ${IDIR_RTORRENT}/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
