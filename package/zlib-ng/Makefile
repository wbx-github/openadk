# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		zlib-ng
PKG_VERSION:=		2.1.6
PKG_RELEASE:=		1
PKG_HASH:=		a5d504c0d52e2e2721e7e7d86988dec2e290d723ced2307145dedd06aeb6fef2
PKG_DESCR:=		implementation of the deflate compression method
PKG_SECTION:=		libs/comp
PKG_SITES:=		https://github.com/zlib-ng/zlib-ng/archive/refs/tags/
PKG_NEEDS:=		c++
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,ZLIB_NG,zlib-ng,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIG_STYLE:=		cmake

zlib-ng-install:
	$(INSTALL_DIR) $(IDIR_ZLIB_NG)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libz-ng*.so* \
		$(IDIR_ZLIB_NG)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
