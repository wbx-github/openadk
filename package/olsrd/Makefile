# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		olsrd
PKG_VERSION:=		0.9.8
PKG_RELEASE:=		1
PKG_HASH:=		ee9e524224e5d5304dcf61f1dc5485c569da09d382934ff85b233be3e24821a3
PKG_DESCR:=		optimized link state routing protocol daemon
PKG_SECTION:=		net/wifi
PKG_BUILDDEP:=		gpsd
PKG_DEPENDS:=		gpsd
PKG_SITES:=		https://github.com/OLSR/olsrd/archive/refs/tags/
PKG_NOPARALLEL:=	1

DISTFILES:=		v${PKG_VERSION}.tar.gz

PKG_SUBPKGS:=		OLSRD OLSRD_MOD_DYN_GW OLSRD_MOD_HTTPINFO
PKG_SUBPKGS+=		OLSRD_MOD_NAMESERVICE OLSRD_MOD_TAS

PKGSD_OLSRD_MOD_DYN_GW:=	support for dynamic gateway
PKGSN_OLSRD_MOD_DYN_GW:=	olsrd
PKGSD_OLSRD_MOD_HTTPINFO:=	support for httpinfo
PKGSN_OLSRD_MOD_HTTPINFO:=	olsrd
PKGSD_OLSRD_MOD_NAMESERVICE:=	nameservice support
PKGSN_OLSRD_MOD_NAMESERVICE:=	olsrd
PKGSD_OLSRD_MOD_TAS:=		tas support
PKGSN_OLSRD_MOD_TAS:=		olsrd

include ${ADK_TOPDIR}/mk/package.mk

define PKG_mod_template

INSTALL_MODS_$${ADK_PACKAGE_${1}}+=	${2}-install

${2}-install:
	$${INSTALL_DIR} $${IDIR_${1}}/usr/lib
	$${CP} $${WRKINST}/usr/lib/olsrd_${2}.so.* $${IDIR_${1}}/usr/lib/

endef

$(eval $(call PKG_template,OLSRD,olsrd,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,OLSRD_MOD_DYN_GW,olsrd-mod-dyn-gw,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,OLSRD_MOD_HTTPINFO,olsrd-mod-httpinfo,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,OLSRD_MOD_NAMESERVICE,olsrd-mod-nameservice,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

$(eval $(call PKG_mod_template,OLSRD_MOD_DYN_GW,dyn_gw))
$(eval $(call PKG_mod_template,OLSRD_MOD_HTTPINFO,httpinfo))
$(eval $(call PKG_mod_template,OLSRD_MOD_NAMESERVICE,nameservice))

CONFIG_STYLE:=          manual

TARGET_CFLAGS+=		-fPIC -D_GNU_SOURCE
ALL_TARGET+=		libs
INSTALL_TARGET+=	install_libs
MAKE_ENV+=		OS="linux" DEBUG=0 STRIP="true" VERBOSE=1 OFLAGS="${TARGET_CFLAGS}" prefix="/usr"

post-install: ${INSTALL_MODS_y} ${INSTALL_MODS_m}
	${INSTALL_DIR} ${IDIR_OLSRD}/usr/sbin ${IDIR_OLSRD}/etc/olsrd
	${INSTALL_DATA} ${WRKINST}/etc/olsrd/olsrd.conf ${IDIR_OLSRD}/etc/olsrd
	${INSTALL_BIN} ${WRKINST}/usr/sbin/olsrd ${IDIR_OLSRD}/usr/sbin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
