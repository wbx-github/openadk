# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		p910nd
PKG_VERSION:=		0.97
PKG_RELEASE:=		1
PKG_HASH:=		a1bcc2dd75bad4e00a9de5098dbd970e8380f978fc09292bcfa15852af6a6964
PKG_DESCR:=		small non-spooling printer server
PKG_SECTION:=		net/misc
PKG_URL:=		https://github.com/kenyapcomau/p910nd
PKG_SITES:=		https://github.com/kenyapcomau/p910nd/archive/refs/tags/

DISTFILES:=		${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,P910ND,p910nd,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
INSTALL_STYLE:=		manual

MAKE_FLAGS+=		${TARGET_ENV} \
			CFLAGS="${TARGET_CFLAGS} -DLOCKFILE_DIR=\"\\\"/tmp\\\"\""
ALL_TARGET:=

do-install:
	${INSTALL_DIR} ${IDIR_P910ND}/usr/sbin
	${INSTALL_BIN} ${WRKBUILD}/p910nd ${IDIR_P910ND}/usr/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
