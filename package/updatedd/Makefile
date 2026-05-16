# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		updatedd
PKG_VERSION:=		2.6
PKG_RELEASE:=		1
PKG_HASH:=		9d240c7e9fcc3f6cb1d32410ca2dee10d359c53f1a5a30d8f3ec49b18b73f1d0
PKG_DESCR:=		update dynamic dns services
PKG_SECTION:=		net/dns
PKG_SITES:=		https://download.savannah.gnu.org/releases/updatedd/

PKG_SUBPKGS:=		UPDATEDD UPDATEDD_MOD_CHANGEIP UPDATEDD_MOD_DYNDNS UPDATEDD_MOD_EURODYNDNS
PKG_SUBPKGS+=		UPDATEDD_MOD_HN UPDATEDD_MOD_NOIP UPDATEDD_MOD_ODS UPDATEDD_MOD_OVH
PKG_SUBPKGS+=		UPDATEDD_MOD_REGFISH UPDATEDD_MOD_TZO
PKGSN_UPDATEDD_MOD_CHANGEIP:=	updatedd
PKGSN_UPDATEDD_MOD_DYNDNS:=	updatedd
PKGSN_UPDATEDD_MOD_EURODYNDNS:=	updatedd
PKGSN_UPDATEDD_MOD_HN:=		updatedd
PKGSN_UPDATEDD_MOD_NOIP:=	updatedd
PKGSN_UPDATEDD_MOD_ODS:=	updatedd
PKGSN_UPDATEDD_MOD_OVH:=	updatedd
PKGSN_UPDATEDD_MOD_REGFISH:=	updatedd
PKGSN_UPDATEDD_MOD_TZO:=	updatedd

DISTFILES:=		${PKG_NAME}_${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

define PKG_libinstall
	${INSTALL_DIR} ${IDIR_${1}}/usr/lib/updatedd
	${INSTALL_BIN} ${WRKINST}/usr/lib/updatedd/lib${2}.so ${IDIR_${1}}/usr/lib/updatedd/
endef

$(eval $(call PKG_template,UPDATEDD,updatedd,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,UPDATEDD_MOD_CHANGEIP,updatedd-mod-changeip,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,UPDATEDD_MOD_DYNDNS,updatedd-mod-dyndns,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,UPDATEDD_MOD_EURODYNDNS,updatedd-mod-eurodyndns,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,UPDATEDD_MOD_HN,updatedd-mod-hn,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,UPDATEDD_MOD_NOIP,updatedd-mod-noip,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,UPDATEDD_MOD_ODS,updatedd-mod-ods,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,UPDATEDD_MOD_OVH,updatedd-mod-ovh,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,UPDATEDD_MOD_REGFISH,updatedd-mod-regfish,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,UPDATEDD_MOD_TZO,updatedd-mod-tzo,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ARGS+=	ac_cv_lib_nsl_gethostbyname=no

updatedd-install:
	${INSTALL_DIR} ${IDIR_UPDATEDD}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/updatedd ${IDIR_UPDATEDD}/usr/bin/
	${INSTALL_DIR} ${IDIR_UPDATEDD}/usr/lib/updatedd
	$(call PKG_libinstall,UPDATEDD_MOD_CHANGEIP,changeip)
	$(call PKG_libinstall,UPDATEDD_MOD_DYNDNS,dyndns)
	$(call PKG_libinstall,UPDATEDD_MOD_EURODYNDNS,eurodyndns)
	$(call PKG_libinstall,UPDATEDD_MOD_HN,hn)
	$(call PKG_libinstall,UPDATEDD_MOD_NOIP,noip)
	$(call PKG_libinstall,UPDATEDD_MOD_ODS,ods)
	$(call PKG_libinstall,UPDATEDD_MOD_OVH,ovh)
	$(call PKG_libinstall,UPDATEDD_MOD_REGFISH,regfish)
	$(call PKG_libinstall,UPDATEDD_MOD_TZO,tzo)

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
