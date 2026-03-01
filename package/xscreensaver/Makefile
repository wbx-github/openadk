# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		xscreensaver
PKG_VERSION:=		6.14
PKG_RELEASE:=		1
PKG_HASH:=		07f310eb60ece3a6c57abaa722d7209a2c4f54309a5a7b09b6eed20152d073f2
PKG_DESCR:=		popular screensaver for xorg
PKG_SECTION:=		x11/apps
PKG_BUILDDEP:=		mesa
PKG_URL:=		https://www.jwz.org/xscreensaver/
PKG_SITES:=		https://www.jwz.org/xscreensaver/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,XSCREENSAVER,xscreensaver,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		minimal
CONFIGURE_ARGS+=	--prefix=/usr \
			--host=$(GNU_TARGET_NAME)

xscreensaver-install:
	$(INSTALL_DIR) $(IDIR_XSCREENSAVER)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/xscreensaver \
		$(IDIR_XSCREENSAVER)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
