# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		pcre
PKG_VERSION:=		8.45
PKG_RELEASE:=		1
PKG_HASH:=		4e6ce03e0336e8b4a3d6c2b70b1c5e18590a5673a98186da90d4f33c23defc09
PKG_DESCR:=		perl compatible regular expression library
PKG_SECTION:=		libs/misc
PKG_URL:=		http://www.pcre.org/
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=pcre/}
PKG_LIBNAME:=		libpcre
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_SUBPKGS:=		LIBPCRE LIBPCRECPP
PKGSD_LIBPCRECPP:=	pcre c++ library

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,PCRE,pcre,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,LIBPCRE,libpcre,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))
$(eval $(call PKG_template,LIBPCRECPP,libpcrecpp,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_LIBPCRECPP},${PKG_SECTION}))

CONFIGURE_ARGS+=	--enable-utf \
			--enable-unicode-properties
XAKE_FLAGS+=		${TARGET_CONFIGURE_OPTS}

ifeq ($(ADK_PACKAGE_LIBPCRECPP),y)
CONFIGURE_ARGS+=	--enable-cpp
else
CONFIGURE_ARGS+=	--disable-cpp
endif

libpcre-install:
	${INSTALL_DIR} ${IDIR_LIBPCRE}/usr/lib
	${CP} ${WRKINST}/usr/lib/libpcre{,posix}.so* ${IDIR_LIBPCRE}/usr/lib

libpcrecpp-install:
	${INSTALL_DIR} ${IDIR_LIBPCRECPP}/usr/lib
	${CP} ${WRKINST}/usr/lib/libpcrecpp.so* ${IDIR_LIBPCRECPP}/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
