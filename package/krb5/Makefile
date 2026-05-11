# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		krb5
PKG_VERSION:=		1.22.2
PKG_RELEASE:=		1
PKG_HASH:=		3243ffbc8ea4d4ac22ddc7dd2a1dc54c57874c40648b60ff97009763554eaf13
PKG_DESCR:=		kerberos server
PKG_SECTION:=		app/crypto
PKG_DEPENDS:=		libkrb5 libncurses keyutils
PKG_BUILDDEP:=		ncurses bison-host
PKG_NEEDS:=		threads intl
PKG_URL:=		http://web.mit.edu/kerberos/
PKG_SITES:=		https://kerberos.org/dist/krb5/1.22/
PKG_LIBNAME:=		libkrb5
PKG_OPTS:=		dev noscripts
PKG_NOPARALLEL:=	1

PKG_SUBPKGS:=		KRB5_SERVER KRB5_CLIENT LIBKRB5
PKGSD_LIBKRB5:=		kerberos libraries
PKGSC_LIBKRB5:=		libs/crypto
PKGSD_KRB5_CLIENT:=	kerberos client tools
PKGSC_KRB5_CLIENT:=	app/crypto
PKGSS_KRB5_CLIENT:=	libkrb5 libncurses

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz
WRKSRC=			${WRKDIST}/src

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,KRB5_SERVER,krb5-server,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,KRB5_CLIENT,krb5-client,$(PKG_VERSION)-${PKG_RELEASE},${PKGSS_KRB5_CLIENT},${PKGSD_KRB5_CLIENT},${PKGSC_KRB5_CLIENT}))
$(eval $(call PKG_template,LIBKRB5,libkrb5,$(PKG_VERSION)-${PKG_RELEASE},,${PKGSD_LIBKRB5},${PKGSC_LIBKRB5},${PKG_OPTS}))

CONFIGURE_ARGS+=	--disable-static \
			--localstatedir=/etc \
			--disable-profiled \
			--disable-pkinit \
			--without-system-et \
			--without-system-ss \
			--without-system-verto \
			--without-tcl
CONFIGURE_ENV+=		krb5_cv_attr_constructor_destructor=yes,yes \
			ac_cv_func_regcomp=yes \
			ac_cv_printf_positional=yes \
			ac_cv_file__etc_environment=no \
			ac_cv_file__etc_TIMEZONE=no


pre-build:
	# fix nm call in script, we need the GNU version of nm
	$(SED) "s#@@NM@@#${NM}#" ${WRKSRC}/util/export-check.pl

krb5-server-install:
	${INSTALL_DIR} ${IDIR_KRB5_SERVER}/etc/krb5kdc
	${INSTALL_DIR} ${IDIR_KRB5_SERVER}/usr/sbin
	${INSTALL_DIR} ${IDIR_KRB5_SERVER}/usr/lib/krb5/plugins/kdb
	${INSTALL_DATA} ./files/kdc.conf ${IDIR_KRB5_SERVER}/etc/krb5kdc
	${INSTALL_DATA} ./files/kadm5.acl ${IDIR_KRB5_SERVER}/etc/krb5kdc
	${INSTALL_BIN} ${WRKINST}/usr/bin/kadmin \
		${IDIR_KRB5_SERVER}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/usr/sbin/{kdb5_util,krb5kdc,kadmind,kadmin.local} \
		${IDIR_KRB5_SERVER}/usr/sbin
	${INSTALL_DATA} ${WRKINST}/usr/lib/krb5/plugins/kdb/db2.so \
		${IDIR_KRB5_SERVER}/usr/lib/krb5/plugins/kdb

krb5-client-install:
	${INSTALL_DIR} ${IDIR_KRB5_CLIENT}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/{kinit,kpasswd,klist,kdestroy,ktutil} \
		${IDIR_KRB5_CLIENT}/usr/bin

libkrb5-install:
	${INSTALL_DIR} ${IDIR_LIBKRB5}/etc
	${INSTALL_DIR} ${IDIR_LIBKRB5}/usr/lib
	${INSTALL_DATA} ./files/krb5.conf ${IDIR_LIBKRB5}/etc
	${CP} ${WRKINST}/usr/lib/lib{verto,gssrpc,kadm5clnt*,kadm5srv*,kdb5}.so* \
		${IDIR_LIBKRB5}/usr/lib
	${CP} ${WRKINST}/usr/lib/lib{gssapi_krb5,k5crypto,krb5,krb5support,com_err}.so* \
		${IDIR_LIBKRB5}/usr/lib
	echo '/usr/lib/libgssapi_krb5.so		mechglue_internal_krb5_init' \
		> ${IDIR_LIBKRB5}/etc/gssapi_mech.conf

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
