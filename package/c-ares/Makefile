# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		c-ares
PKG_VERSION:=		1.16.1
PKG_RELEASE:=		1
PKG_HASH:=		d08312d0ecc3bd48eee0a4cc0d2137c9f194e0a28de2028928c0f6cae85f86ce
PKG_DESCR:=		asynchronous dns library
PKG_SECTION:=		libs/net
PKG_URL:=		http://c-ares.haxx.se
PKG_SITES:=		http://c-ares.haxx.se/download/
PKG_OPTS:=		dev

DISTFILES:=             ${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,C_ARES,c-ares,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

c-ares-install:
	$(INSTALL_DIR) $(IDIR_C_ARES)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libcares*.so* \
		$(IDIR_C_ARES)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
