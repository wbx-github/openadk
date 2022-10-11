# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libevent
PKG_VERSION:=		2.1.12
PKG_RELEASE:=		1
PKG_HASH:=		92e6de1be9ec176428fd2367677e61ceffc2ee1cb119035037a27d346b0403bb
PKG_DESCR:=		event notification library for event-driven network servers
PKG_SECTION:=		libs/net
PKG_URL:=		http://libevent.org/
PKG_SITES:=		https://github.com/libevent/libevent/releases/download/release-$(PKG_VERSION)-stable/
PKG_OPTS:=		dev

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION)-stable.tar.gz
WRKDIST=		$(WRKDIR)/$(PKG_NAME)-$(PKG_VERSION)-stable

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBEVENT,libevent,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

ifeq ($(ADK_TARGET_USE_STATIC_LIBS_ONLY),y)
MAKE_FLAGS+=		LDFLAGS="$(TARGET_LDFLAGS) -all-static"
endif

CONFIGURE_ARGS+=	--disable-openssl

libevent-install:
	$(INSTALL_DIR) $(IDIR_LIBEVENT)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libevent*.so* $(IDIR_LIBEVENT)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
