# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		font-bh-type1
PKG_VERSION:=		1.0.3
PKG_RELEASE:=		1
PKG_HASH:=		d5602f1d749ccd31d3bc1bb6f0c5d77400de0e5e3ac5abebd2a867aa2a4081a4
PKG_DESCR:=		x fonts
PKG_SECTION:=		x11/fonts
PKG_BUILDDEP:=		font-util
PKG_URL:=		http://www.x.org/
PKG_SITES:=		http://www.x.org/releases/individual/font/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,FONT_BH_TYPE1,font-bh-type1,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

font-bh-type1-install:
	$(INSTALL_DIR) $(IDIR_FONT_BH_TYPE1)/usr/share/fonts/X11/Type1
	$(CP) ${WRKINST}/usr/share/fonts/X11/Type1/* \
		$(IDIR_FONT_BH_TYPE1)/usr/share/fonts/X11/Type1

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
