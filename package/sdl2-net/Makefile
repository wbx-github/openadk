# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		sdl2-net
PKG_VERSION:=		2.2.0
PKG_RELEASE:=		1
PKG_HASH:=		4e4a891988316271974ff4e9585ed1ef729a123d22c08bd473129179dc857feb
PKG_DESCR:=		simple directmedia layer net 2
PKG_SECTION:=		libs/misc
PKG_URL:=		http://www.libsdl.org/
PKG_SITES:=		http://www.libsdl.org/projects/SDL_net/release/
PKG_LIBNAME:=		libsdl2-net
PKG_OPTS:=		dev

DISTFILES:=             SDL2_net-$(PKG_VERSION).tar.gz
WRKDIST=		${WRKDIR}/SDL2_net-$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBSDL2_NET,libsdl2-net,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

libsdl2-net-install:
	$(INSTALL_DIR) $(IDIR_LIBSDL2_NET)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libSDL2*.so* \
		$(IDIR_LIBSDL2_NET)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
