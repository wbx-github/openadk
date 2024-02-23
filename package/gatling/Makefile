# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		gatling
PKG_VERSION:=		0.16
PKG_RELEASE:=		1
PKG_HASH:=		5f96438ee201d7f1f6c2e0849ff273b196bdc7493f29a719ce8ed08c8be6365b
PKG_DESCR:=		small non-forking webserver
PKG_SECTION:=		net/http
PKG_BUILDDEP:=		libowfat
PKG_NEEDS:=		iconv
PKG_URL:=		https://www.fefe.de/gatling/
PKG_SITES:=		https://www.fefe.de/gatling/

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,GATLING,gatling,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
INSTALL_STYLE:=		manual

MAKE_FILE:=		GNUmakefile
ALL_TARGET:=		gatling
XAKE_FLAGS+=		CC='${TARGET_CC}' \
			CFLAGS='${TARGET_CPPFLAGS} ${TARGET_CFLAGS}' \
			ZLIB=0 DIET= prefix='${WRKINST}/usr'

do-install:
	${INSTALL_DIR} ${IDIR_GATLING}/usr/sbin
	${INSTALL_BIN} ${WRKBUILD}/gatling ${IDIR_GATLING}/usr/sbin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
