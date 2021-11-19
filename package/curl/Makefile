# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		curl
PKG_VERSION:=		7.79.1
PKG_RELEASE:=		1
PKG_HASH:=		0606f74b1182ab732a17c11613cbbaf7084f2e6cca432642d0e3ad7c224c3689
PKG_DESCR:=		client-side url transfer tool
PKG_SECTION:=		net/http
PKG_DEPENDS:=		libcurl
PKG_BUILDDEP:=		zlib
PKG_NEEDS:=		threads
PKG_URL:=		https://curl.se/
PKG_SITES:=		https://curl.se/download/
PKG_LIBNAME:=		libcurl
PKG_OPTS:=		dev

PKG_SUBPKGS:=		CURL LIBCURL
PKGSD_LIBCURL:=		client-side url transfer library
PKGSC_LIBCURL:=		libs/net
PKGSS_LIBCURL:=		zlib

PKG_FLAVOURS_CURL:=	WITH_IPV6
PKGFD_WITH_IPV6:=	enable ipv6 support

PKG_CHOICES_CURL:=	WITH_LIBRESSL WITH_GNUTLS WITH_WOLFSSL WITHOUT_SSL
PKGCD_WITH_LIBRESSL:=	use libressl for crypto
PKGCS_WITH_LIBRESSL:=	libressl ca-certificates
PKGCB_WITH_LIBRESSL:=	libressl
PKGCD_WITH_GNUTLS:=	use gnutls for crypto
PKGCS_WITH_GNUTLS:=	libgnutls ca-certificates
PKGCB_WITH_GNUTLS:=	gnutls
PKGCD_WITH_WOLFSSL:=	use wolfssl for crypto
PKGCS_WITH_WOLFSSL:=	wolfssl ca-certificates
PKGCB_WITH_WOLFSSL:=	wolfssl
PKGCD_WITHOUT_SSL:=	use no ssl

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,CURL,curl,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,CURL,curl,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,LIBCURL,libcurl,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_LIBCURL},${PKGSD_LIBCURL},${PKGSC_LIBCURL},${PKG_OPTS}))

HOST_CONFIGURE_ARGS+=	--without-ssl

ifeq (${ADK_PACKAGE_CURL_WITH_LIBRESSL},y)
CONFIGURE_ARGS+=	--with-openssl="${STAGING_TARGET_DIR}/usr" \
			--without-gnutls \
			--without-axtls
endif
ifeq (${ADK_PACKAGE_CURL_WITH_GNUTLS},y)
CONFIGURE_ARGS+=	--with-gnutls="${STAGING_TARGET_DIR}/usr" \
			--without-openssl \
			--without-axtls
endif
ifeq (${ADK_PACKAGE_CURL_WITH_WOLFSSL},y)
CONFIGURE_ARGS+=	--with-cyassl="${STAGING_TARGET_DIR}/usr" \
			--without-openssl \
			--without-gnutls \
			--without-axtls
endif
ifeq (${ADK_PACKAGE_CURL_WITHOUT_SSL},y)
CONFIGURE_ARGS+=	--without-ssl \
			--without-gnutls \
			--without-axtls
endif

CONFIGURE_ENV+=		curl_typeof_curl_socklen_t=socklen_t
CONFIGURE_ARGS+=	--enable-cookies \
			--enable-crypto-auth \
			--enable-nonblocking \
			--enable-file \
			--enable-ftp \
			--enable-http \
			--enable-proxy \
			--disable-curldebug \
			--disable-ntlm-wb \
			--disable-symbol-hiding \
			--disable-ares \
			--disable-dict \
			--disable-gopher \
			--disable-ldap \
			--disable-smtp \
			--disable-imap \
			--disable-ldaps \
			--disable-manual \
			--disable-sspi \
			--disable-telnet \
			--disable-verbose \
			--without-libssh2 \
			--without-librtmp \
			--without-libidn \
			--with-ca-path="/etc/ssl/certs" \
			--with-random="/dev/urandom" \
			--without-ca-bundle

ifneq (${ADK_PACKAGE_CURL_WITH_IPV6},)
CONFIGURE_ARGS+=	--enable-ipv6
else
CONFIGURE_ARGS+=	--disable-ipv6
endif

curl-install:
	${INSTALL_DIR} ${IDIR_CURL}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/curl ${IDIR_CURL}/usr/bin

libcurl-install:
	${INSTALL_DIR} ${IDIR_LIBCURL}/usr/lib
	${CP} ${WRKINST}/usr/lib/libcurl.so* ${IDIR_LIBCURL}/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
