# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		vtun
PKG_VERSION:=		3.0.4
PKG_RELEASE:=		1
PKG_HASH:=		abf8df6b15e3febeaaeae2ce24ead7105eb1537ad4ec0d830c83cbb684fd98b9
PKG_DESCR:=		vpn tunnel daemon
PKG_SECTION:=		net/security
PKG_DEPENDS:=		zlib liblzo libressl
PKG_BUILDDEP:=		zlib liblzo libressl
PKG_KDEPENDS:=		tun
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=vtun/}

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,VTUN,vtun,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

INSTALL_STYLE:=		manual

CONFIGURE_ARGS+=	--with-ssl-headers=$(STAGING_TARGET_DIR)/usr/include/openssl \
			--disable-lzo
ALL_TARGET:=		vtund

do-install:
	${INSTALL_DIR} ${IDIR_VTUN}/usr/sbin ${IDIR_VTUN}/etc
	${INSTALL_DATA} ${WRKBUILD}/vtund.conf ${IDIR_VTUN}/etc/
	${INSTALL_BIN} ${WRKBUILD}/vtund ${IDIR_VTUN}/usr/sbin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
