# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		at-spi2-atk
PKG_VERSION:=		2.38.0
PKG_EXTRAVER:=		2.38
PKG_RELEASE:=		1
PKG_HASH:=		cfa008a5af822b36ae6287f18182c40c91dd699c55faa38605881ed175ca464f
PKG_DESCR:=		d-bus based accessibility framework
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		glib libxtst
PKG_BUILDDEP:=		meson-host glib libXtst
PKG_URL:=		http://www.gnome.org/
PKG_SITES:=		$(MASTER_SITE_GNOME:=at-spi2-atk/$(PKG_EXTRAVER)/)
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,AT_SPI2_ATK,at-spi2-atk,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

at-spi2-atk-install:
	$(INSTALL_DIR) $(IDIR_AT_SPI2_ATK)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libat*.so* $(IDIR_AT_SPI2_ATK)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
