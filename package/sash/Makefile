# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		sash
PKG_VERSION:=		1.0
PKG_RELEASE:=		4
PKG_DESCR:=		standalone shell
PKG_SECTION:=		base/shells

PKG_NOPARALLEL:=	1
NO_DISTFILES:=		1

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,SASH,sash,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

#TARGET_CFLAGS:=		-Wno-incompatible-pointer-types
CONFIG_STYLE:=		manual
INSTALL_STYLE:=		manual

do-install:
	${INSTALL_DIR} ${IDIR_SASH}/bin
	${INSTALL_BIN} ${WRKBUILD}/sh ${IDIR_SASH}/bin/sash

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
