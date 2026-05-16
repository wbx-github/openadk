# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		p11-kit
PKG_VERSION:=		0.26.2
PKG_RELEASE:=		1
PKG_HASH:=		09fd9f44da4813a3141e73d5e7cf7008e5660d0405f13d56c15e1da9dcecf828
PKG_DESCR:=		pkcs11 library
PKG_SECTION:=		libs/crypto
PKG_DEPENDS:=		libtasn1
PKG_BUILDDEP:=		libtasn1
PKG_URL:=		https://p11-glue.freedesktop.org/p11-kit.html
PKG_SITES:=		https://github.com/p11-glue/p11-kit/releases/download/0.26.2/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,P11_KIT,p11-kit,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIGURE_ARGS+=	--disable-static

p11-kit-install:
	$(INSTALL_DIR) $(IDIR_P11_KIT)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libp11-kit*.so* \
		$(IDIR_P11_KIT)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
