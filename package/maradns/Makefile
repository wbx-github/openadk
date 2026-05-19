# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		maradns
PKG_VERSION:=		3.5.0036
PKG_RELEASE:=		1
PKG_HASH:=		6cdbeb588c636ca2c19511af49ce56c8903ac264fcfed5fd759fdbedfea1b3a0
PKG_DESCR:=		small and secure DNS server
PKG_SECTION:=		net/dns
PKG_DEPENDS:=		duende
PKG_NEEDS:=		threads
PKG_URL:=		https://samboy.github.io/MaraDNS/webpage/
PKG_SITES:=		https://maradns.samiam.org/download/3.5/$(PKG_VERSION)/

PKG_CFLINE_MARADNS:=	depends on ADK_BROKEN

PKG_SUBPKGS:=		MARADNS DUENDE DEADWOOD ZONESERVER ASKMARA FETCHZONE
PKGSD_DUENDE:=		maradns deamonising tool
PKGSD_DEADWOOD:=	small and secure recursive DNS server
PKGSN_DEADWOOD:=	duende
PKGSD_ZONESERVER:=	maradns zone transfer daemon
PKGSN_ZONESERVER:=	duende
PKGSD_ASKMARA:=		maradns simple dns query tool
PKGSD_FETCHZONE:=	maradns zone retrieval tool

PKG_FLAVOURS_MARADNS:=	WITH_IPV6
PKGFD_WITH_IPV6:=	enable IPv6 support

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,MARADNS,maradns,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,DUENDE,duende,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_DUENDE},${PKG_SECTION}))
$(eval $(call PKG_template,DEADWOOD,deadwood,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_DEADWOOD},${PKG_SECTION}))
$(eval $(call PKG_template,ZONESERVER,zoneserver,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_ZONESERVER},${PKG_SECTION}))
$(eval $(call PKG_template,ASKMARA,askmara,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_ASKMARA},${PKG_SECTION}))
$(eval $(call PKG_template,FETCHZONE,fetchzone,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_FETCHZONE},${PKG_SECTION}))

CONFIG_STYLE:=		manual
FAKE_FLAGS+=		PREFIX="${WRKINST}/usr" \
			RPM_BUILD_ROOT="${WRKINST}"

CONFIGURE_ARGS:=
ifneq (${ADK_PACKAGE_MARADNS_WITH_IPV6},)
CONFIGURE_ARGS+=       --ipv6
endif

pre-install:
	@mkdir -p ${WRKINST}/usr/{sbin,bin,man/man{1,5,8}}

do-configure:
	(cd ${WRKBUILD} && ./configure ${CONFIGURE_ARGS});

maradns-install:
	${INSTALL_DIR} ${IDIR_MARADNS}/etc/maradns/logger
	${INSTALL_DIR} ${IDIR_MARADNS}/usr/sbin
	${INSTALL_DATA} ./files/mararc ${IDIR_MARADNS}/etc/mararc
	${INSTALL_DATA} ./files/sample.{zone,ptr} \
		${IDIR_MARADNS}/etc/maradns/
	${CP} ${WRKINST}/usr/sbin/maradns ${IDIR_MARADNS}/usr/sbin/

duende-install:
	${INSTALL_DIR} ${IDIR_DUENDE}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/duende ${IDIR_DUENDE}/usr/bin/

deadwood-install:
	${INSTALL_DIR} ${IDIR_DEADWOOD}/etc/maradns/logger
	${INSTALL_DIR} ${IDIR_DEADWOOD}/usr/sbin
	${INSTALL_DATA} ./files/dwood3rc ${IDIR_DEADWOOD}/etc/
	${INSTALL_BIN} ${WRKINST}/usr/sbin/Deadwood \
		${IDIR_DEADWOOD}/usr/sbin/

zoneserver-install:
	${INSTALL_DIR} ${IDIR_ZONESERVER}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/usr/sbin/zoneserver \
		${IDIR_ZONESERVER}/usr/sbin/

askmara-install:
	${INSTALL_DIR} ${IDIR_ASKMARA}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/askmara ${IDIR_ASKMARA}/usr/bin/

fetchzone-install:
	${INSTALL_DIR} ${IDIR_FETCHZONE}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/fetchzone ${IDIR_FETCHZONE}/usr/bin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
