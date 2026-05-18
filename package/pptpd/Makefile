# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		pptpd
PKG_VERSION:=		1.5.0
PKG_RELEASE:=		1
PKG_HASH:=		6a724284b1ce00ea23f7d7608d081843a10c8a8d87d951cb2ea86e70aa1b4e77
PKG_DESCR:=		point-to-point tunneling protocol server
PKG_SECTION:=		net/ppp
PKG_DEPENDS:=		ppp
PKG_KDEPENDS:=		ppp ppp-mppe net-ipgre
PKG_SITES:=		https://sourceforge.net/projects/poptop/files/pptpd/$(PKG_NAME)-$(PKG_VERSION)/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_LIBC_DEPENDS:=	uclibc-ng glibc

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,PPTPD,pptpd,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_CFLAGS+=		-fPIC -DSBINDIR='\\\"/usr/sbin\\\"'
FAKE_FLAGS+=		INSTALL="install"

pptpd-install:
	${INSTALL_DIR} ${IDIR_PPTPD}/etc/ppp
	${INSTALL_DIR} ${IDIR_PPTPD}/usr/sbin
	${INSTALL_DATA} ./files/pptpd.conf ${IDIR_PPTPD}/etc/
	${INSTALL_DATA} ./files/options.pptpd ${IDIR_PPTPD}/etc/ppp/
	${INSTALL_BIN} ${WRKINST}/usr/sbin/pptpd \
		${WRKINST}/usr/sbin/pptpctrl ${IDIR_PPTPD}/usr/sbin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
