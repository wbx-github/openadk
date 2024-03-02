# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		freeradius-server
PKG_VERSION:=		3.2.3
PKG_RELEASE:=		1
PKG_HASH:=		4bde047122e588c63fe2d599a73f7ab9a863806f9e716e88a3d77080b482c577
PKG_DESCR:=		flexible radius server
PKG_SECTION:=		net/radius
PKG_DEPENDS:=		libltdl libpcre libtalloc libressl libatomic
PKG_BUILDDEP:=		libtool pcre talloc libressl
PKG_NEEDS:=		threads
PKG_URL:=		http://www.freeradius.org/
PKG_SITES:=		https://github.com/FreeRADIUS/freeradius-server/releases/download/release_3_2_3/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_SUBPKGS:=		FREERADIUS_SERVER FREERADIUS_DEMOCERTS FREERADIUS_MOD_CHAP FREERADIUS_MOD_DETAIL
PKG_SUBPKGS+=		FREERADIUS_MOD_DIGEST FREERADIUS_MOD_FILES FREERADIUS_MOD_LDAP FREERADIUS_MOD_MSCHAP
PKG_SUBPKGS+=		FREERADIUS_MOD_PAP FREERADIUS_MOD_PREPROCESS FREERADIUS_MOD_REALM FREERADIUS_MOD_SQL
PKG_SUBPKGS+=		FREERADIUS_MOD_SQL_MYSQL FREERADIUS_MOD_SQL_PGSQL FREERADIUS_UTILS

# sub package build dependencies
PKGSB_FREERADIUS_MOD_LDAP:=		openldap
PKGSB_FREERADIUS_MOD_SQL_MYSQL:=	mariadb
PKGSB_FREERADIUS_MOD_SQL_PGSQL:=	postgresql
PKGSS_FREERADIUS_MOD_LDAP:=		libopenldap
PKGSS_FREERADIUS_MOD_SQL_MYSQL:=	libmariadbclient
PKGSS_FREERADIUS_MOD_SQL_PGSQL:=	libpq

PKGSD_FREERADIUS_DEMOCERTS:= 		Demo certificates to test the server
PKGSN_FREERADIUS_DEMOCERTS:=		freeradius-server
PKGSD_FREERADIUS_MOD_CHAP:=		CHAP authentication module
PKGSN_FREERADIUS_MOD_CHAP:=		freeradius-server
PKGSD_FREERADIUS_MOD_DETAIL:=		Detailed accounting module
PKGSN_FREERADIUS_MOD_DETAIL:=		freeradius-server
PKGSD_FREERADIUS_MOD_DIGEST:=		Digest authentication module
PKGSN_FREERADIUS_MOD_DIGEST:=		freeradius-server
PKGSD_FREERADIUS_MOD_FILES:=		Module using local files for authorization
PKGSN_FREERADIUS_MOD_FILES:=		freeradius-server
PKGSD_FREERADIUS_MOD_LDAP:=		LDAP module
PKGSN_FREERADIUS_MOD_LDAP:=		freeradius-server
PKGSD_FREERADIUS_MOD_MSCHAP:=		MS-CHAP and MS-CHAPv2 module
PKGSN_FREERADIUS_MOD_MSCHAP:=		freeradius-server
PKGSD_FREERADIUS_MOD_PAP:=		PAP authentication module
PKGSN_FREERADIUS_MOD_PAP:=		freeradius-server
PKGSD_FREERADIUS_MOD_PREPROCESS:=	Request pre-processing module
PKGSN_FREERADIUS_MOD_PREPROCESS:=	freeradius-server
PKGSD_FREERADIUS_MOD_REALM:=		Realms handling module
PKGSN_FREERADIUS_MOD_REALM:=		freeradius-server
PKGSD_FREERADIUS_MOD_SQL:=		Base SQL module
PKGSN_FREERADIUS_MOD_SQL:=		freeradius-server
PKGSD_FREERADIUS_MOD_SQL_MYSQL:=	MySQL module
PKGSN_FREERADIUS_MOD_SQL_MYSQL:=	freeradius-server
PKGSD_FREERADIUS_MOD_SQL_PGSQL:=	PostgreSQL module
PKGSN_FREERADIUS_MOD_SQL_PGSQL:=	freeradius-server
PKGSD_FREERADIUS_UTILS:=		Misc. client utilities
PKGSN_FREERADIUS_UTILS:=		freeradius-server

PKG_CONFIGURE_OPTS:=

ifneq (${ADK_PACKAGE_FREERADIUS_MOD_LDAP},)
PKG_CONFIGURE_LIBS+=	-lcrypto -lssl
PKG_CONFIGURE_OPTS+=	--with-rlm_ldap-include-dir="${STAGING_TARGET_DIR}/usr/include" \
			--with-rlm_ldap-lib-dir="${STAGING_TARGET_DIR}/usr/lib"
else
PKG_CONFIGURE_OPTS+=	--without-rlm_ldap
endif

ifneq (${ADK_PACKAGE_FREERADIUS_MOD_SQL_MYSQL},)
PKG_CONFIGURE_LIBS+=	-lz
PKG_CONFIGURE_OPTS+=	--with-mysql-include-dir="${STAGING_TARGET_DIR}/usr/include/mysql" \
			--with-mysql-lib-dir="${STAGING_TARGET_DIR}/usr/lib/mysql" \
			--without-threads \
			--with-rlm_sql
else
PKG_CONFIGURE_OPTS+=	--without-rlm_sql_mysql
endif
ifneq (${ADK_PACKAGE_FREERADIUS_MOD_SQL_PGSQL},)
PKG_CONFIGURE_OPTS+=	--with-rlm_sql_postgresql-include-dir="${STAGING_TARGET_DIR}/usr/include" \
			--with-rlm_sql_postgresql-lib-dir="${STAGING_TARGET_DIR}/usr/lib" \
			--with-rlm_sql
else
PKG_CONFIGURE_OPTS+=	--without-rlm_sql_postgresql
endif

include ${ADK_TOPDIR}/mk/package.mk

define PKG_mod_template

INSTALL_MODS_$${ADK_PACKAGE_${1}}+=	${2}-install

${2}-install:
	${INSTALL_DIR} $${IDIR_${1}}/usr/lib/freeradius
	for m in ${2}; do \
		${CP} ${WRKINST}/usr/lib/freeradius/$$$${m}.so \
		  $${IDIR_${1}}/usr/lib/freeradius/ ; \
	done
	-${INSTALL_DIR} $${IDIR_${1}}/etc/freeradius
	for f in ${3}; do \
		${CP} ${WRKINST}/etc/freeradius/$$$${f} \
		  $${IDIR_${1}}/etc/freeradius/ ; \
	done
endef

$(eval $(call PKG_template,FREERADIUS_SERVER,freeradius-server,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,FREERADIUS_DEMOCERTS,freeradius-democerts,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_FREERADIUS_DEMOCERTS},${PKG_SECTION}))
$(eval $(call PKG_template,FREERADIUS_MOD_CHAP,freeradius-mod-chap,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_FREERADIUS_MOD_CHAP},${PKG_SECTION}))
$(eval $(call PKG_template,FREERADIUS_MOD_DETAIL,freeradius-mod-detail,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_FREERADIUS_MOD_DETAIL},${PKG_SECTION}))
$(eval $(call PKG_template,FREERADIUS_MOD_DIGEST,freeradius-mod-digest,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_FREERADIUS_MOD_DIGEST},${PKG_SECTION}))
$(eval $(call PKG_template,FREERADIUS_MOD_FILES,freeradius-mod-files,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_FREERADIUS_MOD_FILES},${PKG_SECTION}))
$(eval $(call PKG_template,FREERADIUS_MOD_LDAP,freeradius-mod-ldap,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS_LDAP},${PKGSD_FREERADIUS_MOD_LDAP},${PKG_SECTION}))
$(eval $(call PKG_template,FREERADIUS_MOD_MSCHAP,freeradius-mod-mschap,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_FREERADIUS_MOD_MSCHAP},${PKG_SECTION}))
$(eval $(call PKG_template,FREERADIUS_MOD_PAP,freeradius-mod-pap,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_FREERADIUS_MOD_PAP},${PKG_SECTION}))
$(eval $(call PKG_template,FREERADIUS_MOD_PREPROCESS,freeradius-mod-preprocess,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_FREERADIUS_MOD_PREPROCESS},${PKG_SECTION}))
$(eval $(call PKG_template,FREERADIUS_MOD_REALM,freeradius-mod-realm,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_FREERADIUS_MOD_REALM},${PKG_SECTION}))
$(eval $(call PKG_template,FREERADIUS_MOD_SQL,freeradius-mod-sql,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_FREERADIUS_MOD_SQL},${PKG_SECTION}))
$(eval $(call PKG_template,FREERADIUS_MOD_SQL_MYSQL,freeradius-mod-sql-mysql,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS_MYSQL},${PKGSD_FREERADIUS_MOD_SQL_MYSQL},${PKG_SECTION}))
$(eval $(call PKG_template,FREERADIUS_MOD_SQL_PGSQL,freeradius-mod-sql-pgsql,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS_PGSQL},${PKGSD_FREERADIUS_MOD_SQL_PGSQL},${PKG_SECTION}))
$(eval $(call PKG_template,FREERADIUS_UTILS,freeradius-utils,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_FREERADIUS_UTILS},${PKG_SECTION}))

$(eval $(call PKG_mod_template,FREERADIUS_MOD_CHAP,rlm_chap,))
$(eval $(call PKG_mod_template,FREERADIUS_MOD_DETAIL,rlm_detail,))
$(eval $(call PKG_mod_template,FREERADIUS_MOD_DIGEST,rlm_digest,))
$(eval $(call PKG_mod_template,FREERADIUS_MOD_FILES,rlm_files,acct_users preproxy_users users))
$(eval $(call PKG_mod_template,FREERADIUS_MOD_MSCHAP,rlm_mschap,))
$(eval $(call PKG_mod_template,FREERADIUS_MOD_LDAP,rlm_ldap,))
$(eval $(call PKG_mod_template,FREERADIUS_MOD_PAP,rlm_pap,))
$(eval $(call PKG_mod_template,FREERADIUS_MOD_PREPROCESS,rlm_preprocess,hints huntgroups))
$(eval $(call PKG_mod_template,FREERADIUS_MOD_REALM,rlm_realm,proxy.conf))
$(eval $(call PKG_mod_template,FREERADIUS_MOD_SQL,rlm_sql,))
$(eval $(call PKG_mod_template,FREERADIUS_MOD_SQL_MYSQL,rlm_sql_mysql,))
$(eval $(call PKG_mod_template,FREERADIUS_MOD_SQL_PGSQL,rlm_sql_postgresql,))

CONFIGURE_ARGS+=	${PKG_CONFIGURE_OPTS} \
			--libdir=/usr/lib/freeradius \
			--libexecdir=/usr/lib/freeradius \
			--disable-openssl-version-check \
			--with-execinfo-include-dir=/dev/null \
			--with-threads=yes \
			--with-openssl-include-dir=${STAGING_TARGET_DIR}/usr/include \
			--with-openssl-lib-dir=${STAGING_TARGET_DIR}/usr/lib \
			--with-system-libltld \
			--enable-strict-dependencies \
			--with-raddbdir=/etc/freeradius \
			--without-edir \
			--without-snmp \
			--without-experimental-modules \
			--without-rlm_attr-rewrite \
			--without-rlm_checkval \
			--without-rlm_counter \
			--without-rlm_dbm \
			--without-rlm_eap \
			--without-rlm_eap2 \
			--without-rlm_eap_sim \
			--without-rlm_example \
			--without-rlm_ippool \
			--without-rlm_json \
			--without-rlm_krb5 \
			--without-rlm_otp \
			--without-rlm_smsotp \
			--without-rlm_pam \
			--without-rlm_perl \
			--without-rlm_python3 \
			--without-rlm_radutmp \
			--without-rlm_rest \
			--without-rlm_ruby \
			--without-rlm_python \
			--without-rlm_smb \
			--without-rlm_sqlcounter \
			--without-rlm_sql_db2 \
			--without-rlm_sql_freetds \
			--without-rlm_sql_iodbc \
			--without-rlm_sql_oracle \
			--without-rlm_sql_sybase \
			--without-rlm_sql_unixodbc \
			--without-rlm_sql_log \
			--without-rlm_redis \
			--without-rlm_cache_redis \
			--without-rlm_rediswho \
			--without-rlm_unbound \
			--without-rlm_unix \
			--without-rlm_eap_ikev2 \
			--without-rlm_eap_tnc \
			--without-rlm_cache_memcached \
			--without-rlm_opendirectory \
			--without-rlm_sql_firebird \
			--without-rlm_sql_sqlite
CONFIGURE_ENV+=		ax_cv_cc_builtin_choose_expr=yes \
			ax_cv_cc_builtin_types_compatible_p=yes \
			ax_cv_cc_builtin_bswap64=yes \
			ax_cv_cc_bounded_attribute=yes \
FAKE_FLAGS+=		INSTALLSTRIP=""
MAKE_ENV+=		VERBOSE=1 \
			R="$(WRKINST)"

freeradius-server-install: ${INSTALL_MODS_y} ${INSTALL_MODS_m}
	-${INSTALL_DIR} ${IDIR_FREERADIUS_SERVER}/etc/freeradius
	${CP} ./files/users ${IDIR_FREERADIUS_SERVER}/etc/freeradius/
	${INSTALL_DATA} ./files/radiusd.conf \
		${IDIR_FREERADIUS_SERVER}/etc/freeradius
	${INSTALL_DATA} ./files/clients.conf \
		${IDIR_FREERADIUS_SERVER}/etc/freeradius
	for f in dictionary; do \
		${CP} ${WRKINST}/etc/freeradius/$${f} \
		  ${IDIR_FREERADIUS_SERVER}/etc/freeradius/ ; \
	done
	${INSTALL_DIR} ${IDIR_FREERADIUS_SERVER}/usr/share/freeradius
	${CP} ${WRKINST}/usr/share/freeradius/dictionary* \
		${IDIR_FREERADIUS_SERVER}/usr/share/freeradius/
	${INSTALL_DIR} ${IDIR_FREERADIUS_SERVER}/usr/lib/freeradius
	${CP} ${WRKINST}/usr/lib/freeradius/libfreeradius-{dhcp,eap,server,radius}.so \
	  ${IDIR_FREERADIUS_SERVER}/usr/lib
	${INSTALL_DIR} ${IDIR_FREERADIUS_SERVER}/usr/sbin
	${CP} ${WRKINST}/usr/sbin/radiusd \
	  ${IDIR_FREERADIUS_SERVER}/usr/sbin/
	${INSTALL_DIR} ${IDIR_FREERADIUS_DEMOCERTS}/etc/freeradius
	${CP} ${WRKINST}/etc/freeradius/certs \
	  ${IDIR_FREERADIUS_DEMOCERTS}/etc/freeradius/
	rm -rf ${IDIR_FREERADIUS_DEMOCERTS}/etc/freeradius/certs/README
	rm -rf ${IDIR_FREERADIUS_DEMOCERTS}/etc/freeradius/certs/new*
	rm -rf ${IDIR_FREERADIUS_DEMOCERTS}/etc/freeradius/certs/demoCA/index*
	rm -rf ${IDIR_FREERADIUS_DEMOCERTS}/etc/freeradius/certs/demoCA/serial*
	${INSTALL_DIR} ${IDIR_FREERADIUS_UTILS}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/radclient \
		${IDIR_FREERADIUS_UTILS}/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
