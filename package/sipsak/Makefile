# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		sipsak
PKG_VERSION:=		0.9.8.1
PKG_RELEASE:=		1
PKG_HASH:=		c6faa022cd8c002165875d4aac83b7a2b59194f0491802924117fc6ac980c778
PKG_DESCR:=		sip stress and diagnostics utility
PKG_SECTION:=		net/voip
PKG_SITES:=		https://github.com/nils-ohlmeier/sipsak/releases/download/$(PKG_VERSION)/

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_CHOICES_SIPSAK:=	WITH_LIBRESSL WITHOUT_SSL
PKGCD_WITH_LIBRESSL:=	use libressl for crypto
PKGCB_WITH_LIBRESSL:=	libressl
PKGCS_WITH_LIBRESSL:=	libressl ca-certificates
PKGCD_WITHOUT_SSL:=	use no ssl

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,SIPSAK,sipsak,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ENV+=		ac_cv_func_malloc_0_nonnull=yes
CONFIGURE_ARGS+=	--disable-gnutls

sipsak-install:
	${INSTALL_DIR} ${IDIR_SIPSAK}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/sipsak ${IDIR_SIPSAK}/usr/bin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
