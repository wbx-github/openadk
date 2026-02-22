# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		lxtask
PKG_VERSION:=		0.1.12
PKG_RELEASE:=		1
PKG_HASH:=		099b98ab661ac83019ff9dfd87f0098b008e11b1f97113c0be39d883e1a30102
PKG_DESCR:=		lxde task manager
PKG_SECTION:=		x11/lxde
PKG_DEPENDS:=		libgtk3 harfbuzz
PKG_URL:=		https://lxde.org/
PKG_SITES:=		https://github.com/lxde/releases/raw/refs/heads/master/releases/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LXTASK,lxtask,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIGURE_ARGS+=	--enable-gtk3

lxtask-install:
	$(INSTALL_DIR) $(IDIR_LXTASK)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/lxtask \
		$(IDIR_LXTASK)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
