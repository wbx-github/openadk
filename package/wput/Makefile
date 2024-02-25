# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		wput
PKG_VERSION:=		0.6.1
PKG_RELEASE:=		1
PKG_HASH:=		67125acab1d520e5d2a0429cd9cf7fc379987f30d5bbed0b0e97b92b554fcc13
PKG_DESCR:=		wget-like command-line ftp client
PKG_SECTION:=		net/http
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=wput/}

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tgz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,WPUT,wput,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_CFLAGS+=		-fcommon
CONFIGURE_ARGS+=	--disable-g-switch \
			--without-ssl

wput-install:
	${INSTALL_DIR} ${IDIR_WPUT}/usr/bin
	${INSTALL_BIN} ${WRKBUILD}/wput ${IDIR_WPUT}/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
