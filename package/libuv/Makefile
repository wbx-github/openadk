# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libuv
PKG_VERSION:=		1.50.0
PKG_RELEASE:=		1
PKG_HASH:=		b1ec56444ee3f1e10c8bd3eed16ba47016ed0b94fe42137435aaf2e0bd574579
PKG_DESCR:=		multi-platform support library
PKG_SECTION:=		libs/misc
PKG_URL:=		https://github.com/libuv/libuv/
PKG_SITES:=		https://github.com/libuv/libuv/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBUV,libuv,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIG_STYLE:=		cmake

libuv-install:
	$(INSTALL_DIR) $(IDIR_LIBUV)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libuv*.so* \
		$(IDIR_LIBUV)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
