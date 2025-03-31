# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		at-spi2-core
PKG_VERSION:=		2.56.0
PKG_EXTRAVER:=		2.56
PKG_RELEASE:=		1
PKG_HASH:=		80d7e8ea0be924e045525367f909d6668dfdd3e87cd40792c6cfd08e6b58e95c
PKG_DESCR:=		d-bus based accessibility framework
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		glib libxtst
PKG_BUILDDEP:=		meson-host glib libXtst libSM intltool-host
PKG_NEEDS:=		intl
PKG_URL:=		http://www.gnome.org/
PKG_SITES:=		$(MASTER_SITE_GNOME:=at-spi2-core/$(PKG_EXTRAVER)/)
PKG_OPTS:=		dev

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
