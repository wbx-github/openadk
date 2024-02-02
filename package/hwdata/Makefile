# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		hwdata
PKG_VERSION:=		0.378
PKG_RELEASE:=		1
PKG_HASH:=		098ea8db12a50290f4b23f7f521edf9c5bab25935d2740de17e4a487110b40c8
PKG_DESCR:=		combined repository of pci.ids and usb.ids
PKG_SECTION:=		sys/hw
PKG_URL:=		https://github.com/vcrhonek/hwdata
PKG_SITES:=		https://github.com/vcrhonek/hwdata/archive/refs/tags/

DISTFILES:=		v$(PKG_VERSION).tar.gz

PKG_SUBPKGS:=		HWDATA_NET HWDATA_PCI HWDATA_USB HWDATA_PNP
PKGSD_HWDATA_NET:=	HWDATA files oui.txt and iab.txt
PKGSD_HWDATA_PCI:=	HWDATA file pci.ids
PKGSD_HWDATA_USB:=	HWDATA file usb.ids
PKGSD_HWDATA_PNP:=	HWDATA file pnp.ids

PKG_FLAVOURS_HWDATA:=	WITH_GZIP
PKGFD_WITH_GZIP:=	gzip ids before installation

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,HWDATA_NET,hwdata-net,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKGSD_HWDATA_NET),$(PKG_SECTION)))
$(eval $(call PKG_template,HWDATA_PCI,hwdata-pci,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKGSD_HWDATA_PCI),$(PKG_SECTION)))
$(eval $(call PKG_template,HWDATA_USB,hwdata-usb,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKGSD_HWDATA_USB),$(PKG_SECTION)))
$(eval $(call PKG_template,HWDATA_PNP,hwdata-pnp,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKGSD_HWDATA_PNP),$(PKG_SECTION)))

define HWDATA_INSTALL_template
$(2)-install:
	$$(INSTALL_DIR) $$(IDIR_$(1))/usr/share/hwdata
	$$(INSTALL_DATA) $$(patsubst %,$$(WRKINST)/usr/share/hwdata/%,$(3)) \
		$$(IDIR_$(1))/usr/share/hwdata/
endef

$(eval $(call HWDATA_INSTALL_template,HWDATA_NET,hwdata-net,oui.txt iab.txt))
ifeq ($(ADK_PACKAGE_HWDATA_WITH_GZIP),y)
$(eval $(call HWDATA_INSTALL_template,HWDATA_PCI,hwdata-pci,pci.ids.gz))
$(eval $(call HWDATA_INSTALL_template,HWDATA_USB,hwdata-usb,usb.ids.gz))
$(eval $(call HWDATA_INSTALL_template,HWDATA_PNP,hwdata-pnp,pnp.ids.gz))
else
$(eval $(call HWDATA_INSTALL_template,HWDATA_PCI,hwdata-pci,pci.ids))
$(eval $(call HWDATA_INSTALL_template,HWDATA_USB,hwdata-usb,usb.ids))
$(eval $(call HWDATA_INSTALL_template,HWDATA_PNP,hwdata-pnp,pnp.ids))
endif

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
