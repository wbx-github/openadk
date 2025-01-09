# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		net-snmp
PKG_VERSION:=		5.8
PKG_RELEASE:=		1
PKG_HASH:=		b2fc3500840ebe532734c4786b0da4ef0a5f67e51ef4c86b3345d697e4976adf
PKG_DESCR:=		snmp agent
PKG_SECTION:=		net/misc
PKG_DEPENDS:=		libnetsnmp elfutils libnl
PKG_BUILDDEP:=		elfutils libnl
PKG_URL:=		http://www.net-snmp.org/
PKG_SITES:=		$(MASTER_SITE_SOURCEFORGE:=net-snmp/)
PKG_NOPARALLEL:=	1
PKG_LIBNAME:=		libnetsnmp
PKG_OPTS:=		dev

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_SUBPKGS:=		SNMPD SNMP_UTILS LIBNETSNMP
PKGSD_SNMP_UTILS:=	snmp utilities
PKGSS_SNMP_UTILS:=	libnetsnmp elfutils
PKGSD_LIBNETSNMP:=	snmp library
PKGSS_LIBNETSNMP:=	elfutils
PKGSC_LIBNETSNMP:=	libs/net

PKG_FLAVOURS_SNMPD:=	WITH_IPV6
PKGFD_WITH_IPV6:=	enable ipv6 support

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,SNMPD,snmpd,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))
$(eval $(call PKG_template,SNMP_UTILS,snmp-utils,$(PKG_VERSION)-$(PKG_RELEASE),$(PKGSS_SNMP_UTILS),$(PKGSD_SNMP_UTILS),$(PKG_SECTION)))
$(eval $(call PKG_template,LIBNETSNMP,libnetsnmp,$(PKG_VERSION)-$(PKG_RELEASE),$(PKGSS_LIBNETSNMP),$(PKGSD_LIBNETSNMP),$(PKGSC_LIBNETSNMP),$(PKG_OPTS)))

SNMP_TRANSPORTS_INCLUDED:=	UDP TCP Callback Unix
SNMP_TRANSPORTS_EXCLUDED:=	Alias
ifneq ($(ADK_PACKAGE_SNMPD_WITH_IPV6),)
SNMP_TRANSPORTS_INCLUDED+=	TCPIPv6 UDPIPv6
else
SNMP_TRANSPORTS_EXCLUDED:=	TCPIPv6 UDPIPv6
endif

TARGET_LDFLAGS+=	-pthread
CONFIGURE_ARGS+=	--with-defaults \
			--with-persistent-directory=/etc/snmp \
			--with-default-snmp-version=3 \
			--with-sys-contact=root@localhost \
			--with-sys-location=Unknown \
			--enable-applications \
			--disable-embedded-perl \
			--without-perl-modules \
			--disable-debugging \
			--disable-manuals \
			--disable-mib-loading \
			--disable-mibs \
			--disable-scripts \
			--with-transports="$(SNMP_TRANSPORTS_INCLUDED)" \
			--with-out-transports="$(SNMP_TRANSPORTS_EXCLUDED)" \
			--with-opaque-special-types \
			--without-openssl \
			--without-libwrap \
			--without-rpm \
			--without-zlib

ifneq ($(ADK_PACKAGE_SNMPD_WITH_IPV6),)
CONFIGURE_ARGS+=	--enable-ipv6
else
CONFIGURE_ARGS+=	--disable-ipv6
endif

FAKE_FLAGS+=		INSTALL_PREFIX="$(WRKINST)"

libnetsnmp-install:
	$(INSTALL_DIR) $(IDIR_LIBNETSNMP)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libnetsnmp*.so* $(IDIR_LIBNETSNMP)/usr/lib/

snmpd-install:
	$(INSTALL_DIR) $(IDIR_SNMPD)/etc/snmp
	$(INSTALL_DIR) $(IDIR_SNMPD)/usr/sbin
	$(INSTALL_DATA) ./files/snmpd.conf $(IDIR_SNMPD)/etc/snmp/snmpd.conf
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/snmpd $(IDIR_SNMPD)/usr/sbin/snmpd

snmp-utils-install:
	$(INSTALL_DIR) $(IDIR_SNMP_UTILS)/usr/bin
	$(CP) $(WRKINST)/usr/bin/snmp{get,set,status,test,trap,walk} \
		$(IDIR_SNMP_UTILS)/usr/bin/

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
