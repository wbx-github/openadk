# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		ctorrent
PKG_VERSION:=		dnh3.3.2
PKG_RELEASE:=		2
PKG_HASH:=		c87366c91475931f75b924119580abd06a7b3cb3f00fef47346552cab1e24863
PKG_DESCR:=		console-based bittorrent client
PKG_SECTION:=		app/p2p
PKG_DEPENDS:=		libopenssl
PKG_BUILDDEP:=		openssl
PKG_NEEDS:=		c++
PKG_URL:=		http://www.rahul.net/dholmes/ctorrent
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=dtorrent/}

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,CTORRENT,ctorrent,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

ctorrent-install:
	${INSTALL_DIR} ${IDIR_CTORRENT}/usr/bin
	${CP} ${WRKINST}/usr/bin/ctorrent ${IDIR_CTORRENT}/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
