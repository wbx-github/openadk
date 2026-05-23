# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		netcat
PKG_VERSION:=		0.7.1
PKG_RELEASE:=		1
PKG_HASH:=		30719c9a4ffbcf15676b8f528233ccc54ee6cba96cb4590975f5fd60c68a066f
PKG_DESCR:=		network swiss army knife
PKG_SECTION:=		net/misc
PKG_URL:=		http://netcat.sourceforge.net/
PKG_SITES:=		https://sourceforge.net/projects/netcat/files/netcat/$(PKG_VERSION)/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,NETCAT,netcat,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

netcat-install:
	$(INSTALL_DIR) $(IDIR_NETCAT)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/netcat \
		$(IDIR_NETCAT)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
