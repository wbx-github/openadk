# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		opensips
PKG_VERSION:=		3.4.4
PKG_RELEASE:=		1
PKG_HASH:=		eab3608a464884fc40f33cc639a5b124dc838799bd4a9701b7a8af49fb937fc7
PKG_DESCR:=		high-performance, configurable, free sip server
PKG_SECTION:=		net/voip
PKG_DEPENDS:=		libressl
PKG_BUILDDEP:=		libressl flex-host bison-host
PKG_URL:=		http://opensips.org/
PKG_SITES:=		http://opensips.org/pub/opensips/$(PKG_VERSION)/

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_SUBPKGS:=		OPENSIPS OPENSIPS_MOD_ACCOUNTING OPENSIPS_MOD_AUTH
PKG_SUBPKGS+=		OPENSIPS_MOD_AUTH_DB OPENSIPS_MOD_AVPOPS OPENSIPS_MOD_DISPATCHER
PKG_SUBPKGS+=		OPENSIPS_MOD_DIVERSION OPENSIPS_MOD_FLATSTORE OPENSIPS_MOD_GFLAGS
PKG_SUBPKGS+=		OPENSIPS_MOD_GROUP OPENSIPS_MOD_MEDIAPROXY OPENSIPS_MOD_MSILO
PKG_SUBPKGS+=		OPENSIPS_MOD_NATHELPER OPENSIPS_MOD_OPTIONS
PKG_SUBPKGS+=		OPENSIPS_MOD_PERMISSIONS OPENSIPS_MOD_PIKE
PKG_SUBPKGS+=		OPENSIPS_MOD_UAC OPENSIPS_MOD_UAC_REDIRECT

PKGSD_OPENSIPS_MOD_ACCOUNTING:=		accounting support
PKGSN_OPENSIPS_MOD_ACCOUNTING:=		opensips
PKGSD_OPENSIPS_MOD_AUTH:=		authentication support
PKGSN_OPENSIPS_MOD_AUTH:=		opensips
PKGSD_OPENSIPS_MOD_AUTH_DB:=		authentication database support
PKGSN_OPENSIPS_MOD_AUTH_DB:=		opensips
PKGSD_OPENSIPS_MOD_AVPOPS:=		avpops support
PKGSN_OPENSIPS_MOD_AVPOPS:=		opensips
PKGSD_OPENSIPS_MOD_DISPATCHER:=		dispatcher support
PKGSN_OPENSIPS_MOD_DISPATCHER:=		opensips
PKGSD_OPENSIPS_MOD_DIVERSION:=		diversion support
PKGSN_OPENSIPS_MOD_DIVERSION:=		opensips
PKGSD_OPENSIPS_MOD_FLATSTORE:=		flatstore support
PKGSN_OPENSIPS_MOD_FLATSTORE:=		opensips
PKGSD_OPENSIPS_MOD_GFLAGS:=		gflags support
PKGSN_OPENSIPS_MOD_GFLAGS:=		opensips
PKGSD_OPENSIPS_MOD_GROUP:=		group support
PKGSN_OPENSIPS_MOD_GROUP:=		opensips
PKGSD_OPENSIPS_MOD_MEDIAPROXY:=		mediaproxy support
PKGSN_OPENSIPS_MOD_MEDIAPROXY:=		opensips
PKGSD_OPENSIPS_MOD_MSILO:=		msilo support
PKGSN_OPENSIPS_MOD_MSILO:=		opensips
PKGSD_OPENSIPS_MOD_NATHELPER:=		nathelper support
PKGSN_OPENSIPS_MOD_NATHELPER:=		opensips
PKGSD_OPENSIPS_MOD_OPTIONS:=		options support
PKGSN_OPENSIPS_MOD_OPTIONS:=		opensips
PKGSD_OPENSIPS_MOD_PERMISSIONS:=	permissions support
PKGSN_OPENSIPS_MOD_PERMISSIONS:=	opensips
PKGSD_OPENSIPS_MOD_PIKE:=		pike support
PKGSN_OPENSIPS_MOD_PIKE:=		opensips
PKGSD_OPENSIPS_MOD_UAC:=		uac support
PKGSN_OPENSIPS_MOD_UAC:=		opensips
PKGSD_OPENSIPS_MOD_UAC_REDIRECT:=	uac redirect support
PKGSN_OPENSIPS_MOD_UAC_REDIRECT:=	opensips

include $(ADK_TOPDIR)/mk/package.mk

define PKG_mod_template

INSTALL_MODS_$${ADK_PACKAGE_${1}}+=    ${2}-install

${2}-install:
	[ -z "$(2)" ] || install -d -m 0755 $$(IDIR_$(1))/usr/lib/opensips/modules/
	$(CP) $(WRKBUILD)/modules/$(2)/$(2).so \
			$$(IDIR_$(1))/usr/lib/opensips/modules/

endef

$(eval $(call PKG_template,OPENSIPS,opensips,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,OPENSIPS_MOD_ACCOUNTING,opensips-mod-acc,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,OPENSIPS_MOD_AUTH,opensips-mod-auth,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,OPENSIPS_MOD_AUTH_DB,opensips-mod-auth-db,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,OPENSIPS_MOD_AVPOPS,opensips-mod-avpops,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,OPENSIPS_MOD_DISPATCHER,opensips-mod-dispatcher,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,OPENSIPS_MOD_DIVERSION,opensips-mod-diversion,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,OPENSIPS_MOD_FLATSTORE,opensips-mod-flatstore,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,OPENSIPS_MOD_GFLAGS,opensips-mod-gflags,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,OPENSIPS_MOD_GROUP,opensips-mod-group,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,OPENSIPS_MOD_MEDIAPROXY,opensips-mod-mediaproxy,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,OPENSIPS_MOD_MSILO,opensips-mod-msilo,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,OPENSIPS_MOD_NATHELPER,opensips-mod-nathelper,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,OPENSIPS_MOD_OPTIONS,opensips-mod-options,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,OPENSIPS_MOD_PERMISSIONS,opensips-mod-permissions,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,OPENSIPS_MOD_PIKE,opensips-mod-pike,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,OPENSIPS_MOD_UAC,opensips-mod-uac,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,OPENSIPS_MOD_UAC_REDIRECT,opensips-mod-uac-redirect,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

$(eval $(call PKG_mod_template,OPENSIPS_MOD_ACCOUNTING,acc))
$(eval $(call PKG_mod_template,OPENSIPS_MOD_AUTH,auth))
$(eval $(call PKG_mod_template,OPENSIPS_MOD_AUTH_DB,auth_db))
$(eval $(call PKG_mod_template,OPENSIPS_MOD_AVPOPS,avpops))
$(eval $(call PKG_mod_template,OPENSIPS_MOD_DISPATCHER,dispatcher))
$(eval $(call PKG_mod_template,OPENSIPS_MOD_DIVERSION,diversion))
$(eval $(call PKG_mod_template,OPENSIPS_MOD_FLATSTORE,db_flatstore))
$(eval $(call PKG_mod_template,OPENSIPS_MOD_GFLAGS,gflags))
$(eval $(call PKG_mod_template,OPENSIPS_MOD_GROUP,group))
$(eval $(call PKG_mod_template,OPENSIPS_MOD_MEDIAPROXY,mediaproxy))
$(eval $(call PKG_mod_template,OPENSIPS_MOD_MSILO,msilo))
$(eval $(call PKG_mod_template,OPENSIPS_MOD_NATHELPER,nathelper))
$(eval $(call PKG_mod_template,OPENSIPS_MOD_OPTIONS,options))
$(eval $(call PKG_mod_template,OPENSIPS_MOD_PERMISSIONS,permissions))
$(eval $(call PKG_mod_template,OPENSIPS_MOD_PIKE,pike))
$(eval $(call PKG_mod_template,OPENSIPS_MOD_SPEEDIAL,speeddial))
$(eval $(call PKG_mod_template,OPENSIPS_MOD_UAC,uac))
$(eval $(call PKG_mod_template,OPENSIPS_MOD_UAC_REDIRECT,uac_redirect))

# Select here the modules for the main package
OPENSIPS_MODULES:=	sl tm rr maxfwd usrloc registrar db_text textops exec mi_fifo signaling

OPENSIPS_MODULE_FILES:=	$(foreach module,$(OPENSIPS_MODULES),modules/$(module)/$(module).so)
OPENSIPS_MODULES:=	$(patsubst %,modules/%,$(OPENSIPS_MODULES))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

do-build:
	PATH='$(HOST_PATH)' $(MAKE) -C $(WRKBUILD) \
		prefix=/ \
		TLS=1 \
		FREERADIUS=0 \
		NICER=0 \
		NO_EPOLL=1 \
		CC="$(TARGET_CC)" \
		OS="linux" \
		ARCH="$(ADK_TARGET_ARCH)"  \
		CFLAGS="$(TARGET_CFLAGS) -fPIC" \
		LOCALBASE="$(STAGING_TARGET_DIR)/usr" \
		SYSBASE="$(STAGING_TARGET_DIR)/usr" \
		all modules

do-install: ${INSTALL_MODS_y} ${INSTALL_MODS_m}
	${INSTALL_DIR} $(IDIR_OPENSIPS)/etc/opensips
	${INSTALL_DIR} $(IDIR_OPENSIPS)/usr/sbin
	${INSTALL_DIR} $(IDIR_OPENSIPS)/usr/lib/opensips/modules
	$(CP) $(WRKBUILD)/$(PKG_NAME) $(IDIR_OPENSIPS)/usr/sbin/
	(cd $(WRKBUILD);\
		$(CP) $(OPENSIPS_MODULE_FILES) \
		$(IDIR_OPENSIPS)/usr/lib/opensips/modules/; \
	)
	$(CP) ./files/opensips.cfg $(IDIR_OPENSIPS)/etc/opensips/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
