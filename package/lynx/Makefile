# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		lynx
PKG_VERSION:=		2.9.1
PKG_RELEASE:=		1
PKG_HASH:=		085fb3924b8684485c6be1b1ca745417da6ace768f94428ead95caf9dd8b56b7
PKG_DESCR:=		text browser
PKG_SECTION:=		app/browser
PKG_DEPENDS:=		libncurses zlib
PKG_BUILDDEP:=		ncurses zlib
PKG_URL:=		https://lynx.invisible-island.net/
PKG_SITES:=		https://invisible-island.net/archives/lynx/tarballs/
PKG_NOPARALLEL:=	1

DISTFILES:=		${PKG_NAME}${PKG_VERSION}.tar.gz
WRKDIST=		${WRKDIR}/$(PKG_NAME)$(PKG_VERSION)

PKG_CHOICES_LYNX:=	WITH_LIBRESSL WITH_OPENSSL WITH_GNUTLS WITHOUT_SSL
PKGCD_WITH_LIBRESSL:=	use libressl for crypto
PKGCS_WITH_LIBRESSL:=	libressl ca-certificates
PKGCB_WITH_LIBRESSL:=	libressl
PKGCD_WITH_OPENSSL:=	use libopenssl for crypto
PKGCS_WITH_OPENSSL:=	libopenssl ca-certificates
PKGCB_WITH_OPENSSL:=	openssl
PKGCD_WITH_GNUTLS:=	use gnutls for crypto
PKGCS_WITH_GNUTLS:=	libgnutls ca-certificates
PKGCB_WITH_GNUTLS:=	gnutls
PKGCD_WITHOUT_SSL:=	use no ssl

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LYNX,lynx,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

#TARGET_CPPFLAGS+=	-I${STAGING_TARGET_DIR}/include/openssl
#TARGET_CPPFLAGS+=	-DUSE_OPENSSL_INCL -DUSE_X509_SUPPORT
#HOST_CFLAGS+=		-DUSE_OPENSSL_INCL -DUSE_X509_SUPPORT

ifeq (${ADK_PACKAGE_LYNX_WITH_LIBRESSL},y)
CONFIGURE_ARGS+=	--with-ssl="${STAGING_TARGET_DIR}/usr" \
			--without-gnutls
endif
ifeq (${ADK_PACKAGE_LYNX_WITH_OPENSSL},y)
CONFIGURE_ARGS+=	--with-ssl="${STAGING_TARGET_DIR}/usr" \
			--without-gnutls
endif
ifeq (${ADK_PACKAGE_LYNX_WITH_GNUTLS},y)
CONFIGURE_ARGS+=	--with-gnutls="${STAGING_TARGET_DIR}/usr" \
			--without-ssl
endif
ifeq (${ADK_PACKAGE_LYNX_WITHOUT_SSL},y)
CONFIGURE_ARGS+=	--without-ssl \
			--without-gnutls
endif

CONFIGURE_ENV+=		ac_cv_path_TELNET=telnet \
			ac_cv_path_TN3270=tn3270 \
			ac_cv_path_RLOGIN=rlogin \
			ac_cv_path_MV=mv \
			ac_cv_path_GZIP=gzip \
			ac_cv_path_UNCOMPRESS=gunzip \
			ac_cv_path_UNZIP=unzip \
			ac_cv_path_BZIP2=bzip2 \
			ac_cv_path_TAR=tar \
			ac_cv_path_COMPRESS=compress \
			ac_cv_path_RM=rm \
			ac_cv_path_UUDECODE=uudecode \
			ac_cv_path_ZCAT=zcat \
			ac_cv_path_ZIP=zip \
			ac_cv_path_NCURSES_CONFIG=${STAGING_TARGET_DIR}/usr/bin/ncurses5-config

CONFIGURE_ARGS+=	--disable-warnings \
			--without-socks \
			--without-socks5 \
			--enable-addrlist-page \
			--enable-charset-choice \
			--enable-color-style \
			--disable-default-colors \
			--disable-htmlized-cfg \
			--enable-nested-tables \
			--disable-scrollbar \
			--enable-justify-elts \
			--enable-internal-links \
			--enable-nsl-fork \
			--enable-underlines \
			--without-bzlib \
			--without-x \
			--with-zlib=${STAGING_TARGET_DIR}/usr \
			--with-curses-dir=${STAGING_TARGET_DIR}/usr \
			--disable-full-paths \
			--with-cfg-file=/etc/lynx.cfg \
			--with-lss-file=/etc/lynx.lss \
			--disable-font-switch \
			--disable-japanese-utf8 \
			--disable-vertrace \
			--disable-trace \
			--disable-cjk \
			--disable-kbd-layout \
			--disable-prettysrc \
			--disable-finger \
			--disable-dired \
			--with-screen=ncurses \
			--disable-widec \
			--disable-locale-charset \
			--with-build-cc='$(HOST_CC)' \
			--with-build-cflags="$(HOST_CFLAGS)" \
			--with-build-cppflags="-I/usr/include/ncurses"
MAKE_FILE:=		makefile

lynx-install:
	${INSTALL_DIR} ${IDIR_LYNX}/etc ${IDIR_LYNX}/usr/bin
	${CP} ${WRKINST}/etc/lynx.{cfg,lss} ${IDIR_LYNX}/etc
	${CP} ${WRKINST}/usr/bin/lynx ${IDIR_LYNX}/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
