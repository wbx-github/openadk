# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		dejavu-fonts-ttf
PKG_VERSION:=		2.37
PKG_RELEASE:=		1
PKG_HASH:=		fa9ca4d13871dd122f61258a80d01751d603b4d3ee14095d65453b4e846e17d7
PKG_DESCR:=		free fonts
PKG_SECTION:=		x11/fonts
PKG_URL:=		https://dejavu-fonts.github.io/
PKG_SITES:=		http://sourceforge.net/projects/dejavu/files/dejavu/$(PKG_VERSION)/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,DEJAVU_FONTS_TTF,dejavu-fonts-ttf,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

dejavu-fonts-ttf-install:
	$(INSTALL_DIR) $(IDIR_DEJAVU_FONTS_TTF)/usr/share/fonts/dejavu
	$(INSTALL_BIN) $(WRKBUILD)/ttf/*.ttf \
		$(IDIR_DEJAVU_FONTS_TTF)/usr/share/fonts/dejavu

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
