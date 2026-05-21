# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		comgt
PKG_VERSION:=		0.32
PKG_RELEASE:=		3
PKG_HASH:=		0cedb2a5aa608510da66a99aab74df3db363df495032e57e791a2ff55f1d7913
PKG_DESCR:=		3g/gprs datacard control tool
PKG_SECTION:=		sys/hw
PKG_URL:=		http://sourceforge.net/projects/comgt
PKG_SITES:=		https://sourceforge.net/projects/comgt/files/comgt/$(PKG_VERSION)/

DISTFILES:=		${PKG_NAME}.${PKG_VERSION}.tgz
WRKDIST=		${WRKDIR}/${PKG_NAME}.${PKG_VERSION}

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,COMGT,comgt,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
INSTALL_STYLE:=		manual
ALL_TARGET=		comgt

do-install:
	${INSTALL_DIR} ${IDIR_COMGT}/usr/bin ${IDIR_COMGT}/etc/comgt
	${INSTALL_BIN} ${WRKBUILD}/comgt ${IDIR_COMGT}/usr/bin/comgt
	${INSTALL_DATA} ./files/*.comgt ${IDIR_COMGT}/etc/comgt/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
