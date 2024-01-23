# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		sdl2
PKG_VERSION:=		2.28.5
PKG_RELEASE:=		1
PKG_HASH:=		9f0556e4a24ef5b267010038ad9e9948b62f236d5bcc4b22179f95ef62d84023
PKG_DESCR:=		simple directmedia layer 2
PKG_SECTION:=		libs/misc
PKG_URL:=		http://www.libsdl.org/
PKG_SITES:=		https://github.com/libsdl-org/SDL/archive/refs/tags/
PKG_BUILDDEP:=		mesa libdrm alsa-lib
PKG_DEPENDS:=		mesa libdrm alsa-lib
PKG_LIBNAME:=		libsdl2
PKG_OPTS:=		dev

DISTFILES:=             release-$(PKG_VERSION).tar.gz
WRKDIST=		${WRKDIR}/SDL-release-$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBSDL2,libsdl2,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

libsdl2-install:
	$(INSTALL_DIR) $(IDIR_LIBSDL2)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libSDL2*.so* \
		$(IDIR_LIBSDL2)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
