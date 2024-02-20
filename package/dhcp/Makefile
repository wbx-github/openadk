# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		dhcp
PKG_VERSION:=		4.4.3-P1
PKG_RELEASE:=		1
PKG_HASH:=		0ac416bb55997ca8632174fd10737fd61cdb8dba2752160a335775bc21dc73c7
PKG_DESCR:=		dhcp server
PKG_SECTION:=		net/dns
PKG_URL:=		https://www.isc.org/software/dhcp/
PKG_SITES:=		https://downloads.isc.org/isc/dhcp/$(PKG_VERSION)/
PKG_NOPARALLEL:=	1

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_SUBPKGS:=		DHCP_SERVER DHCP_RELAY
PKGSD_DHCP_RELAY:=	dhcp relay server

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,DHCP_SERVER,dhcp-server,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,DHCP_RELAY,dhcp-relay,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_DHCP_RELAY},${PKG_SECTION}))

MAKE_ENV+=		BUILD_CC="$(HOST_CC)" \
			BUILD_CFLAGS="$(HOST_CFLAGS)" \
			BUILD_CPPFLAGS="$(HOST_CPPFLAGS)" \
			BUILD_LDFLAGS="$(HOST_LDFLAGS)"

CONFIGURE_ARGS+=	--with-randomdev=/dev/random
			--with-srv-lease-file=/var/lib/dhcp/dhcpd.leases \
			--with-srv6-lease-file=/var/lib/dhcp/dhcpd6.leases \
			--with-cli-lease-file=/var/lib/dhcp/dhclient.leases \
			--with-cli6-lease-file=/var/lib/dhcp/dhclient6.leases \
			--with-srv-pid-file=/var/run/dhcpd.pid \
			--with-srv6-pid-file=/var/run/dhcpd6.pid \
			--with-cli-pid-file=/var/run/dhclient.pid \
			--with-cli6-pid-file=/var/run/dhclient6.pid \
			--with-relay-pid-file=/var/run/dhcrelay.pid \
			--with-relay6-pid-file=/var/run/dhcrelay6.pid

post-extract:
	cd $(WRKBUILD)/bind; tar -xvf bind.tar.gz

dhcp-relay-install:
	${INSTALL_DIR} ${IDIR_DHCP_RELAY}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/usr/sbin/dhcrelay \
		${IDIR_DHCP_RELAY}/usr/sbin/

dhcp-server-install:
	${INSTALL_DIR} ${IDIR_DHCP_SERVER}/usr/sbin
	${INSTALL_DIR} ${IDIR_DHCP_SERVER}/etc
	${INSTALL_DATA} ./files/dhcpd.conf ${IDIR_DHCP_SERVER}/etc
	${INSTALL_BIN} ${WRKINST}/usr/sbin/dhcpd \
		${IDIR_DHCP_SERVER}/usr/sbin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
