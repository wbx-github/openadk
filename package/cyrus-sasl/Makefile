# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		cyrus-sasl
PKG_VERSION:=		b2e733c5f7351fadecadb797882e71d2529f4053
PKG_GIT:=		hash
PKG_RELEASE:=		1
PKG_HASH:=		3e38933a30b9ce183a5488b4f6a5937a702549cde0d3287903d80968ad4ec341
PKG_DESCR:=		general purpose authentication library
PKG_SECTION:=		libs/crypto
PKG_DEPENDS:=		libopenssl
PKG_BUILDDEP:=		openssl
PKG_URL:=		http://cyrusimap.org/
PKG_SITES:=		https://github.com/cyrusimap/cyrus-sasl.git
PKG_LIBNAME:=		libsasl2
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LIBSASL2,libsasl2,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

AUTOTOOL_STYLE:=	autogen
CONFIGURE_ARGS+=	--enable-plain \
			--disable-anon \
			--disable-scram \
			--with-ipctype=unix \
			--with-devrandom="/dev/urandom" \
			--with-openssl="${STAGING_TARGET_DIR}/usr" \
			--disable-sample \
			--disable-alwaystrue \
			--disable-checkapop \
			--disable-otp \
			--disable-srp \
			--disable-srp-setpass \
			--disable-gssapi \
			--disable-gss_mutexes \
			--disable-sql \
			--disable-static \
			--without-dblib \
			--without-gdbm \
			--without-pam \
			--without-saslauthd \
			--without-authdaemond \
			--without-pwcheck \
			--without-opie \
			--without-ldap \
			--without-mysql \
			--without-pgsql \
			--without-sqlite \
			--without-dmalloc \
			--without-sfio


libsasl2-install:
	${INSTALL_DIR} ${IDIR_LIBSASL2}/usr/lib/sasl2
	${CP} ${WRKINST}/usr/lib/libsasl2.so* ${IDIR_LIBSASL2}/usr/lib
	${CP} ${WRKINST}/usr/lib/sasl2/lib*.so* \
		${IDIR_LIBSASL2}/usr/lib/sasl2

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
