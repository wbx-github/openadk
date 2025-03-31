# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		enchant
PKG_VERSION:=		2.8.2
PKG_RELEASE:=		1
PKG_HASH:=		8f19535adb5577b83b00e02f330fe9b9eb40dd21f19e2899636fc4d3a7696375
PKG_DESCR:=		spelling library
PKG_SECTION:=		libs/misc
PKG_SITES:=		https://github.com/rrthomas/enchant/releases/download/v$(PKG_VERSION)/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,ENCHANT,enchant,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

enchant-install:
	$(INSTALL_DIR) $(IDIR_ENCHANT)/usr/lib/enchant
	$(CP) $(WRKINST)/usr/lib/libenchant.so* \
		$(IDIR_ENCHANT)/usr/lib
	$(CP) $(WRKINST)/usr/lib/enchant/*.so* \
		$(IDIR_ENCHANT)/usr/lib/enchant

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
