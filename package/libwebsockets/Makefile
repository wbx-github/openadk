# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libwebsockets
PKG_VERSION:=		4.3.3
PKG_RELEASE:=		1
PKG_HASH:=		6fd33527b410a37ebc91bb64ca51bdabab12b076bc99d153d7c5dd405e4bdf90
PKG_DESCR:=		lightweight network library
PKG_SECTION:=		libs/net
PKG_BUILDDEP:=		cmake-host zlib libressl
PKG_DEPENDS:=		zlib libressl
PKG_URL:=		https://libwebsockets.org/
PKG_SITES:=		https://github.com/warmcat/libwebsockets/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBWEBSOCKETS,libwebsockets,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIG_STYLE:=		cmake

libwebsockets-install:
	$(INSTALL_DIR) $(IDIR_LIBWEBSOCKETS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libwebsockets*.so* \
		$(IDIR_LIBWEBSOCKETS)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
