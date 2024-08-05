# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		openldap
PKG_VERSION:=		2.6.8
PKG_RELEASE:=		1
PKG_HASH:=		48969323e94e3be3b03c6a132942dcba7ef8d545f2ad35401709019f696c3c4e
PKG_DESCR:=		ldap client libraries
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		libsasl2 libuuid libncurses libressl
PKG_BUILDDEP:=		cyrus-sasl util-linux libressl
PKG_NEEDS:=		threads c++
PKG_URL:=		http://www.openldap.org/
PKG_SITES:=		https://openldap.org/software/download/OpenLDAP/openldap-release/
PKG_LIBNAME:=		libopenldap
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tgz

PKG_SUBPKGS:=		LIBOPENLDAP OPENLDAP_UTILS OPENLDAP_SLAPD
PKGSD_OPENLDAP_UTILS:=	ldap utilities
PKGSS_OPENLDAP_UTILS:=	libopenldap
PKGSC_OPENLDAP_UTILS:=	net/misc
PKGSD_OPENLDAP_SLAPD:=	ldap server daemon
PKGSS_OPENLDAP_SLAPD:=	libopenldap
PKGSC_OPENLDAP_SLAPD:=	net/misc

PKG_FLAVOURS_OPENLDAP_SLAPD:=	WITH_IPV6
PKGFD_WITH_IPV6:=		enable IPv6 support

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LIBOPENLDAP,libopenldap,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))
$(eval $(call PKG_template,OPENLDAP_UTILS,openldap-utils,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_OPENLDAP_UTILS},${PKGSD_OPENLDAP_UTILS},${PKGSC_OPENLDAP_UTILS}))
$(eval $(call PKG_template,OPENLDAP_SLAPD,openldap-slapd,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_OPENLDAP_SLAPD},${PKGSD_OPENLDAP_SLAPD},${PKGSC_OPENLDAP_SLAPD}))

CONFIGURE_ENV+=		ac_cv_func_memcmp_working=yes
CONFIGURE_ARGS+= 	--enable-slapd \
			--libexecdir=/usr/sbin \
			--disable-bdb \
			--disable-hdb \
			--disable-relay \
			--enable-dynamic \
			--enable-syslog \
			--enable-local \
			--disable-syncprov \
			--without-fetch \
			--with-cyrus-sasl \
			--with-threads \
			--with-tls \
			--with-yielding_select="yes" \

ifneq (${ADK_PACKAGE_OPENLDAP_SLAPD_WITH_IPV6},)
CONFIGURE_ARGS+=	--enable-ipv6
else
CONFIGURE_ARGS+=	--disable-ipv6
endif

XAKE_FLAGS+=		STRIP="" CPPFLAGS="-D_GNU_SOURCE"

libopenldap-install:
	${INSTALL_DIR} ${IDIR_LIBOPENLDAP}/etc/openldap
	${CP} ${WRKINST}/etc/openldap/ldap.conf \
		${IDIR_LIBOPENLDAP}/etc/openldap
	${INSTALL_DIR} ${IDIR_LIBOPENLDAP}/usr/lib
	${CP} ${WRKINST}/usr/lib/lib{lber,ldap}*.so* \
		${IDIR_LIBOPENLDAP}/usr/lib

openldap-utils-install:
	${INSTALL_DIR} ${IDIR_OPENLDAP_UTILS}/etc/openldap-data
	${INSTALL_DIR} ${IDIR_OPENLDAP_UTILS}/usr/bin
	${CP} ${WRKINST}/usr/bin/ldap* ${IDIR_OPENLDAP_UTILS}/usr/bin/

openldap-slapd-install:
	${INSTALL_DIR} ${IDIR_OPENLDAP_SLAPD}/etc/openldap/schema
	${INSTALL_DIR} ${IDIR_OPENLDAP_SLAPD}/usr/sbin
	${CP} ${WRKINST}/usr/sbin/slap* ${IDIR_OPENLDAP_SLAPD}/usr/sbin
	${INSTALL_DATA} ${WRKINST}/etc/openldap/schema/*.schema \
		${IDIR_OPENLDAP_SLAPD}/etc/openldap/schema
	${INSTALL_DATA} ./files/slapd.conf ${IDIR_OPENLDAP_SLAPD}/etc/openldap

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
