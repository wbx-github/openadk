# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		socat
PKG_VERSION:=		1.7.4.3
PKG_RELEASE:=		1
PKG_HASH:=		d697245144731423ddbbceacabbd29447089ea223e9a439b28f9ff90d0dd216e
PKG_DESCR:=		multipurpose relay
PKG_SECTION:=		net/misc
PKG_NEEDS:=		threads
PKG_URL:=		http://www.dest-unreach.org/socat/
PKG_SITES:=		http://www.dest-unreach.org/socat/download/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_CHOICES_SOCAT:=	WITH_LIBRESSL WITHOUT_SSL
PKGCD_WITH_LIBRESSL:=	use libressl for crypto
PKGCB_WITH_LIBRESSL:=	libressl
PKGCS_WITH_LIBRESSL:=	libressl
PKGCD_WITHOUT_SSL:=	use no ssl

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,SOCAT,socat,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

AUTOTOOL_STYLE:=	autoconf
CONFIGURE_ENV+=		sc_cv_termios_ispeed=no \
			sc_cv_sys_crdly_shift=9 \
			sc_cv_sys_tabdly_shift=11 \
			sc_cv_sys_csize_shift=4
CONFIGURE_ARGS+=	--disable-libwrap \
			--disable-readline

ifeq (${ADK_PACKAGE_SOCAT_WITH_LIBRESSL},y)
CONFIGURE_ARGS+=	--enable-openssl
endif
ifeq (${ADK_PACKAGE_SOCAT_WITHOUT_SSL},y)
CONFIGURE_ARGS+=	--disable-openssl
endif

socat-install:
	${INSTALL_DIR} ${IDIR_SOCAT}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/socat ${IDIR_SOCAT}/usr/bin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
