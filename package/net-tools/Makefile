# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		net-tools
PKG_VERSION:=		1.60
PKG_RELEASE:=		2
PKG_HASH:=		7ae4dd6d44d6715f18e10559ffd270511b6e55a8900ca54fbebafe0ae6cf7d7b
PKG_DESCR:=		arp networking tool
PKG_SECTION:=		net/misc
PKG_URL:=		http://net-tools.sourceforge.net/
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=net-tools/}
PKG_NOPARALLEL:=	1

PKG_SUBPKGS:=		ARP

DISTFILES:=             ${PKG_NAME}-${PKG_VERSION}.tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,ARP,arp,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
INSTALL_STYLE:=		manual

do-configure:
	$(CP) ./files/config.* $(WRKBUILD)/

arp-install:
	$(INSTALL_DIR) $(IDIR_ARP)/sbin
	$(INSTALL_BIN) $(WRKBUILD)/arp \
		$(IDIR_ARP)/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
