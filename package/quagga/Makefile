# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		quagga
PKG_VERSION:=		1.2.4
PKG_RELEASE:=		1
PKG_HASH:=		e364c082c3309910e1eb7b068bf39ee298e2f2f3f31a6431a5c115193bd653d3
PKG_DESCR:=		routing software package
PKG_SECTION:=		net/route
PKG_BUILDDEP:=		readline ncurses c-ares
PKG_DEPENDS:=		c-ares
PKG_NEEDS:=		threads
PKG_URL:=		http://www.quagga.net/
PKG_SITES:=		https://github.com/Quagga/quagga/releases/download/$(PKG_NAME)-$(PKG_VERSION)/

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_SUBPKGS:=		QUAGGA QUAGGA_BGPD QUAGGA_OSPFD QUAGGA_OSPF6D
PKG_SUBPKGS+=		QUAGGA_RIPNGD QUAGGA_RIPD QUAGGA_VTYSH
PKGSD_QUAGGA_BGPD:=	bgp daemon
PKGSN_QUAGGA_BGPD:=	quagga
PKGSD_QUAGGA_OSPFD:=	ospf daemon
PKGSN_QUAGGA_OSPFD:=	quagga
PKGSD_QUAGGA_OSPF6D:=	ospf ipv6 daemon
PKGSN_QUAGGA_OSPF6D:=	quagga
PKGSD_QUAGGA_RIPNGD:=	ripng daemon
PKGSN_QUAGGA_RIPNGD:=	quagga
PKGSD_QUAGGA_RIPD:=	rip daemon
PKGSN_QUAGGA_RIPD:=	quagga
PKGSD_QUAGGA_VTYSH:=	vtysh utility
PKGSN_QUAGGA_VTYSH:=	quagga

PKG_CFLINE_QUAGGA:=	select BUSYBOX_PIDOF

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,QUAGGA,quagga,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))
$(eval $(call PKG_template,QUAGGA_BGPD,quagga-bgpd,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKGSD_QUAGGA_BGPD),$(PKG_SECTION)))
$(eval $(call PKG_template,QUAGGA_OSPFD,quagga-ospfd,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKGSD_QUAGGA_OSPFD),$(PKG_SECTION)))
$(eval $(call PKG_template,QUAGGA_OSPF6D,quagga-ospf6d,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKGSD_QUAGGA_OSPF6D),$(PKG_SECTION)))
$(eval $(call PKG_template,QUAGGA_RIPNGD,quagga-ripngd,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKGSD_QUAGGA_RIPNGD),$(PKG_SECTION)))
$(eval $(call PKG_template,QUAGGA_RIPD,quagga-ripd,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKGSD_QUAGGA_RIPD),$(PKG_SECTION)))
$(eval $(call PKG_template,QUAGGA_VTYSH,quagga-vtysh,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKGSD_QUAGGA_VTYSH),$(PKG_SECTION)))

TARGET_CFLAGS+=		-fcommon
CONFIGURE_ENV+=		quagga_cv_ipforward_method="proc"
CONFIGURE_ARGS+=	--localstatedir=/var/run/quagga \
			--sysconfdir=/etc/quagga \
			--enable-vtysh \
			--enable-user=quagga \
			--enable-group=quagga \
			--disable-pie \
			--disable-babeld \
			--disable-doc \
			--enable-multipath=8

quagga-install:
	$(INSTALL_DIR) $(IDIR_QUAGGA)/etc/quagga
	$(INSTALL_DIR) $(IDIR_QUAGGA)/usr/lib
	$(INSTALL_DIR) $(IDIR_QUAGGA)/usr/sbin
	$(CP) $(WRKINST)/usr/lib/libzebra.so.* $(IDIR_QUAGGA)/usr/lib/
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/zebra \
		$(WRKINST)/usr/sbin/watchquagga $(IDIR_QUAGGA)/usr/sbin/
	$(CP) $(WRKINST)/etc/quagga/zebra.conf.sample \
		$(IDIR_QUAGGA)/etc/quagga/zebra.conf

quagga-bgpd-install:
	$(INSTALL_DIR) $(IDIR_QUAGGA_BGPD)/usr/sbin
	$(CP) $(WRKINST)/usr/sbin/bgpd $(IDIR_QUAGGA_BGPD)/usr/sbin/
	$(CP) $(WRKINST)/etc/quagga/bgpd.conf.sample \
		$(IDIR_QUAGGA)/etc/quagga/bgpd.conf

quagga-ospfd-install:
	$(INSTALL_DIR) $(IDIR_QUAGGA_OSPFD)/usr/lib
	$(INSTALL_DIR) $(IDIR_QUAGGA_OSPFD)/usr/sbin
	$(CP) $(WRKINST)/usr/lib/libospf.so.* $(IDIR_QUAGGA_OSPFD)/usr/lib/
	$(CP) $(WRKINST)/usr/sbin/ospfd $(IDIR_QUAGGA_OSPFD)/usr/sbin/
	$(CP) $(WRKINST)/etc/quagga/ospfd.conf.sample \
		$(IDIR_QUAGGA)/etc/quagga/ospfd.conf

quagga-ospf6d-install:
	$(INSTALL_DIR) $(IDIR_QUAGGA_OSPF6D)/usr/sbin
	$(CP) $(WRKINST)/usr/sbin/ospf6d $(IDIR_QUAGGA_OSPF6D)/usr/sbin/

quagga-ripngd-install:
	$(INSTALL_DIR) $(IDIR_QUAGGA_RIPNGD)/usr/sbin
	$(CP) $(WRKINST)/usr/sbin/ripngd $(IDIR_QUAGGA_RIPNGD)/usr/sbin/

quagga-ripd-install:
	$(INSTALL_DIR) $(IDIR_QUAGGA_RIPD)/usr/sbin
	$(CP) $(WRKINST)/usr/sbin/ripd $(IDIR_QUAGGA_RIPD)/usr/sbin/

quagga-vtysh-install:
	$(INSTALL_DIR) $(IDIR_QUAGGA_VTYSH)/usr/bin
	$(CP) $(WRKINST)/usr/bin/vtysh $(IDIR_QUAGGA_VTYSH)/usr/bin/

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
