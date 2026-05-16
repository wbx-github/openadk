# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		enchant
PKG_VERSION:=		2.8.16
PKG_RELEASE:=		1
PKG_HASH:=		d73162b5eff401a6397e1215e2b103bcef83f921c396c7f6b1394d2450d124e2
PKG_DESCR:=		spelling library
PKG_SECTION:=		libs/misc
PKG_URL:=		https://github.com/rrthomas/enchant
PKG_SITES:=		https://github.com/rrthomas/enchant/releases/download/v$(PKG_VERSION)/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,ENCHANT,enchant,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

AUTOTOOL_STYLE:=	autoreconf

pre-install:
	mkdir -p $(WRKINST)/usr/lib/enchant-2

enchant-install:
	$(INSTALL_DIR) $(IDIR_ENCHANT)/usr/lib/enchant
	$(CP) $(WRKINST)/usr/lib/libenchant*.so* \
		$(IDIR_ENCHANT)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
