# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		pptp
PKG_VERSION:=		1.10.0
PKG_RELEASE:=		1
PKG_HASH:=		82492db8e487ce73b182ee7f444251d20c44f5c26d6e96c553ec7093aefb5af4
PKG_DESCR:=		point-to-point tunneling protocol client
PKG_SECTION:=		net/ppp
PKG_DEPENDS:=		ppp
PKG_KDEPENDS:=		ppp net-ipgre
PKG_SITES:=		https://sourceforge.net/projects/pptpclient/files/pptp/pptp-$(PKG_VERSION)/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,PPTP,pptp,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=          manual
INSTALL_STYLE:=         manual

do-install:
	${INSTALL_DIR} ${IDIR_PPTP}/sbin
	${INSTALL_DIR} ${IDIR_PPTP}/usr/sbin
	${INSTALL_DIR} ${IDIR_PPTP}/etc/ppp
	${INSTALL_BIN} ./files/ifup.pptp ${IDIR_PPTP}/sbin/ifup.pptp
	${INSTALL_DATA} ./files/options.pptp ${IDIR_PPTP}/etc/ppp/
	${INSTALL_BIN} ${WRKBUILD}/pptp ${IDIR_PPTP}/usr/sbin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
