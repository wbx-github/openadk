# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		pango
PKG_VERSION:=		1.50.4
PKG_EXTRAVER:=		1.50
PKG_RELEASE:=		1
PKG_HASH:=		f4ad63e87dc2b145300542a4fb004d07a9f91b34152fae0ddbe50ecdd851c162
PKG_DESCR:=		library for laying out and rendering of text
PKG_SECTION:=		libs/fonts
PKG_BUILDDEP:=		libXft glib cairo harfbuzz fontconfig fribidi
HOST_BUILDDEP:=		cairo-host harfbuzz-host glib-host meson-host
PKG_NEEDS:=		c++
PKG_URL:=		http://www.pango.org/
PKG_SITES:=		$(MASTER_SITE_GNOME:=pango/$(PKG_EXTRAVER)/)
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,PANGO,pango,$(PKG_VERSION)-$(PKG_RELEASE)))
$(eval $(call PKG_template,PANGO,pango,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

HOST_STYLE:=		meson
CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

pango-install:
	$(INSTALL_DIR) $(IDIR_PANGO)/etc/pango $(IDIR_PANGO)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libpango*.so* \
		$(IDIR_PANGO)/usr/lib

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
