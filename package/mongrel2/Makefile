# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		mongrel2
PKG_VERSION:=		1.13.0
PKG_RELEASE:=		1
PKG_HASH:=		b6f1f50c9f65b605342d8792b1cc8a1c151105339030313b9825b6a68d400c10
PKG_DESCR:=		application, language, and network architecture agnostic web server
PKG_SECTION:=		net/http
PKG_BUILDDEP:=		zeromq sqlite-host sqlite mbedtls
PKG_DEPENDS:=		zeromq libsqlite mbedtls
PKG_NEEDS:=		threads c++
PKG_URL:=		http://mongrel2.org
PKG_SITES:=		https://github.com/mongrel2/mongrel2/releases/download/v$(PKG_VERSION)/

DISTFILES:=             $(PKG_NAME)-v$(PKG_VERSION).tar.bz2
WRKDIST=		${WRKDIR}/$(PKG_NAME)-v$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,MONGREL2,mongrel2,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		manual

mongrel2-install:
	$(INSTALL_DIR) $(IDIR_MONGREL2)/etc/mongrel2
	$(CP) $(WRKBUILD)/examples/configs/sample.conf \
		$(IDIR_MONGREL2)/etc/mongrel2/site.conf
	$(INSTALL_DIR) $(IDIR_MONGREL2)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/m2sh \
		$(IDIR_MONGREL2)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/mongrel2 \
		$(IDIR_MONGREL2)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
