# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		at-spi2-core
PKG_VERSION:=		2.60.3
PKG_RELEASE:=		1
PKG_HASH:=		1ce9adb87dd4a54f70119d9639a2398d9e60befc542be59b7fa6161946a97d05
PKG_DESCR:=		d-bus based accessibility framework
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		glib libxtst
PKG_BUILDDEP:=		meson-host glib libXtst libSM intltool-host
PKG_NEEDS:=		intl
PKG_URL:=		http://www.gnome.org/
PKG_SITES:=		https://gitlab.gnome.org/GNOME/at-spi2-core/-/archive/$(PKG_VERSION)/
PKG_OPTS:=		dev

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,AT_SPI2_CORE,at-spi2-core,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

at-spi2-core-install:
	$(INSTALL_DIR) $(IDIR_AT_SPI2_CORE)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libat*.so* $(IDIR_AT_SPI2_CORE)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
