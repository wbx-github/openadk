# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		font-bh-ttf
PKG_VERSION:=		1.0.3
PKG_RELEASE:=		1
PKG_HASH:=		c583b4b968ffae6ea30d5b74041afeac83126682c490a9624b770d60d0e63d59
PKG_DESCR:=		x fonts
PKG_SECTION:=		x11/fonts
PKG_BUILDDEP:=		font-util
PKG_URL:=		http://www.x.org/
PKG_SITES:=		http://www.x.org/releases/individual/font/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,FONT_BH_TTF,font-bh-ttf,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

font-bh-ttf-install:
	$(INSTALL_DIR) $(IDIR_FONT_BH_TTF)/usr/share/fonts/X11/TTF
	$(CP) ${WRKINST}/usr/share/fonts/X11/TTF/* \
		$(IDIR_FONT_BH_TTF)/usr/share/fonts/X11/TTF

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
