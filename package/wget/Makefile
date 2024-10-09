# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		wget
PKG_VERSION:=		1.24.5
PKG_RELEASE:=		1
PKG_HASH:=		fa2dc35bab5184ecbc46a9ef83def2aaaa3f4c9f3c97d4bd19dcb07d4da637de
PKG_DESCR:=		retrieving files using http(s) and ftp
PKG_SECTION:=		net/http
HOST_BUILDDEP:=		openssl-host
PKG_URL:=		http://www.gnu.org/software/wget/
PKG_SITES:=		${MASTER_SITE_GNU:=wget/}
PKG_BB:=		1

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_CHOICES_WGET:=	WITH_OPENSSL WITH_LIBRESSL WITH_GNUTLS WITHOUT_SSL
PKGCD_WITH_OPENSSL:=	use openssl for crypto
PKGCS_WITH_OPENSSL:=	libopenssl ca-certificates libgmp
PKGCB_WITH_OPENSSL:=	openssl
PKGCD_WITH_LIBRESSL:=	use libressl for crypto
PKGCS_WITH_LIBRESSL:=	libressl ca-certificates libgmp
PKGCB_WITH_LIBRESSL:=	libressl
PKGCD_WITH_GNUTLS:=	use gnutls for crypto
PKGCS_WITH_GNUTLS:=	libgnutls ca-certificates libgmp
PKGCB_WITH_GNUTLS:=	gnutls
PKGCD_WITHOUT_SSL:=	use no ssl

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,WGET,wget,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,WGET,wget,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ARGS+=	--disable-pcre

ifeq (${ADK_PACKAGE_WGET_WITHOUT_SSL},y)
CONFIGURE_ARGS+=	--with-ssl=no
endif
ifeq (${ADK_PACKAGE_WGET_WITH_OPENSSL},y)
CONFIGURE_ARGS+=	--with-ssl=openssl \
			--with-openssl=yes \
			--with-libssl-prefix=${STAGING_TARGET_DIR}
endif
ifeq (${ADK_PACKAGE_WGET_WITH_LIBRESSL},y)
CONFIGURE_ARGS+=	--with-ssl=openssl \
			--with-openssl=yes \
			--with-libssl-prefix=${STAGING_TARGET_DIR}
endif
ifeq (${ADK_PACKAGE_WGET_WITH_GNUTLS},y)
CONFIGURE_ARGS+=	--with-ssl=gnutls \
			--with-libgnutls-prefix="$(STAGING_TARGET_DIR)/usr"
endif

HOST_CONFIGURE_ARGS+=	--with-ssl=openssl \
			--with-openssl=yes \
			--with-libssl-prefix=$(STAGING_HOST_DIR)/usr

wget-install:
	${INSTALL_DIR} ${IDIR_WGET}/etc ${IDIR_WGET}/usr/bin
	${INSTALL_DATA} ${WRKBUILD}/doc/sample.wgetrc \
		${IDIR_WGET}/etc/wgetrc
	${INSTALL_BIN} ${WRKINST}/usr/bin/wget ${IDIR_WGET}/usr/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
