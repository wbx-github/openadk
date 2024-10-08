# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libressl
PKG_VERSION:=		3.9.2
PKG_RELEASE:=		1
PKG_HASH:=		7b031dac64a59eb6ee3304f7ffb75dad33ab8c9d279c847f92c89fb846068f97
PKG_DESCR:=		ssl/tls library
PKG_SECTION:=		libs/crypto
PKG_URL:=		http://www.libressl.org
PKG_SITES:=		http://ftp.openbsd.org/pub/OpenBSD/LibreSSL/
PKG_OPTS:=		dev

PKG_ARCH_DEPENDS:=	!m68k !xtensa

DISTFILES:=             ${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_SUBPKGS:=		LIBRESSL LIBRESSL_UTIL
PKGSD_LIBRESSL_UTIL:=	openssl command line tool
PKGSC_LIBRESSL_UTIL:=	app/crypto
PKGSS_LIBRESSL_UTIL:=	libressl

include ${ADK_TOPDIR}/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,LIBRESSL,libressl,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,LIBRESSL,libressl,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))
$(eval $(call PKG_template,LIBRESSL_UTIL,libressl-util,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_LIBRESSL_UTIL},${PKGSD_LIBRESSL_UTIL},${PKGSC_LIBRESSL_UTIL}))

ifeq ($(ADK_TARGET_ARCH_ARM),y)
CONFIGURE_ARGS+=	--disable-asm
endif

ifeq ($(ADK_TARGET_USE_SSP),y)
CONFIGURE_ARGS+=	--enable-hardening
else
CONFIGURE_ARGS+=	--disable-hardening
endif

libressl-install:
	${INSTALL_DIR} ${IDIR_LIBRESSL}/etc/ssl
	${CP} ${WRKINST}/etc/ssl/openssl.cnf ${IDIR_LIBRESSL}/etc/ssl
	$(INSTALL_DIR) $(IDIR_LIBRESSL)/usr/lib
	$(CP) $(WRKINST)/usr/lib/lib{crypto,ssl,tls}.so* \
		$(IDIR_LIBRESSL)/usr/lib

libressl-util-install:
	${INSTALL_DIR} ${IDIR_LIBRESSL_UTIL}/usr/bin
	${CP} ${WRKINST}/usr/bin/openssl ${IDIR_LIBRESSL_UTIL}/usr/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
