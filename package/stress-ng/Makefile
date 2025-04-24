# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		stress-ng
PKG_VERSION:=		0.18.12
PKG_RELEASE:=		1
PKG_HASH:=		20401a5a52a3b3b5d84fbdd561e4daf1076b0368a1ccbbbc8d41af2be6ea6f34
PKG_DESCR:=		stress test a computer system in various selectable ways
PKG_SECTION:=		sys/utils
PKG_SITES:=		https://github.com/ColinIanKing/stress-ng/archive/refs/tags/

DISTFILES:=		V${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,STRESS_NG,stress-ng,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual

do-build:
	PATH='$(HOST_PATH)' $(MAKE) ${BB_MAKE_FLAGS} -C ${WRKBUILD} stress-ng

stress-ng-install:
	${INSTALL_DIR} ${IDIR_STRESS_NG}/usr/bin/
	${INSTALL_BIN} ${WRKINST}/usr/bin/stress-ng ${IDIR_STRESS_NG}/usr/bin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk

