# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		nim
PKG_VERSION:=		2.4.2
PKG_RELEASE:=		1
PKG_HASH:=		b28bf4da1fce46dba9d16685c981b3d5e98de8db1b60d66f279b0bd2af2d8211
PKG_DESCR:=		nim programming language
PKG_SECTION:=		dev/lang
PKG_URL:=		https://nim-lang.org/
PKG_SITES:=		https://github.com/nim-lang/nightlies/releases/download/2026-11-13-version-2-4-b27dcb4f70883978e984e427cc24b64eeb7c875f/

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
