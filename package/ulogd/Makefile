# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		ulogd
PKG_VERSION:=		2.0.5
PKG_RELEASE:=		1
PKG_HASH:=		a221cb9f77347c0ca00d0937e27c1b90e3291a553cc62a4139b788e2e420e8c0
PKG_DESCR:=		netfilter userspace logging daemon
PKG_SECTION:=		net/firewall
PKG_DEPENDS:=		iptables libnetfilter-conntrack libnetfilter-log libnetfilter-acct libmnl
PKG_BUILDDEP:=		iptables libnetfilter_conntrack libnetfilter_log libnetfilter_acct libmnl
PKG_URL:=		http://www.netfilter.org/projects/ulogd/
PKG_SITES:=		http://www.netfilter.org/projects/ulogd/files/
PKG_NOPARALLEL:=	1

PKG_SUBPKGS:=		ULOGD ULOGD_MOD_MARIADB ULOGD_MOD_PCAP ULOGD_MOD_PGSQL ULOGD_MOD_SQLITE
PKGSD_ULOGD_MOD_MARIADB:=	mariadb plugin for ulogd
PKGSB_ULOGD_MOD_MARIADB:=	mariadb
PKGSS_ULOGD_MOD_MARIADB:=	zlib libmariadbclient
PKGSN_ULOGD_MOD_MARIADB:=	ulogd
PKGSD_ULOGD_MOD_PGSQL:=		postgresql plugin for ulogd
PKGSB_ULOGD_MOD_PGSQL:=		postgresql
PKGSS_ULOGD_MOD_PGSQL:=		libpq
PKGSN_ULOGD_MOD_PGSQL:=		ulogd
PKGSD_ULOGD_MOD_SQLITE:=	sqlite plugin for ulogd
PKGSB_ULOGD_MOD_SQLITE:=	sqlite
PKGSS_ULOGD_MOD_SQLITE:=	libsqlite
PKGSN_ULOGD_MOD_SQLITE:=	ulogd
PKGSD_ULOGD_MOD_PCAP:=		libpcap plugin for ulogd
PKGSB_ULOGD_MOD_PCAP:=		libpcap
PKGSS_ULOGD_MOD_PCAP:=		libpcap
PKGSN_ULOGD_MOD_PCAP:=		ulogd

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.bz2

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,ULOGD,ulogd,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,ULOGD_MOD_MYSQL,ulogd-mod-mysql,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_ULOGD_MOD_MYSQL},${PKGSD_ULOGD_MOD_MYSQL},${PKG_SECTION}))
$(eval $(call PKG_template,ULOGD_MOD_PCAP,ulogd-mod-pcap,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_ULOGD_MOD_PCAP},${PKGSD_ULOGD_MOD_PCAP},${PKG_SECTION}))
$(eval $(call PKG_template,ULOGD_MOD_PGSQL,ulogd-mod-pgsql,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_ULOGD_MOD_PGSQL},${PKGSD_ULOGD_MOD_PGSQL},${PKG_SECTION}))
$(eval $(call PKG_template,ULOGD_MOD_SQLITE,ulogd-mod-sqlite,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_ULOGD_MOD_SQLITE},${PKGSD_ULOGD_MOD_SQLITE},${PKG_SECTION}))

AUTOTOOL_STYLE:=	autoreconf
TARGET_CPPFLAGS+=	-D_GNU_SOURCE
TARGET_CFLAGS+=		-fPIC

ifneq (${ADK_PACKAGE_ULOGD_MOD_MYSQL},)
CONFIGURE_ARGS+=	--with-mysql=${STAGING_TARGET_DIR}/usr
else
CONFIGURE_ARGS+=	--without-mysql
endif

ifneq (${ADK_PACKAGE_ULOGD_MOD_PGSQL},)
CONFIGURE_ARGS+=	--with-pgsql=${STAGING_TARGET_DIR}/usr
else
CONFIGURE_ARGS+=	--without-pgsql
endif

ulogd-install:
	${INSTALL_DIR} ${IDIR_ULOGD}/etc
	${INSTALL_DATA} ${WRKBUILD}/ulogd.conf ${IDIR_ULOGD}/etc
	${INSTALL_DIR} ${IDIR_ULOGD}/usr/sbin ${IDIR_ULOGD}/usr/lib/ulogd/
	${INSTALL_BIN} ${WRKINST}/usr/lib/ulogd/ulogd_raw2packet_BASE.so \
		${IDIR_ULOGD}/usr/lib/ulogd/
	${INSTALL_BIN} ${WRKINST}/usr/lib/ulogd/ulogd_filter_HWHDR.so \
		${IDIR_ULOGD}/usr/lib/ulogd/
	${INSTALL_BIN} ${WRKINST}/usr/lib/ulogd/ulogd_filter_IFINDEX.so \
		${IDIR_ULOGD}/usr/lib/ulogd/
	${INSTALL_BIN} ${WRKINST}/usr/lib/ulogd/ulogd_filter_IP2BIN.so \
		${IDIR_ULOGD}/usr/lib/ulogd/
	${INSTALL_BIN} ${WRKINST}/usr/lib/ulogd/ulogd_filter_IP2HBIN.so \
		${IDIR_ULOGD}/usr/lib/ulogd/
	${INSTALL_BIN} ${WRKINST}/usr/lib/ulogd/ulogd_filter_IP2STR.so \
		${IDIR_ULOGD}/usr/lib/ulogd/
	${INSTALL_BIN} ${WRKINST}/usr/lib/ulogd/ulogd_filter_MARK.so \
		${IDIR_ULOGD}/usr/lib/ulogd/
	${INSTALL_BIN} ${WRKINST}/usr/lib/ulogd/ulogd_filter_PRINTFLOW.so \
		${IDIR_ULOGD}/usr/lib/ulogd/
	${INSTALL_BIN} ${WRKINST}/usr/lib/ulogd/ulogd_filter_PRINTPKT.so \
		${IDIR_ULOGD}/usr/lib/ulogd/
	${INSTALL_BIN} ${WRKINST}/usr/lib/ulogd/ulogd_filter_PWSNIFF.so \
		${IDIR_ULOGD}/usr/lib/ulogd/
	${INSTALL_BIN} ${WRKINST}/usr/lib/ulogd/ulogd_inpflow_NFACCT.so \
		${IDIR_ULOGD}/usr/lib/ulogd/
	${INSTALL_BIN} ${WRKINST}/usr/lib/ulogd/ulogd_inpflow_NFCT.so \
		${IDIR_ULOGD}/usr/lib/ulogd/
	${INSTALL_BIN} ${WRKINST}/usr/lib/ulogd/ulogd_inppkt_NFLOG.so \
		${IDIR_ULOGD}/usr/lib/ulogd/
	${INSTALL_BIN} ${WRKINST}/usr/lib/ulogd/ulogd_inppkt_ULOG.so \
		${IDIR_ULOGD}/usr/lib/ulogd/
	${INSTALL_BIN} ${WRKINST}/usr/lib/ulogd/ulogd_inppkt_UNIXSOCK.so \
		${IDIR_ULOGD}/usr/lib/ulogd/
	${INSTALL_BIN} ${WRKINST}/usr/lib/ulogd/ulogd_output_GPRINT.so \
		${IDIR_ULOGD}/usr/lib/ulogd/
	${INSTALL_BIN} ${WRKINST}/usr/lib/ulogd/ulogd_output_GRAPHITE.so \
		${IDIR_ULOGD}/usr/lib/ulogd/
	${INSTALL_BIN} ${WRKINST}/usr/lib/ulogd/ulogd_output_LOGEMU.so \
		${IDIR_ULOGD}/usr/lib/ulogd/
	${INSTALL_BIN} ${WRKINST}/usr/lib/ulogd/ulogd_output_NACCT.so \
		${IDIR_ULOGD}/usr/lib/ulogd/
	${INSTALL_BIN} ${WRKINST}/usr/lib/ulogd/ulogd_output_OPRINT.so \
		${IDIR_ULOGD}/usr/lib/ulogd/
	${INSTALL_BIN} ${WRKINST}/usr/lib/ulogd/ulogd_output_SYSLOG.so \
		${IDIR_ULOGD}/usr/lib/ulogd/
	${INSTALL_BIN} ${WRKINST}/usr/lib/ulogd/ulogd_output_XML.so \
		${IDIR_ULOGD}/usr/lib/ulogd/
	${INSTALL_BIN} ${WRKINST}/usr/sbin/ulogd ${IDIR_ULOGD}/usr/sbin

ulogd-mod-pcap-install:
	${INSTALL_DIR} ${IDIR_ULOGD_MOD_PCAP}/usr/lib/ulogd
	${CP} ${WRKINST}/usr/lib/ulogd/ulogd_output_PCAP.so \
		${IDIR_ULOGD_MOD_PCAP}/usr/lib/ulogd

ulogd-mod-sqlite-install:
	${INSTALL_DIR} ${IDIR_ULOGD_MOD_SQLITE}/usr/lib/ulogd
	${CP} ${WRKINST}/usr/lib/ulogd/ulogd_output_SQLITE3.so \
		${IDIR_ULOGD_MOD_SQLITE}/usr/lib/ulogd

ulogd-mod-pgsql-install:
	${INSTALL_DIR} ${IDIR_ULOGD_MOD_PGSQL}/usr/lib/ulogd
	${CP} ${WRKINST}/usr/lib/ulogd/ulogd_output_PGSQL.so \
		${IDIR_ULOGD_MOD_PGSQL}/usr/lib/ulogd

ulogd-mod-mysql-install:
	${INSTALL_DIR} ${IDIR_ULOGD_MOD_MYSQL}/usr/lib/ulogd
	${CP} ${WRKINST}/usr/lib/ulogd/ulogd_output_MYSQL.so \
		${IDIR_ULOGD_MOD_MYSQL}/usr/lib/ulogd

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
