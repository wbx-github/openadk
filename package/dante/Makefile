# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		dante
PKG_VERSION:=		1.4.4
PKG_RELEASE:=		1
PKG_HASH:=		1973c7732f1f9f0a4c0ccf2c1ce462c7c25060b25643ea90f9b98f53a813faec
PKG_DESCR:=		socks proxy
PKG_SECTION:=		net/proxy
PKG_URL:=		https://www.inet.no/dante/
PKG_SITES:=		https://www.inet.no/dante/files/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,DANTE,dante,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

dante-install:
	$(INSTALL_DIR) $(IDIR_DANTE)/etc
	$(CP) $(WRKSRC)/example/sockd.conf \
		$(IDIR_DANTE)/etc
	$(INSTALL_DIR) $(IDIR_DANTE)/usr/lib
	$(CP) $(WRKINST)/usr/lib/lib*.so* \
		$(IDIR_DANTE)/usr/lib
	$(INSTALL_DIR) $(IDIR_DANTE)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/sockd \
		$(IDIR_DANTE)/usr/sbin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
