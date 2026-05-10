# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		easy-rsa
PKG_VERSION:=		3.0.3
PKG_RELEASE:=		1
PKG_HASH:=		3e41c0dfebe04332cdc07f13bf48a69e25dfc31d059e94071a9cfb9f3bba6f9a
PKG_DESCR:=		x509 ca scripts
PKG_SECTION:=		app/crypto
PKG_DEPENDS:=		openssl-util
PKG_URL:=		https://github.com/OpenVPN/easy-rsa
PKG_SITES:=		https://github.com/OpenVPN/easy-rsa/archive/

PKG_CFLINE_EASY_RSA:=	depends on ADK_BROKEN

DISTFILES:=		v${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,EASY_RSA,easy-rsa,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

easy-rsa-install:
	${INSTALL_DIR} $(IDIR_EASY_RSA)/usr/sbin
	$(CP) $(WRKBUILD)/easyrsa3/openssl-1.0.cnf \
		$(IDIR_EASY_RSA)/usr/sbin
	$(CP) $(WRKBUILD)/easyrsa3/easyrsa \
		$(IDIR_EASY_RSA)/usr/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
