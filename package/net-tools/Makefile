# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		net-tools
PKG_VERSION:=		2.10
PKG_RELEASE:=		1
PKG_HASH:=		b262435a5241e89bfa51c3cabd5133753952f7a7b7b93f32e08cb9d96f580d69
PKG_DESCR:=		networking tools
PKG_SECTION:=		net/misc
PKG_URL:=		http://net-tools.sourceforge.net/
PKG_SITES:=		https://sourceforge.net/projects/net-tools/files/
PKG_NOPARALLEL:=	1

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,NET_TOOLS,net-tools,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
INSTALL_STYLE:=		manual

do-configure:
	$(CP) ./files/config.* $(WRKBUILD)/

net-tools-install:
	$(INSTALL_DIR) $(IDIR_NET_TOOLS)/sbin
	$(INSTALL_BIN) $(WRKBUILD)/{arp,ifconfig,route,hostname} \
		$(IDIR_NET_TOOLS)/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
