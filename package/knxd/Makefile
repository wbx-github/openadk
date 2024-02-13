# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		knxd
PKG_VERSION:=		0.14.61
PKG_RELEASE:=		1
PKG_HASH:=		b5284c89a55a2c53e0ff769ec4f736fc1ad4b55afdd2a18b9258fa95f708d798
PKG_DESCR:=		knx daemon
PKG_SECTION:=		sys/hw
PKG_DEPENDS:=		libev
PKG_BUILDDEP:=		libev cmake-host
PKG_URL:=		https://github.com/knxd/knxd
PKG_SITES:=		https://github.com/knxd/knxd/archive/refs/tags/

PKG_CFLINE_KNXD:=	depends on ADK_BROKEN

DISTFILES:=		$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,KNXD,knxd,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

AUTOTOOL_STYLE:=	bootstrap

CONFIGURE_ARGS+=	--disable-systemd --disable-usb

knxd-install:
	$(INSTALL_DIR) $(IDIR_KNXD)/usr/bin
	$(INSTALL_DIR) $(IDIR_KNXD)/usr/lib
	$(INSTALL_DIR) $(IDIR_KNXD)/usr/share
	$(INSTALL_BIN) $(WRKINST)/usr/bin/knxd \
		$(IDIR_KNXD)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/knxtool \
		$(IDIR_KNXD)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/libexec/knxd_args \
		$(IDIR_KNXD)/usr/bin
	$(CP) $(WRKINST)/usr/lib/libeib*.so* \
		$(IDIR_KNXD)/usr/lib
	$(CP) $(WRKINST)/usr/libexec/knxd/* \
		$(IDIR_KNXD)/usr/bin
	$(CP) $(WRKINST)/usr/share/* \
		$(IDIR_KNXD)/usr/share


include $(ADK_TOPDIR)/mk/pkg-bottom.mk
