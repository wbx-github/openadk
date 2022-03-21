# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		openvpn
PKG_VERSION:=		2.5.6
PKG_RELEASE:=		1
PKG_HASH:=		333a7ef3d5b317968aca2c77bdc29aa7c6d6bb3316eb3f79743b59c53242ad3d
PKG_DESCR:=		vpn solution using ssl/tls
PKG_DEPENDS:=		libressl
PKG_BUILDDEP:=		libressl
PKG_KDEPENDS:=		tun
PKG_SECTION:=		net/security
PKG_URL:=		http://openvpn.net/
PKG_SITES:=		http://swupdate.openvpn.org/community/releases/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_FLAVOURS_OPENVPN:=	WITH_LZO WITH_LZ4 WITH_MANAGEMENT WITH_SMALL
PKGFD_WITH_LZO:=	enable lzo compression support
PKGFS_WITH_LZO:=	liblzo
PKGFB_WITH_LZO:=	liblzo
PKGFD_WITH_LZ4:=	enable lz4 compression support
PKGFS_WITH_LZ4:=	liblz4
PKGFB_WITH_LZ4:=	lz4
PKGFD_WITH_MANAGEMENT:=	enable management server support
PKGFD_WITH_SMALL:=	enable extra small binary

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,OPENVPN,openvpn,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ENV+=		ac_cv_lib_nsl_inet_ntoa=no

ifneq ($(ADK_PACKAGE_OPENVPN_WITH_LZ4),)
CONFIGURE_ARGS+=	--enable-lz4
else
CONFIGURE_ARGS+=	--disable-lz4
endif

ifneq ($(ADK_PACKAGE_OPENVPN_WITH_LZO),)
CONFIGURE_ARGS+=	--enable-lzo
else
CONFIGURE_ARGS+=	--disable-lzo
endif

ifneq ($(ADK_PACKAGE_OPENVPN_WITH_MANAGEMENT),)
CONFIGURE_ARGS+=	--enable-management
else
CONFIGURE_ARGS+=	--disable-management
endif

ifneq ($(ADK_PACKAGE_OPENVPN_WITH_SMALL),)
CONFIGURE_ARGS+=	--enable-small
endif

ifeq ($(ADK_DEBUG),y)
CONFIGURE_ARGS+=	--enable-debug
else
CONFIGURE_ARGS+=	--disable-debug
endif

CONFIGURE_ARGS+=	--disable-plugins \
			--with-crypto-library=openssl \
			--enable-iproute2

openvpn-install:
	${INSTALL_DIR} $(IDIR_OPENVPN)/usr/sbin $(IDIR_OPENVPN)/etc/openvpn
	${INSTALL_BIN} $(WRKINST)/usr/sbin/openvpn $(IDIR_OPENVPN)/usr/sbin/
	$(CP) ./files/server.conf $(IDIR_OPENVPN)/etc/openvpn/server.conf.example
	$(CP) ./files/client.conf $(IDIR_OPENVPN)/etc/openvpn/client.conf.example

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
