# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		chocolate-doom
PKG_VERSION:=		3.0.1
PKG_RELEASE:=		1
PKG_HASH:=		a54383beef6a52babc5b00d58fcf53a454f012ced7b1936ba359b13f1f10ac66
PKG_DESCR:=		doom
PKG_SECTION:=		app/games
PKG_DEPENDS:=		libsdl2 libsdl2-mixer libsdl2-net
PKG_BUILDDEP:=		sdl2 sdl2-mixer sdl2-net
PKG_URL:=		https://www.chocolate-doom.org
PKG_SITES:=		https://github.com/chocolate-doom/chocolate-doom/archive/refs/tags/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz
WRKDIST=		${WRKDIR}/$(PKG_NAME)-$(PKG_NAME)-$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,CHOCOLATE_DOOM,chocolate-doom,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

AUTOTOOL_STYLE:=	autogen
TARGET_CFLAGS+=		-fcommon

chocolate-doom-install:
	$(INSTALL_DIR) $(IDIR_CHOCOLATE_DOOM)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/chocolate-doom \
		$(IDIR_CHOCOLATE_DOOM)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
