# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		tor
PKG_VERSION:=		0.4.8.10
PKG_RELEASE:=		1
PKG_HASH:=		e628b4fab70edb4727715b23cf2931375a9f7685ac08f2c59ea498a178463a86
PKG_DESCR:=		anonymous internet communication system
PKG_SECTION:=		net/proxy
PKG_DEPENDS:=		libevent zlib libressl
PKG_BUILDDEP:=		libevent zlib libressl
PKG_NEEDS:=		threads
PKG_URL:=		https://www.torproject.org/
PKG_SITES:=		https://www.torproject.org/dist/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,TOR,tor,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

# -DNDEBUG not supported
TARGET_CPPFLAGS:=
CONFIGURE_ENV+=		ac_cv_libevent_normal=yes \
			ac_cv_libevent_linker_option="" \
			ac_cv_libevent_dir="${STAGING_TARGET_DIR}/usr" \
			ac_cv_openssldir="${STAGING_TARGET_DIR}/usr" \
			ac_cv_openssl_linker_option="" \
			tor_cv_time_t_signed=yes \
			tor_cv_null_is_zero=yes \
			tor_cv_unaligned_ok=yes

CONFIGURE_ARGS+=	--disable-tool-name-check

ifeq ($(ADK_TARGET_USE_SSP),y)
CONFIGURE_ARGS+=	--enable-gcc-hardening
else
CONFIGURE_ARGS+=	--disable-gcc-hardening
endif

tor-install:
	${INSTALL_DIR} ${IDIR_TOR}/usr/bin ${IDIR_TOR}/etc/tor
	${INSTALL_DATA} ./files/torrc ${IDIR_TOR}/etc/tor/
	${CP} ${WRKINST}/usr/bin/tor ${IDIR_TOR}/usr/bin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
