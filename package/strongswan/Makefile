# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		strongswan
PKG_VERSION:=		5.9.5
PKG_RELEASE:=		1
PKG_HASH:=		6db028c9033dfd7cab578ca7e4b0075922cffec7af8bffc7d67cac67f348a5be
PKG_DESCR:=		ipsec based vpn software
PKG_SECTION:=		net/security
PKG_KDEPENDS:=		net-key inet-esp xfrm-user inet-xfrm-mode-transport
PKG_KDEPENDS+=		inet-xfrm-mode-tunnel
PKG_NEEDS:=		threads
PKG_URL:=		http://strongswan.org/index.htm
PKG_SITES:=		http://download.strongswan.org/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_CHOICES_STRONGSWAN:=WITH_LIBRESSL WITH_GNUTLS WITH_GMP
PKGCD_WITH_GMP:=	use gmp for crypto
PKGCS_WITH_GMP:=	libgmp
PKGCB_WITH_GMP:=	gmp
PKGCD_WITH_LIBRESSL:=	use libressl for crypto
PKGCS_WITH_LIBRESSL:=	libressl
PKGCB_WITH_LIBRESSL:=	libressl
PKGCD_WITH_GNUTLS:=	use gnutls for crypto
PKGCS_WITH_GNUTLS:=	libgnutls
PKGCB_WITH_GNUTLS:=	gnutls

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,STRONGSWAN,strongswan,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

ifeq (${ADK_PACKAGE_STRONGSWAN_WITH_LIBRESSL},y)
CONFIGURE_ARGS+=	--enable-openssl \
			--disable-gcrypt \
			--disable-gmp
endif
ifeq (${ADK_PACKAGE_STRONGSWAN_WITH_GNUTLS},y)
CONFIGURE_ARGS+=	--enable-gcrypt \
			--disable-openssl \
			--disable-gmp
endif
ifeq (${ADK_PACKAGE_STRONGSWAN_WITH_GMP},y)
CONFIGURE_ARGS+=	--enable-gmp \
			--disable-openssl \
			--disable-gcrypt
endif

CONFIGURE_ARGS+=	--disable-tools \
			--disable-fips-prf \
			--with-group=root \
			--enable-kernel-pfkey

TARGET_LDFLAGS+=        -Wl,-rpath -Wl,/usr/lib/ipsec

strongswan-install:
	$(INSTALL_DIR) $(IDIR_STRONGSWAN)/etc
	$(INSTALL_DIR) $(IDIR_STRONGSWAN)/usr/sbin
	$(INSTALL_DIR) $(IDIR_STRONGSWAN)/usr/libexec/ipsec
	$(INSTALL_DIR) $(IDIR_STRONGSWAN)/usr/lib/ipsec/plugins
	touch $(IDIR_STRONGSWAN)/etc/ipsec.secrets
	$(CP) $(WRKINST)/usr/lib/ipsec/plugins/*.so \
		$(IDIR_STRONGSWAN)/usr/lib/ipsec/plugins
	$(CP) $(WRKINST)/etc/* $(IDIR_STRONGSWAN)/etc
	$(CP) $(WRKINST)/usr/libexec/ipsec/* \
		$(IDIR_STRONGSWAN)/usr/libexec/ipsec
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/ipsec \
		$(IDIR_STRONGSWAN)/usr/sbin
	$(CP) $(WRKINST)/usr/lib/ipsec/libvici*.so* \
		$(IDIR_STRONGSWAN)/usr/lib/ipsec/
	$(CP) $(WRKINST)/usr/lib/ipsec/libcharon*.so* \
		$(IDIR_STRONGSWAN)/usr/lib/ipsec/
	$(CP) $(WRKINST)/usr/lib/ipsec/libstrongswan*.so* \
		$(IDIR_STRONGSWAN)/usr/lib/ipsec/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
