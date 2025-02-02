# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		cyrus-sasl
PKG_VERSION:=		2.1.28
PKG_RELEASE:=		1
PKG_HASH:=		3e38933a30b9ce183a5488b4f6a5937a702549cde0d3287903d80968ad4ec341
PKG_DESCR:=		general purpose authentication library
PKG_SECTION:=		libs/crypto
PKG_DEPENDS:=		libopenssl
PKG_BUILDDEP:=		openssl
PKG_URL:=		http://cyrusimap.org/
PKG_SITES:=		https://github.com/cyrusimap/cyrus-sasl/archive/refs/tags/
PKG_LIBNAME:=		libsasl2
PKG_OPTS:=		dev

PKG_NOPARALLEL:=	1

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz
WRKDIST=                ${WRKDIR}/$(PKG_NAME)-$(PKG_NAME)-${PKG_VERSION}

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LIBSASL2,libsasl2,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

AUTOTOOL_STYLE:=	autogen
CONFIGURE_ARGS+=	--enable-plain \
			--enable-login \
			--disable-anon \
			--disable-cram \
			--disable-digest \
			--disable-scram \
			--with-ipctype=unix \
			--with-devrandom="/dev/urandom" \
			--with-openssl="${STAGING_TARGET_DIR}/usr" \
			--disable-sample \
			--disable-java \
			--disable-alwaystrue \
			--disable-checkapop \
			--disable-otp \
			--disable-srp \
			--disable-srp-setpass \
			--disable-krb4 \
			--disable-gssapi \
			--disable-gss_mutexes \
			--disable-ntlm \
			--disable-sql \
			--disable-static \
			--without-dblib \
			--without-gdbm \
			--without-pam \
			--without-saslauthd \
			--without-authdaemond \
			--without-pwcheck \
			--without-des \
			--without-opie \
			--without-ldap \
			--without-mysql \
			--without-pgsql \
			--without-sqlite \
			--without-rc4 \
			--without-dmalloc \
			--without-sfio

pre-build:
	${MAKE} -C ${WRKBUILD}/include \
		CC="${CC_FOR_BUILD}" \
		LINK="${CC_FOR_BUILD} -o makemd5 -lc" \
		LIBS="" \
		CFLAGS="${CFLAGS_FOR_BUILD}" \
		LDFLAGS="" \
		CPPFLAGS="" \
		makemd5

libsasl2-install:
	${INSTALL_DIR} ${IDIR_LIBSASL2}/usr/lib/sasl2
	${CP} ${WRKINST}/usr/lib/libsasl2.so* ${IDIR_LIBSASL2}/usr/lib
	${CP} ${WRKINST}/usr/lib/sasl2/lib*.so* \
		${IDIR_LIBSASL2}/usr/lib/sasl2

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
