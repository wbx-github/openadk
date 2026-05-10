# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		freeradius-client
PKG_VERSION:=		1.1.6
PKG_RELEASE:=		2
PKG_HASH:=		478bfb7ec00789af150acf6a231bc9b0731d06353c7fe36a8fd6d4d83e42a07f
PKG_DESCR:=		radius client
PKG_SECTION:=		net/radius
PKG_DEPENDS:=		libfreeradius-client libopenssl
PKG_BUILDDEP:=		openssl
PKG_URL:=		http://www.freeradius.org/
PKG_SITES:=		ftp://ftp.freeradius.org/pub/radius/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_SUBPKGS:=		FREERADIUS_CLIENT LIBFREERADIUS_CLIENT
PKGSC_LIBFREERADIUS_CLIENT:=	libs/net

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,FREERADIUS_CLIENT,freeradius-client,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,LIBFREERADIUS_CLIENT,libfreeradius-client,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKGSC_LIBFREERADIUS_CLIENT}))

CONFIGURE_ENV+=		ac_cv_func_uname=no

freeradius-client-install:
	${INSTALL_DIR} ${IDIR_FREERADIUS_CLIENT}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/usr/sbin/radiusclient \
		${IDIR_FREERADIUS_CLIENT}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/usr/sbin/rad{login,status} \
		${IDIR_FREERADIUS_CLIENT}/usr/sbin
	${CP} ${WRKINST}/etc ${IDIR_FREERADIUS_CLIENT}/

libfreeradius-client-install:
	${INSTALL_DIR} ${IDIR_LIBFREERADIUS_CLIENT}/usr/lib
	${CP} ${WRKINST}/usr/lib/libfreeradius-client.so* \
		${IDIR_LIBFREERADIUS_CLIENT}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
