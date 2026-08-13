# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		nim
PKG_VERSION:=		2.2.10
PKG_RELEASE:=		1
PKG_HASH:=		7957b7ed004206bcf10bcc4f3b4744153878e62f2431552a9a8e9d3f40e8d5d5
PKG_DESCR:=		nim programming language
PKG_SECTION:=		dev/lang
PKG_URL:=		https://nim-lang.org/
PKG_SITES:=		https://github.com/nim-lang/nightlies/releases/download/2026-04-24-version-2-2-bfeb3146d1638b39f69007a4ae5a23e23ae4e5ef/

PKG_CFLINE_NIM:=	depends on ADK_HOST_ONLY

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,NIM,nim,$(PKG_VERSION)-$(PKG_RELEASE)))
$(eval $(call PKG_template,NIM,nim,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

HOST_STYLE:=		manual

host-build:
	(cd $(WRKBUILD) && ./build.sh)

nim-hostinstall:
	$(INSTALL_BIN) $(WRKBUILD)/bin/nim $(STAGING_HOST_DIR)/usr/bin
	$(CP) $(WRKBUILD)/lib/* $(STAGING_HOST_DIR)/usr/lib

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
