# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		lttng-tools
PKG_VERSION:=		2.13.11
PKG_RELEASE:=		1
PKG_HASH:=		ac5baeef9fa690936b1ca01ecd1742da762c2c08511ff1b4e923938d94d0f979
PKG_DESCR:=		open source tracing framework
PKG_SECTION:=		app/debug
PKG_BUILDDEP:=		popt libxml2 util-linux userspace-rcu ncurses
PKG_DEPENDS:=		libpopt libxml2 libuuid liburcu libncurses
PKG_URL:=		http://lttng.org/
PKG_SITES:=		http://lttng.org/files/lttng-tools/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LTTNG_TOOLS,lttng-tools,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ARGS+=	--without-lttng-ust \
			--disable-tests \
			--disable-silent-rules

lttng-tools-install:
	$(INSTALL_DIR) $(IDIR_LTTNG_TOOLS)/usr/bin
	$(INSTALL_DIR) $(IDIR_LTTNG_TOOLS)/usr/lib
	$(INSTALL_BIN) $(WRKINST)/usr/bin/* \
		$(IDIR_LTTNG_TOOLS)/usr/bin
	$(CP) $(WRKINST)/usr/lib/*.so* \
		$(IDIR_LTTNG_TOOLS)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
