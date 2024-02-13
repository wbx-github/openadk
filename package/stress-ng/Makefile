# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		stress-ng
PKG_VERSION:=		0.07.29
PKG_RELEASE:=		1
PKG_HASH:=		71a9555d1d9ee0a4a9bca9ee14294289ee77e998a951c7071df6cc8e153d8410
PKG_DESCR:=		stress-ng will stress test a computer system in various selectable ways
PKG_SECTION:=		sys/utils
PKG_SITES:=		http://kernel.ubuntu.com/~cking/tarballs/stress-ng/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_CFLINE_STRESS_NG:=	depends on ADK_BROKEN

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,STRESS_NG,stress-ng,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual

stress-ng-install:
	${INSTALL_DIR} ${IDIR_STRESS_NG}/usr/bin/
	${INSTALL_BIN} ${WRKINST}/usr/bin/stress-ng ${IDIR_STRESS_NG}/usr/bin/

do-build:
	PATH='$(HOST_PATH)' $(MAKE) ${BB_MAKE_FLAGS} -C ${WRKBUILD} stress-ng

include ${ADK_TOPDIR}/mk/pkg-bottom.mk

