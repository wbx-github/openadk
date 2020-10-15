# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		popt
PKG_VERSION:=		1.16
PKG_RELEASE:=		4
PKG_HASH:=		e728ed296fe9f069a0e005003c3d6b2dde3d9cad453422a10d6558616d304cc8
PKG_DESCR:=		command line option parsing library
PKG_SECTION:=		libs/misc
PKG_URL:=		http://rpm5.org/
PKG_SITES:=		https://distfiles.openadk.org/
PKG_LIBNAME:=		libpopt
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,POPT,popt,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,LIBPOPT,libpopt,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

libpopt-install:
	${INSTALL_DIR} ${IDIR_LIBPOPT}/usr/lib
	${CP} ${WRKINST}/usr/lib/libpopt.so* ${IDIR_LIBPOPT}/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
