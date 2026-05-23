# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		igmpproxy
PKG_VERSION:=		0.4
PKG_RELEASE:=		1
PKG_HASH:=		afa4b75a823b82f71ce99f33eae4e8136b906ae8a5ede5caaad93bac38cdae24
PKG_DESCR:=		simple dynamic multicast routing daemon
PKG_SECTION:=		net/route
PKG_KDEPENDS:=		ip-multicast ip-mroute
PKG_SITES:=		https://github.com/pali/igmpproxy/releases/download/$(PKG_VERSION)/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,IGMPPROXY,igmpproxy,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_CFLAGS+=		-std=gnu99

igmpproxy-install:
	${INSTALL_DIR} ${IDIR_IGMPPROXY}/usr/sbin ${IDIR_IGMPPROXY}/etc
	${INSTALL_BIN} ${WRKINST}/usr/sbin/igmpproxy ${IDIR_IGMPPROXY}/usr/sbin
	${INSTALL_DATA} ${WRKINST}/etc/igmpproxy.conf ${IDIR_IGMPPROXY}/etc

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
