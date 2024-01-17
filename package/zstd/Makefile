# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		zstd
PKG_VERSION:=		1.5.5
PKG_RELEASE:=		1
PKG_HASH:=		98e9c3d949d1b924e28e01eccb7deed865eefebf25c2f21c702e5cd5b63b85e1
PKG_DESCR:=		zstandard compression application
PKG_SECTION:=		app/archive
PKG_SITES:=		https://github.com/facebook/zstd/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=             v$(PKG_VERSION).tar.gz

include ${ADK_TOPDIR}/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,ZSTD,zstd,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,ZSTD,zstd,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

HOST_CONFIG_STYLE:=	manual
HOST_INSTALL_STYLE:=	auto
CONFIG_STYLE:=		manual
ALL_TARGET:=		default
HOST_ALL_TARGET:=	default

zstd-install:
	$(INSTALL_DIR) $(IDIR_ZSTD)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libzstd*.so* \
		$(IDIR_ZSTD)/usr/lib
	$(INSTALL_DIR) $(IDIR_ZSTD)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/zstd \
		$(IDIR_ZSTD)/usr/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
