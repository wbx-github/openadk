# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		opensc
PKG_VERSION:=		0.22.0
PKG_RELEASE:=		1
PKG_HASH:=		8d4e5347195ebea332be585df61dcc470331c26969e4b0447c851fb0844c7186
PKG_DESCR:=		utilities to access smart cards
PKG_SECTION:=		app/crypto
PKG_BUILDDEP:=		openct pcsc-lite readline libressl
PKG_DEPENDS:=		libopensc libopenct pcsc-lite libreadline libressl
PKG_URL:=		https://github.com/OpenSC/OpenSC/wiki
PKG_SITES:=		https://github.com/OpenSC/OpenSC/releases/download/$(PKG_VERSION)/
PKG_LIBNAME:=		libopensc
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_SUBPKGS:=		OPENSC LIBOPENSC
PKGSD_LIBOPENSC:=	opensc library
PKGSC_LIBOPENSC:=	libs/crypto
PKGSS_LIBOPENSC:=	libltdl
PKGSB_LIBOPENSC:=	libtool

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,OPENSC,${PKG_NAME},${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,LIBOPENSC,libopensc,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_LIBOPENSC},${PKGSD_LIBOPENSC},${PKGSC_LIBOPENSC},${PKG_OPTS}))

CONFIGURE_ARGS+=	--disable-man \
			--disable-iconv \
			--disable-pcsc \
			--enable-openct

opensc-install:
	${INSTALL_DIR} ${IDIR_OPENSC}/usr/bin
	${INSTALL_DIR} ${IDIR_OPENSC}/usr/share/opensc
	${INSTALL_DATA} ${WRKINST}/usr/share/opensc/* \
		${IDIR_OPENSC}/usr/share/opensc
	${INSTALL_BIN} ${WRKINST}/usr/bin/opensc-explorer \
		 ${IDIR_OPENSC}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/opensc-tool \
		 ${IDIR_OPENSC}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/pkcs15-init \
		 ${IDIR_OPENSC}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/pkcs15-tool \
		 ${IDIR_OPENSC}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/pkcs15-crypt \
		 ${IDIR_OPENSC}/usr/bin

libopensc-install:
	${INSTALL_DIR} ${IDIR_LIBOPENSC}/usr/lib
	${CP} ${WRKINST}/usr/lib/libopensc.so* \
		${IDIR_LIBOPENSC}/usr/lib
	${CP} ${WRKINST}/usr/lib/opensc-pkcs11.so \
		${IDIR_LIBOPENSC}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
