# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		iperf3
PKG_VERSION:=		3.21
PKG_RELEASE:=		1
PKG_HASH:=		656e4405ebd620121de7ceca3eaf43a88f79ea1b857d041a6a0b1314801acdd8
PKG_DESCR:=		internet protocol bandwidth measuring tool
PKG_SECTION:=		net/perf
PKG_DEPENDS:=		libopenssl
PKG_BUILDDEP:=		openssl
PKG_URL:=		http://iperf.fr
PKG_SITES:=		https://downloads.es.net/pub/iperf/

DISTFILES:=		iperf-$(PKG_VERSION).tar.gz
WRKDIST=		$(WRKDIR)/iperf-$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,IPERF3,iperf3,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

iperf3-install:
	$(INSTALL_DIR) $(IDIR_IPERF3)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libiperf*so.* \
		$(IDIR_IPERF3)/usr/lib
	$(INSTALL_DIR) $(IDIR_IPERF3)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/iperf3 \
		$(IDIR_IPERF3)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
