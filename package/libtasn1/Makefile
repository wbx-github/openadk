# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libtasn1
PKG_VERSION:=		4.19.0
PKG_RELEASE:=		1
PKG_HASH:=		1613f0ac1cf484d6ec0ce3b8c06d56263cc7242f1c23b30d82d23de345a63f7a
PKG_DESCR:=		asn.1 and der structures manipulation library
PKG_SECTION:=		libs/crypto
PKG_URL:=		http://www.gnupg.org/
PKG_SITES:=		$(MASTER_SITE_GNU:=libtasn1/)
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBTASN1,libtasn1,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIGURE_ARGS+=	--disable-gtk-doc-html \
			--disable-gcc-warnings

libtasn1-install:
	$(INSTALL_DIR) $(IDIR_LIBTASN1)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libtasn1.so* $(IDIR_LIBTASN1)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
