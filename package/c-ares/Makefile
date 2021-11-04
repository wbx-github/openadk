# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		c-ares
PKG_VERSION:=		1.18.1
PKG_RELEASE:=		1
PKG_HASH:=		1a7d52a8a84a9fbffb1be9133c0f6e17217d91ea5a6fa61f6b4729cda78ebbcf
PKG_DESCR:=		asynchronous dns library
PKG_SECTION:=		libs/net
PKG_URL:=		https://c-ares.org
PKG_SITES:=		https://c-ares.org/download/
PKG_OPTS:=		dev

DISTFILES:=             ${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,C_ARES,c-ares,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

c-ares-install:
	$(INSTALL_DIR) $(IDIR_C_ARES)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libcares*.so* \
		$(IDIR_C_ARES)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
