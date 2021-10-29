# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		bind
PKG_VERSION:=		9.16.22
PKG_RELEASE:=		1
PKG_HASH:=		65e7b2af6479db346e2fc99bcfb6ec3240066468e09dbec575ebc7c57d994061
PKG_DESCR:=		dns server
PKG_SECTION:=		net/dns
PKG_DEPENDS:=		libxml2 libressl libuv libressl-util
PKG_BUILDDEP:=		libxml2 libressl libuv
PKG_NEEDS:=		c++
PKG_URL:=		https://www.isc.org/software/bind/
PKG_SITES:=		ftp://ftp.isc.org/isc/bind9/${PKG_VERSION}/
PKG_LIBNAME:=		libbind
PKG_OPTS:=		dev

PKG_SUBPKGS:=		LIBBIND BIND_SERVER BIND_NSUPDATE BIND_RNDC BIND_CHECK BIND_DNSSEC BIND_HOST BIND_DIG
PKGSD_LIBBIND:=		library for the bind software suite
PKGSC_LIBBIND:=		libs/net
PKGSD_BIND_SERVER:=	dns server
PKGSC_BIND_SERVER:=	net/dns
PKGSS_BIND_SERVER:=	libbind libxml2
PKGSD_BIND_NSUPDATE:=	nsupdate utility
PKGSC_BIND_NSUPDATE:=	net/dns
PKGSS_BIND_NSUPDATE:=	libbind libxml2
PKGSD_BIND_RNDC:=	rndc & rndc-confgen utilities
PKGSC_BIND_RNDC:=	net/dns
PKGSS_BIND_RNDC:=	libbind libxml2
PKGSD_BIND_CHECK:=	check utilities
PKGSC_BIND_CHECK:=	net/dns
PKGSS_BIND_CHECK:=	libbind libxml2
PKGSD_BIND_DNSSEC:=	dnssec utilities
PKGSC_BIND_DNSSEC:=	net/dns
PKGSS_BIND_DNSSEC:=	libbind libxml2
PKGSD_BIND_HOST:=	host utility
PKGSC_BIND_HOST:=	net/dns
PKGSS_BIND_HOST:=	libbind libxml2
PKGSD_BIND_DIG:=	dig utility
PKGSC_BIND_DIG:=	net/dns
PKGSS_BIND_DIG:=	libbind libxml2

PKG_FLAVOURS_LIBBIND:=	WITH_IPV6
PKGFD_WITH_IPV6:=	enable IPv6 support

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,BIND_SERVER,bind-server,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,BIND_NSUPDATE,bind-nsupdate,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_BIND_NSUPDATE},${PKGSD_BIND_NSUPDATE},${PKGSC_BIND_NSUPDATE}))
$(eval $(call PKG_template,BIND_RNDC,bind-rndc,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_BIND_RNDC},${PKGSD_BIND_RNDC},${PKGSC_BIND_RNDC}))
$(eval $(call PKG_template,BIND_CHECK,bind-check,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_BIND_CHECK},${PKGSD_BIND_CHECK},${PKGSC_BIND_CHECK}))
$(eval $(call PKG_template,BIND_DNSSEC,bind-dnssec,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_BIND_DNSSEC},${PKGSD_BIND_DNSSEC},${PKGSC_BIND_DNSSEC}))
$(eval $(call PKG_template,BIND_HOST,bind-host,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_BIND_HOST},${PKGSD_BIND_HOST},${PKGSC_BIND_HOST}))
$(eval $(call PKG_template,BIND_DIG,bind-dig,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_BIND_DIG},${PKGSD_BIND_DIG},${PKGSC_BIND_DIG}))
$(eval $(call PKG_template,LIBBIND,libbind,${PKG_VERSION}-${PKG_RELEASE},,${PKGSD_LIBBIND},${PKGSC_LIBBIND},${PKG_OPTS}))

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ENV+=		BUILD_CC="${HOST_CC}" BUILD_CFLAGS='${HOST_CFLAGS}' BUILD_LDFLAGS='${HOST_LDFLAGS}'
CONFIGURE_ARGS+=	--with-randomdev=/dev/urandom \
			--with-export-libdir=/usr/lib \
			--enable-exportlib \
			--with-ecdsa=no \
			--with-gost=no \
			--with-gssapi=no \
			--with-openssl=${STAGING_TARGET_DIR}/usr \
			--without-python \
			--disable-linux-caps \
			--enable-epoll \
			--with-libtool

ifneq (${ADK_PACKAGE_LIBBIND_WITH_IPV6},)
CONFIGURE_ARGS+=	--enable-ipv6
else
CONFIGURE_ARGS+=	--disable-ipv6
endif

bind-server-install:
	${INSTALL_DIR} ${IDIR_BIND_SERVER}/usr/sbin ${IDIR_BIND_SERVER}/etc
	${INSTALL_BIN} ${WRKINST}/usr/sbin/named ${IDIR_BIND_SERVER}/usr/sbin
	${CP} ./files/bind ${IDIR_BIND_SERVER}/etc

bind-nsupdate-install:
	${INSTALL_DIR} ${IDIR_BIND_NSUPDATE}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/nsupdate ${IDIR_BIND_NSUPDATE}/usr/bin

bind-rndc-install:
	${INSTALL_DIR} ${IDIR_BIND_RNDC}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/usr/sbin/rndc ${IDIR_BIND_RNDC}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/usr/sbin/rndc-confgen \
		${IDIR_BIND_RNDC}/usr/sbin

bind-check-install:
	${INSTALL_DIR} ${IDIR_BIND_CHECK}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/usr/sbin/named-checkconf \
		${IDIR_BIND_CHECK}/usr/sbin/
	${INSTALL_BIN} ${WRKINST}/usr/sbin/named-checkzone \
		${IDIR_BIND_CHECK}/usr/sbin/

bind-dnssec-install:
	${INSTALL_DIR} ${IDIR_BIND_DNSSEC}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/usr/sbin/dnssec-keygen \
		${IDIR_BIND_DNSSEC}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/usr/sbin/dnssec-signzone \
		${IDIR_BIND_DNSSEC}/usr/sbin

bind-host-install:
	${INSTALL_DIR} ${IDIR_BIND_HOST}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/host ${IDIR_BIND_HOST}/usr/bin

bind-dig-install:
	${INSTALL_DIR} ${IDIR_BIND_DIG}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/dig ${IDIR_BIND_DIG}/usr/bin

libbind-install:
	${INSTALL_DIR} ${IDIR_LIBBIND}/usr/lib
	${CP} ${WRKINST}/usr/lib/libbind9*.so ${IDIR_LIBBIND}/usr/lib
	${CP} ${WRKINST}/usr/lib/libdns*.so ${IDIR_LIBBIND}/usr/lib
	${CP} ${WRKINST}/usr/lib/libisccc*.so ${IDIR_LIBBIND}/usr/lib
	${CP} ${WRKINST}/usr/lib/libisccfg*.so ${IDIR_LIBBIND}/usr/lib
	${CP} ${WRKINST}/usr/lib/libisc*.so ${IDIR_LIBBIND}/usr/lib
	${CP} ${WRKINST}/usr/lib/libirs*.so ${IDIR_LIBBIND}/usr/lib
	${CP} ${WRKINST}/usr/lib/libns*.so ${IDIR_LIBBIND}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
