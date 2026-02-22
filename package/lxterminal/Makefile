# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		lxterminal
PKG_VERSION:=		0.4.1
PKG_RELEASE:=		1
PKG_HASH:=		851a0bc59e3e1a0974baf0cf0d877dba8b3e1d400418121fd6e715607b56ad31
PKG_DESCR:=		lxde terminal
PKG_DEPENDS:=		vte libgtk3 harfbuzz glib pango gdk-pixbuf libmount
PKG_BUILDDEP:=		vte libgtk3 harfbuzz glib pango gdk-pixbuf util-linux
PKG_SECTION:=		x11/lxde
PKG_URL:=		https://lxde.org/
PKG_SITES:=		https://github.com/lxde/releases/raw/refs/heads/master/releases/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LXTERMINAL,lxterminal,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIGURE_ARGS+=	--enable-gtk3

lxterminal-install:
	$(INSTALL_DIR) $(IDIR_LXTERMINAL)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/lxterminal \
		$(IDIR_LXTERMINAL)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
