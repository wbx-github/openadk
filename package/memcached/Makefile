# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		memcached
PKG_VERSION:=		1.6.42
PKG_RELEASE:=		1
PKG_HASH:=		50f08b879d4f9d36dea9d905e9eaade15c708e38db7e9a73fc21dc8b45395de7
PKG_DESCR:=		high-performance distributed memory caching system
PKG_SECTION:=		net/misc
PKG_DEPENDS:=		libevent
PKG_BUILDDEP:=		libevent
PKG_URL:=		https://memcached.org/
PKG_SITES:=		https://www.memcached.org/files/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,MEMCACHED,memcached,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ARGS+=	--disable-coverage --disable-werror

memcached-install:
	$(INSTALL_DIR) $(IDIR_MEMCACHED)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/memcached \
		$(IDIR_MEMCACHED)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
