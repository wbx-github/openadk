# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		menu-cache
PKG_VERSION:=		1.1.1
PKG_RELEASE:=		1
PKG_HASH:=		8232399b45b0b99bd480ec6df8fb9a5b8e034cc31c90b375916b372631f4531a
PKG_DESCR:=		lxde menu cache library
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		libfm-extra
PKG_BUILDDEP:=		libfm-extra
PKG_URL:=		https://lxde.org/
PKG_SITES:=		https://github.com/lxde/releases/raw/refs/heads/master/releases/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,MENU_CACHE,menu-cache,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

menu-cache-install:
	$(INSTALL_DIR) $(IDIR_MENU_CACHE)/usr/libexec
	$(CP) $(WRKINST)/usr/libexec/* \
		$(IDIR_MENU_CACHE)/usr/libexec
	$(INSTALL_DIR) $(IDIR_MENU_CACHE)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libmenu-cache*.so* \
		$(IDIR_MENU_CACHE)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
