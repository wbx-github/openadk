# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		sdl2-mixer
PKG_VERSION:=		2.6.3
PKG_RELEASE:=		1
PKG_HASH:=		7a6ba86a478648ce617e3a5e9277181bc67f7ce9876605eea6affd4a0d6eea8f
PKG_DESCR:=		simple directmedia layer mixer 2
PKG_SECTION:=		libs/misc
PKG_URL:=		http://www.libsdl.org/
PKG_SITES:=		http://www.libsdl.org/projects/SDL_mixer/release/
PKG_LIBNAME:=		libsdl2-mixer
PKG_OPTS:=		dev

DISTFILES:=             SDL2_mixer-$(PKG_VERSION).tar.gz
WRKDIST=		${WRKDIR}/SDL2_mixer-$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBSDL2_MIXER,libsdl2-mixer,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

libsdl2-mixer-install:
	$(INSTALL_DIR) $(IDIR_LIBSDL2_MIXER)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libSDL2*.so* \
		$(IDIR_LIBSDL2_MIXER)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
