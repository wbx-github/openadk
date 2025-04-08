# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		font-bh-lucidatypewriter-100dpi
PKG_VERSION:=		1.0.3
PKG_RELEASE:=		1
PKG_HASH:=		5e05a642182ec6a77bd7cacb913d3c86b364429329a5f223b69792d418f90ae9
PKG_DESCR:=		x fonts
PKG_SECTION:=		x11/fonts
PKG_BUILDDEP:=		font-util
PKG_URL:=		http://www.x.org/
PKG_SITES:=		http://www.x.org/releases/individual/font/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,FONT_BH_LUCIDATYPEWRITER_100DPI,font-bh-lucidatypewriter-100dpi,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

font-bh-lucidatypewriter-100dpi-install:
	$(INSTALL_DIR) $(IDIR_FONT_BH_LUCIDATYPEWRITER_100DPI)/usr/share/fonts/X11/100dpi
	$(CP) ${WRKINST}/usr/share/fonts/X11/100dpi/* \
		$(IDIR_FONT_BH_LUCIDATYPEWRITER_100DPI)/usr/share/fonts/X11/100dpi

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
