# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		keybinder
PKG_VERSION:=		0.3.2
PKG_RELEASE:=		1
PKG_HASH:=		e6e3de4e1f3b201814a956ab8f16dfc8a262db1937ff1eee4d855365398c6020
PKG_DESCR:=		utility library registering global x keyboard shortcuts
PKG_SECTION:=		libs/misc
PKG_SITES:=		https://github.com/kupferlauncher/keybinder/releases/download/keybinder-3.0-v0.3.2/
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_NAME)-3.0-$(PKG_VERSION).tar.gz
WRKDIST=		${WRKDIR}/${PKG_NAME}-3.0-${PKG_VERSION}

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,KEYBINDER,keybinder,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

keybinder-install:
	$(INSTALL_DIR) $(IDIR_KEYBINDER)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libkeybinder*.so* \
		$(IDIR_KEYBINDER)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
