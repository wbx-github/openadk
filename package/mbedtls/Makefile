# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		mbedtls
PKG_VERSION:=		2.28.7
PKG_RELEASE:=		1
PKG_HASH:=		1df6073f0cf6a4e1953890bf5e0de2a8c7e6be50d6d6c69fa9fefcb1d14e981a
PKG_DESCR:=		embedded ssl/tls library
PKG_SECTION:=		libs/crypto
PKG_URL:=		https://tls.mbed.org
PKG_SITES:=		https://github.com/Mbed-TLS/mbedtls/archive/refs/tags/
PKG_LIBNAME:=		libmbedtls
PKG_OPTS:=		dev

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBMBEDTLS,libmbedtls,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIG_STYLE:=		manual
ALL_TARGET:=		lib
TARGET_CFLAGS+=		-DSHARED

libmbedtls-install:
	$(INSTALL_DIR) $(IDIR_LIBMBEDTLS)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
