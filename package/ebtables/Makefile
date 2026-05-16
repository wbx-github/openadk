# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		ebtables
PKG_VERSION:=		2.0.11
PKG_RELEASE:=		1
PKG_HASH:=		b71f654784a726329f88b412ef7b96b4e5d786ed2bd28193ed7b4c0d677dfd2a
PKG_DESCR:=		ethernet bridging firewall tool
PKG_SECTION:=		net/route
PKG_SITES:=		https://www.netfilter.org/pub/ebtables/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,EBTABLES,ebtables,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

ebtables-install:
	${INSTALL_DIR} ${IDIR_EBTABLES}/etc
	${INSTALL_DIR} ${IDIR_EBTABLES}/usr/sbin ${IDIR_EBTABLES}/usr/lib
	${INSTALL_DATA} ${WRKINST}/etc/ethertypes ${IDIR_EBTABLES}/etc
	${INSTALL_BIN} ${WRKINST}/usr/sbin/ebtables-legacy ${IDIR_EBTABLES}/usr/sbin/ebtables
	${CP} ${WRKINST}/usr/lib/*.so ${IDIR_EBTABLES}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
