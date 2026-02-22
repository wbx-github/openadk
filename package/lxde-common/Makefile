# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		lxde-common
PKG_VERSION:=		0.99.3
PKG_RELEASE:=		1
PKG_HASH:=		021bac866122325401e57c0ed5b55e5796f1a7e5d432958c662bd65dae5bbdb0
PKG_DESCR:=		lxde common data
PKG_SECTION:=		x11/lxde
PKG_URL:=		https://lxde.org/
PKG_SITES:=		https://github.com/lxde/releases/raw/refs/heads/master/releases/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LXDE_COMMON,lxde-common,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

lxde-common-install:
	$(INSTALL_DIR) $(IDIR_LXDE_COMMON)/etc/xdg
	$(CP) $(WRKINST)/etc/xdg/* $(IDIR_LXDE_COMMON)/etc/xdg
	$(INSTALL_DIR) $(IDIR_LXDE_COMMON)/usr/share
	$(CP) $(WRKINST)/usr/share/* $(IDIR_LXDE_COMMON)/usr/share
	$(INSTALL_DIR) $(IDIR_LXDE_COMMON)/usr/bin
	$(CP) $(WRKINST)/usr/bin/* $(IDIR_LXDE_COMMON)/usr/bin
	$(INSTALL_DIR) $(IDIR_LXDE_COMMON)/etc/X11/xdm
	$(CP) ./files/Xsession $(IDIR_LXDE_COMMON)/etc/X11/xdm/Xsession

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
