# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		jq
PKG_VERSION:=		1.8.2
PKG_RELEASE:=		1
PKG_HASH:=		71b8d6e8f5fe81f6c6d0d110e3892251f6ce76ed095abd315e26e6e1193af3af
PKG_DESCR:=		command-line json processor
PKG_SECTION:=		sys/misc
PKG_URL:=		http://stedolan.github.io/jq/
PKG_SITES:=		https://github.com/stedolan/jq/releases/download/jq-$(PKG_VERSION)/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,JQ,jq,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

jq-install:
	$(INSTALL_DIR) $(IDIR_JQ)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libjq.so* \
		$(IDIR_JQ)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libonig.so* \
		$(IDIR_JQ)/usr/lib
	$(INSTALL_DIR) $(IDIR_JQ)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/jq \
		$(IDIR_JQ)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
