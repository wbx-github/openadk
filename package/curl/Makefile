# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		curl
PKG_VERSION:=		8.9.0
PKG_RELEASE:=		1
PKG_HASH:=		ff09b2791ca56d25fd5c3f3a4927dce7c8a9dc4182200c487ca889fba1fdd412
PKG_DESCR:=		client-side url transfer tool
PKG_SECTION:=		net/http
PKG_BUILDDEP:=		zlib
PKG_NEEDS:=		threads
PKG_URL:=		https://curl.se/
PKG_SITES:=		https://curl.se/download/
PKG_LIBNAME:=		libcurl
PKG_OPTS:=		dev

PKG_SUBPKGS:=		LIBCURL CURL
PKGSD_LIBCURL:=		client-side url transfer library
PKGSC_LIBCURL:=		libs/net
PKGSS_LIBCURL:=		zlib
PKGSD_CURL:=		client-side url transfer utiity
PKGSC_CURL:=		net/http
PKGSS_CURL:=		zlib libcurl

PKG_FLAVOURS_LIBCURL:=	WITH_IPV6
PKGFD_WITH_IPV6:=	enable ipv6 support

PKG_CHOICES_LIBCURL:=	WITH_LIBRESSL WITH_OPENSSL WITH_GNUTLS WITH_WOLFSSL WITHOUT_SSL
PKGCD_WITH_LIBRESSL:=	use libressl for crypto
PKGCS_WITH_LIBRESSL:=	libressl ca-certificates
PKGCB_WITH_LIBRESSL:=	libressl
PKGCD_WITH_OPENSSL:=	use libopenssl for crypto
PKGCS_WITH_OPENSSL:=	libopenssl ca-certificates
PKGCB_WITH_OPENSSL:=	openssl
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
$(eval $(call PKG_template,LIBCURL,libcurl,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_LIBCURL},${PKGSD_LIBCURL},${PKGSC_LIBCURL},${PKG_OPTS}))
$(eval $(call PKG_template,CURL,curl,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

HOST_CONFIGURE_ARGS+=	--without-ssl \
			--without-libpsl

ifeq (${ADK_PACKAGE_LIBCURL_WITH_LIBRESSL},y)
CONFIGURE_ARGS+=	--with-openssl="${STAGING_TARGET_DIR}/usr" \
			--without-gnutls \
			--without-wolfssl
endif
ifeq (${ADK_PACKAGE_LIBCURL_WITH_OPENSSL},y)
CONFIGURE_ARGS+=	--with-openssl="${STAGING_TARGET_DIR}/usr" \
			--without-gnutls \
			--without-wolfssl
endif
ifeq (${ADK_PACKAGE_LIBCURL_WITH_GNUTLS},y)
CONFIGURE_ARGS+=	--with-gnutls="${STAGING_TARGET_DIR}/usr" \
			--without-openssl \
			--without-wolfssl
endif
ifeq (${ADK_PACKAGE_LIBCURL_WITH_WOLFSSL},y)
CONFIGURE_ARGS+=	--with-wolfssl="${STAGING_TARGET_DIR}/usr" \
			--without-openssl \
			--without-gnutls
endif
ifeq (${ADK_PACKAGE_LIBCURL_WITHOUT_SSL},y)
CONFIGURE_ARGS+=	--without-ssl \
			--without-gnutls \
			--without-wolfssl
endif

CONFIGURE_ENV+=		curl_typeof_curl_socklen_t=socklen_t \
			LDFLAGS='$(TARGET_LDFLAGS) -latomic'
CONFIGURE_ARGS+=	--enable-cookies \
			--enable-file \
			--enable-ftp \
			--enable-http \
			--enable-proxy \
			--disable-curldebug \
			--disable-ntlm \
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
			--without-libpsl \
			--without-librtmp \
			--with-ca-path="/etc/ssl/certs" \
			--with-random="/dev/urandom" \
			--without-ca-bundle

ifneq (${ADK_PACKAGE_LIBCURL_WITH_IPV6},)
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
