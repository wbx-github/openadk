# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		xburst-tools
PKG_VERSION:=		bcf6c4e07a13aa2eb1b379863261f3ba5e4511a7
PKG_RELEASE:=		1
PKG_DESCR:=		usb boot and nand flash tools for ingenic xburst
HOST_BUILDDEP:=		libusb-host libusb-compat-host confuse-host
PKG_SECTION:=		base/tools
PKG_URL:=		https://github.com/kyak/xburst-tools

NO_DISTFILES:=		1

PKG_CFLINE_XBURST_TOOLS:=depends on ADK_HOST_ONLY

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,XBURST_TOOLS,xburst-tools,$(PKG_VERSION)-${PKG_RELEASE}))

HOST_CONFIGURE_ARGS+=	--disable-firmware

hostpost-install:
	$(INSTALL_DIR) $(STAGING_HOST_DIR)/usr/share/xburst-tools
	$(CP) ./files/xburst_* $(STAGING_HOST_DIR)/usr/share/xburst-tools/

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
