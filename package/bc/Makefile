# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		bc
PKG_VERSION:=		1.08.2
PKG_RELEASE:=		1
PKG_HASH:=		ae470fec429775653e042015edc928d07c8c3b2fc59765172a330d3d87785f86
PKG_DESCR:=		arbitrary precision calculator language
PKG_SECTION:=		sys/utils
PKG_BUILDDEP:=		m4-host flex-host
HOST_BUILDDEP:=		m4-host flex-host
PKG_URL:=		http://www.gnu.org/software/bc/
PKG_SITES:=		http://ftp.gnu.org/pub/gnu/bc/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_SUBPKGS:=		BC DC

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,BC,bc,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,BC,bc,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,DC,dc,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

bc-install:
	${INSTALL_DIR} ${IDIR_BC}/usr/bin
	${INSTALL_BIN} ${WRKBUILD}/bc/bc ${IDIR_BC}/usr/bin/bc

dc-install:
	${INSTALL_DIR} ${IDIR_DC}/usr/bin
	${INSTALL_BIN} ${WRKBUILD}/dc/dc ${IDIR_DC}/usr/bin/dc

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
