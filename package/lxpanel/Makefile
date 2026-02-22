# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		lxpanel
PKG_VERSION:=		0.11.1
PKG_RELEASE:=		1
PKG_HASH:=		251f32cdcc3722ed942bdf33d50d9f0a6bd3ffe07983047b023e02e6c9561d92
PKG_DESCR:=		lxde panel
PKG_SECTION:=		x11/lxde
PKG_DEPENDS:=		libgtk3 libwnck keybinder libcurl
PKG_BUILDDEP:=		libgtk3 libwnck keybinder curl
PKG_URL:=		https://lxde.org
PKG_SITES:=		https://github.com/lxde/releases/raw/refs/heads/master/releases/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LXPANEL,lxpanel,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIGURE_ARGS+=	--enable-gtk3 \
			--with-plugins=none

lxpanel-install:
	$(INSTALL_DIR) $(IDIR_LXPANEL)/etc/xdg
	$(CP) $(WRKINST)/etc/xdg/* \
		$(IDIR_LXPANEL)/etc/xdg
	$(INSTALL_DIR) $(IDIR_LXPANEL)/usr/lib
	$(CP) $(WRKINST)/usr/lib/lxpanel/lib*.so* \
		$(IDIR_LXPANEL)/usr/lib
	$(INSTALL_DIR) $(IDIR_LXPANEL)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/lxpanel \
		$(IDIR_LXPANEL)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
