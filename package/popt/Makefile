# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		popt
PKG_VERSION:=		1.19
PKG_RELEASE:=		1
PKG_HASH:=		6eb40d650526cb9fe63eb4415bcecdf9cf306f7556e77eff689abc5a44670060
PKG_DESCR:=		command line option parsing library
PKG_SECTION:=		libs/misc
PKG_URL:=		http://rpm5.org/
PKG_BUILDDEP:=		gettext-host
HOST_BUILDDEP:=		gettext-host libtool-host
PKG_SITES:=		https://github.com/rpm-software-management/popt/archive/refs/tags/
PKG_LIBNAME:=		libpopt
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}-release.tar.gz
WRKDIST=		${WRKDIR}/${PKG_NAME}-${PKG_NAME}-${PKG_VERSION}-release

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,POPT,popt,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,LIBPOPT,libpopt,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

AUTOTOOL_STYLE:=	autogen

libpopt-install:
	${INSTALL_DIR} ${IDIR_LIBPOPT}/usr/lib
	${CP} ${WRKINST}/usr/lib/libpopt.so* ${IDIR_LIBPOPT}/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
