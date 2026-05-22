# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		rtorrent
PKG_VERSION:=		0.16.11
PKG_RELEASE:=		1
PKG_HASH:=		bed2fefd69a01dbe95a02b330dd8c257d1aae2b4ee2ba4a9c4859da2fa404f65
PKG_DESCR:=		console torrent application
PKG_SECTION:=		app/p2p
PKG_DEPENDS:=		libncurses libtorrent libcurl
PKG_BUILDDEP:=		ncurses libtorrent curl
PKG_NEEDS:=		c++
PKG_URL:=		https://rtorrent.net/
PKG_SITES:=		https://github.com/rakshasa/rtorrent-archive/raw/master/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,RTORRENT,rtorrent,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

rtorrent-install:
	${INSTALL_DIR} ${IDIR_RTORRENT}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/rtorrent ${IDIR_RTORRENT}/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
