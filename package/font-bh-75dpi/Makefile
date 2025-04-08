# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		font-bh-75dpi
PKG_VERSION:=		1.0.3
PKG_RELEASE:=		1
PKG_HASH:=		720b6a513894bfc09a163951ec3dd8311201e08ee40e8891547b6c129ffb5fce
PKG_DESCR:=		x fonts
PKG_SECTION:=		x11/fonts
PKG_BUILDDEP:=		font-util
PKG_URL:=		http://www.x.org/
PKG_SITES:=		http://www.x.org/releases/individual/font/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,FONT_BH_75DPI,font-bh-75dpi,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

font-bh-75dpi-install:
	$(INSTALL_DIR) $(IDIR_FONT_BH_75DPI)/usr/share/fonts/X11/75dpi
	$(CP) ${WRKINST}/usr/share/fonts/X11/75dpi/* \
		$(IDIR_FONT_BH_75DPI)/usr/share/fonts/X11/75dpi

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
