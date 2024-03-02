# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		hostapd
PKG_VERSION:=		2.10
PKG_RELEASE:=		1
PKG_HASH:=		206e7c799b678572c2e3d12030238784bc4a9f82323b0156b4c9466f1498915d
PKG_DESCR:=		wireless authenticator
PKG_SECTION:=		net/wifi
PKG_DEPENDS:=		libnl
PKG_BUILDDEP:=		libnl
PKG_SITES:=		http://w1.fi/releases/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_SUBPKGS:=		HOSTAPD HOSTAPD_UTILS
PKG_CHOICES_HOSTAPD:=	WITH_LIBRESSL WITH_GNUTLS
PKGCD_WITH_LIBRESSL:=	use libressl for crypto
PKGCS_WITH_LIBRESSL:=	libressl
PKGCB_WITH_LIBRESSL:=	libressl
PKGCD_WITH_GNUTLS:=	use gnutls for crypto
PKGCS_WITH_GNUTLS:=	libgnutls
PKGCB_WITH_GNUTLS:=	gnutls
PKGSN_HOSTAPD_UTILS:=	hostapd

WRKSRC=			${WRKDIST}/${PKG_NAME}

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,HOSTAPD,hostapd,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,HOSTAPD_UTILS,hostapd-utils,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
INSTALL_STYLE:=		manual

TARGET_CFLAGS+=		-I$(STAGING_TARGET_DIR)/usr/include/libnl3

do-configure:
	${CP} ./files/hostapd.config ${WRKBUILD}/.config
ifneq (${ADK_PACKAGE_HOSTAPD_WITH_GNUTLS},)
	${SED} "s#openssl#gnutls#" ${WRKBUILD}/.config
endif

do-install:
	${INSTALL_DIR} ${IDIR_HOSTAPD_UTILS}/usr/sbin
	${INSTALL_BIN} ${WRKBUILD}/hostapd_cli ${IDIR_HOSTAPD_UTILS}/usr/sbin/
	${INSTALL_DIR} ${IDIR_HOSTAPD}/etc
	${INSTALL_DIR} ${IDIR_HOSTAPD}/usr/sbin
	${INSTALL_BIN} ${WRKBUILD}/hostapd ${IDIR_HOSTAPD}/usr/sbin/
	${INSTALL_DATA} ./files/hostapd.conf ${IDIR_HOSTAPD}/etc

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
