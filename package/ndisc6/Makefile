# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		ndisc6
PKG_VERSION:=		1.0.8
PKG_RELEASE:=		1
PKG_HASH:=		1f2fb2dc1172770aa5a09d39738a44d8b753cc5e2e25e306ca78682f9fea0b4f
PKG_DESCR:=		icmpv6 neighbour discovery tools
PKG_SECTION:=		net/ipv6
PKG_URL:=		http://www.remlab.net/
PKG_SITES:=		http://www.remlab.net/files/ndisc6/

PKG_LIBC_DEPENDS:=	uclibc-ng glibc

PKG_SUBPKGS:=		NDISC6 RDISC6 TCPTRACEROUTE6
PKGSD_NDISC6:=		icmpv6 neighbour discovery tool
PKGSD_RDISC6:=		icmpv6 router discovery tool
PKGSD_TCPTRACEROUTE6:=	lightweight ipv6 tcptraceroute

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.bz2

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,NDISC6,ndisc6,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_NDISC6},${PKG_SECTION}))
$(eval $(call PKG_template,RDISC6,rdisc6,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_RDISC6},${PKG_SECTION}))
$(eval $(call PKG_template,TCPTRACEROUTE6,tcptraceroute6,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_TCPTRACEROUTE6},${PKG_SECTION}))

MAKE_FLAGS+=		CC="${TARGET_CC}"

ndisc6-install:
	${INSTALL_DIR} ${IDIR_NDISC6}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/ndisc6 ${IDIR_NDISC6}/usr/bin/

rdisc6-install:
	${INSTALL_DIR} ${IDIR_RDISC6}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/rdisc6 ${IDIR_RDISC6}/usr/bin/

tcptraceroute6-install:
	${INSTALL_DIR} ${IDIR_TCPTRACEROUTE6}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/tcptraceroute6 \
		${IDIR_TCPTRACEROUTE6}/usr/bin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
