# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		lighttpd
PKG_VERSION:=		1.4.82
PKG_RELEASE:=		1
PKG_HASH:=		abfe74391f9cbd66ab154ea07e64f194dbe7e906ef4ed47eb3b0f3b46246c962
PKG_DESCR:=		lightweight web server
PKG_SECTION:=		net/http
PKG_DEPENDS:=		pcre2
PKG_BUILDDEP:=		pcre2
PKG_URL:=		http://www.lighttpd.net/
PKG_SITES:=		http://download.lighttpd.net/lighttpd/releases-1.4.x/

PKG_FLAVOURS_LIGHTTPD:=	WITH_IPV6
PKGFD_WITH_IPV6:=	enable ipv6 support

PKG_CHOICES_LIGHTTPD:=	WITH_OPENSSL WITHOUT_SSL
PKGCD_WITH_OPENSSL:=	use libopenssl for crypto
PKGCB_WITH_OPENSSL:=	openssl
PKGCS_WITH_OPENSSL:=	libopenssl ca-certificates
PKGCD_WITHOUT_SSL:=	use no ssl

PKG_SUBPKGS:=		LIGHTTPD LIGHTTPD_MOD_AUTH
PKG_SUBPKGS+=		LIGHTTPD_MOD_CGI LIGHTTPD_MOD_DIRLIST
PKG_SUBPKGS+=		LIGHTTPD_MOD_PROXY
PKG_SUBPKGS+=		LIGHTTPD_MOD_SSI LIGHTTPD_MOD_STATUS
PKGSD_LIGHTTPD_MOD_AUTH:=	authentication support
PKGSN_LIGHTTPD_MOD_AUTH:=	lighttpd
PKGSD_LIGHTTPD_MOD_CGI:=	CGI support
PKGSN_LIGHTTPD_MOD_CGI:=	lighttpd
PKGSD_LIGHTTPD_MOD_DIRLIST:=	Dirlisting support
PKGSB_LIGHTTPD_MOD_DIRLIST:=	pcre
PKGSS_LIGHTTPD_MOD_DIRLIST:=	libpcre
PKGSN_LIGHTTPD_MOD_DIRLIST:=	lighttpd
PKGSD_LIGHTTPD_MOD_PROXY:=	Proxy support
PKGSN_LIGHTTPD_MOD_PROXY:=	lighttpd
PKGSD_LIGHTTPD_MOD_SSI:=	SSI support
PKGSN_LIGHTTPD_MOD_SSI:=	lighttpd
PKGSD_LIGHTTPD_MOD_STATUS:=	Status support
PKGSN_LIGHTTPD_MOD_STATUS:=	lighttpd
PKGSD_LIGHTTPD_MOD_WEBDAV:=	Webdav support
PKGSB_LIGHTTPD_MOD_WEBDAV:=	libxml2 sqlite util-linux
PKGSS_LIGHTTPD_MOD_WEBDAV:=	libxml2 libsqlite libuuid
PKGSN_LIGHTTPD_MOD_WEBDAV:=	lighttpd

include $(ADK_TOPDIR)/mk/package.mk

define PKG_mod_template

INSTALL_MODS_$${ADK_PACKAGE_${1}}+=	${2}-install

${2}-install:
	${INSTALL_DIR} $$(IDIR_$(1))/usr/lib/lighttpd
	${INSTALL_BIN} $(WRKINST)/usr/lib/lighttpd/mod_$(2).so $$(IDIR_$(1))/usr/lib/lighttpd/

endef

$(eval $(call PKG_template,LIGHTTPD,lighttpd,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,LIGHTTPD_MOD_AUTH,lighttpd-mod-auth,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_LIGHTTPD_MOD_AUTH},${PKG_SECTION}))
$(eval $(call PKG_template,LIGHTTPD_MOD_CGI,lighttpd-mod-cgi,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_LIGHTTPD_MOD_CGI},${PKG_SECTION}))
$(eval $(call PKG_template,LIGHTTPD_MOD_DIRLIST,lighttpd-mod-dirlist,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_LIGHTTPD_MOD_DIRLIST},${PKG_SECTION}))
$(eval $(call PKG_template,LIGHTTPD_MOD_PROXY,lighttpd-mod-proxy,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_LIGHTTPD_MOD_PROXY},${PKG_SECTION}))
$(eval $(call PKG_template,LIGHTTPD_MOD_SSI,lighttpd-mod-ssi,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_LIGHTTPD_MOD_SSI},${PKG_SECTION}))
$(eval $(call PKG_template,LIGHTTPD_MOD_STATUS,lighttpd-mod-status,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_LIGHTTPD_MOD_STATUS},${PKG_SECTION}))

$(eval $(call PKG_mod_template,LIGHTTPD_MOD_AUTH,auth))
$(eval $(call PKG_mod_template,LIGHTTPD_MOD_CGI,cgi))
$(eval $(call PKG_mod_template,LIGHTTPD_MOD_DIRLIST,dirlisting))
$(eval $(call PKG_mod_template,LIGHTTPD_MOD_PROXY,proxy))
$(eval $(call PKG_mod_template,LIGHTTPD_MOD_SSI,ssi))
$(eval $(call PKG_mod_template,LIGHTTPD_MOD_STATUS,status))

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ARGS+=	--libdir=/usr/lib/lighttpd \
			--sysconfdir=/etc/lighttpd \
			--without-attr \
			--without-zlib \
			--without-bzip2 \
			--without-fam \
			--without-ldap \
			--without-lua \
			--without-mysql \
			--without-webdav-props \
			--without-webdav-locks \
			--without-valgrind

ifneq ($(ADK_PACKAGE_LIGHTTPD_MOD_SSI)$(ADK_PACKAGE_LIGHTTPD_MOD_DIRLIST)$(ADK_PACKAGE_LIGHTTPD_MOD_REWRITE)$(ADK_PACKAGE_LIGHTTPD_MOD_REDIRECT),)
CONFIGURE_ARGS+=	--with-pcre2
CONFIGURE_ENV+=		PCRE_LIB="-lpcre2"
else
CONFIGURE_ARGS+=	--without-pcre2
endif

ifneq ($(ADK_PACKAGE_LIGHTTPD_WITH_IPV6),)
CONFIGURE_ARGS+=	--enable-ipv6
else
CONFIGURE_ARGS+=	--disable-ipv6
endif

ifeq ($(ADK_PACKAGE_LIGHTTPD_WITH_OPENSSL),y)
CONFIGURE_ARGS+=	--with-openssl
endif
ifeq ($(ADK_PACKAGE_LIGHTTPD_WITHOUT_SSL),y)
CONFIGURE_ARGS+=	--without-openssl
endif

lighttpd-install: ${INSTALL_MODS_y} ${INSTALL_MODS_m}
	${INSTALL_DIR} $(IDIR_LIGHTTPD)/etc/lighttpd/conf.d
	${INSTALL_DATA} ./files/lighttpd.conf $(IDIR_LIGHTTPD)/etc/lighttpd
	${INSTALL_DATA} ./files/modules.conf $(IDIR_LIGHTTPD)/etc/lighttpd
	${CP} ${WRKBUILD}/doc/config/conf.d/*.conf \
		$(IDIR_LIGHTTPD)/etc/lighttpd/conf.d
	${CP} ./files/conf.d $(IDIR_LIGHTTPD)/etc/lighttpd
	${INSTALL_DIR} $(IDIR_LIGHTTPD)/usr/lib/lighttpd
	for m in indexfile staticfile accesslog; do \
		$(CP) $(WRKINST)/usr/lib/lighttpd/mod_$$m.so $(IDIR_LIGHTTPD)/usr/lib/lighttpd/ ; \
	done
	${INSTALL_DIR} $(IDIR_LIGHTTPD)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/lighttpd $(IDIR_LIGHTTPD)/usr/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
