# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		wpa_supplicant
PKG_VERSION:=		2.10
PKG_RELEASE:=		2
PKG_HASH:=		20df7ae5154b3830355f8ab4269123a87affdea59fe74fe9292a91d0d7e17b2f
PKG_DESCR:=		wpa supplicant
PKG_SECTION:=		net/wifi
PKG_DEPENDS:=		libnl
PKG_BUILDDEP:=		libnl
PKG_NEEDS:=		threads
PKG_URL:=		http://hostap.epitest.fi/wpa_supplicant/
PKG_SITES:=		http://w1.fi/releases/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_DFLT_WPA_SUPPLICANT:=	y if ADK_TARGET_WITH_WIFI

WRKSRC=			${WRKDIST}/${PKG_NAME}

PKG_CHOICES_WPA_SUPPLICANT:=	WITH_INTERNAL WITH_LIBRESSL WITH_GNUTLS
PKGCD_WITH_LIBRESSL:=		use libressl for crypto
PKGCS_WITH_LIBRESSL:=		libressl
PKGCB_WITH_LIBRESSL:=		libressl
PKGCD_WITH_GNUTLS:=		use gnutls for crypto
PKGCS_WITH_GNUTLS:=		libgnutls
PKGCB_WITH_GNUTLS:=		gnutls
PKGCD_WITH_INTERNAL:=		use internal crypto library

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,WPA_SUPPLICANT,wpa-supplicant,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_CFLAGS+=		-I$(STAGING_TARGET_DIR)/usr/include/libnl3

CONFIG_STYLE:=          manual
INSTALL_STYLE:=         manual

MAKE_FLAGS+=		CPPFLAGS='${TARGET_CPPFLAGS}' \
			LDFLAGS='${TARGET_LDFLAGS}' \
			OPT_FLAGS='${TARGET_CFLAGS}' \
			KERNEL=${LINUX_DIR}

do-configure:
	${CP} ./files/config ${WRKBUILD}/.config
ifneq (${ADK_PACKAGE_WPA_SUPPLICANT_WITH_GNUTLS},)
	${SED} "s#openssl#gnutls#" ${WRKBUILD}/.config
endif
ifneq (${ADK_PACKAGE_WPA_SUPPLICANT_WITH_INTERNAL},)
	${SED} "s#openssl#internal#" ${WRKBUILD}/.config
endif

do-install:
	${INSTALL_DIR} ${IDIR_WPA_SUPPLICANT}/usr/sbin
	${INSTALL_BIN} ${WRKBUILD}/wpa_cli \
		${IDIR_WPA_SUPPLICANT}/usr/sbin/
	${INSTALL_BIN} ${WRKBUILD}/wpa_passphrase \
		${IDIR_WPA_SUPPLICANT}/usr/sbin/
	${INSTALL_BIN} ${WRKBUILD}/wpa_supplicant \
		${IDIR_WPA_SUPPLICANT}/usr/sbin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
