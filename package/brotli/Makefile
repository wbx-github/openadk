# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		brotli
PKG_VERSION:=		1.2.1
PKG_RELEASE:=		1
PKG_HASH:=		98d35d11a78dc453aebb7d10c3748f3f73ff78c8267c0dc697b8631f67bf7e8f
PKG_DESCR:=		compression library
PKG_SECTION:=		libs/comp
PKG_URL:=		https://github.com/google/brotli
PKG_SITES:=		https://github.com/google/brotli/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,BROTLI,brotli,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIG_STYLE:=		cmake

brotli-install:
	$(INSTALL_DIR) $(IDIR_BROTLI)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libbrotli*.so* \
		$(IDIR_BROTLI)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
