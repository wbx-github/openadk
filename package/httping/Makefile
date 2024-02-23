# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		httping
PKG_VERSION:=		3.5
PKG_RELEASE:=		1
PKG_HASH:=		8c081daae31cad586bce7742bd721c2a741d7ce0687fb3a12cafd389b90bf79c
PKG_DESCR:=		like ping but for http-requests
PKG_SECTION:=		net/http
PKG_DEPENDS:=		libressl
PKG_BUILDDEP:=		cmake-host libressl
PKG_NEEDS:=		intl
PKG_SITES:=		https://github.com/folkertvanheusden/HTTPing/archive/refs/tags/

DISTFILES:=		v${PKG_VERSION}.tar.gz
WRKDIST=		${WRKDIR}/HTTPing-${PKG_VERSION}

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,HTTPING,httping,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		cmake

httping-install:
	${INSTALL_DIR} ${IDIR_HTTPING}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/httping ${IDIR_HTTPING}/usr/bin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
