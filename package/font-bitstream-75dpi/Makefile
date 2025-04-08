# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		font-bitstream-75dpi
PKG_VERSION:=		1.0.3
PKG_RELEASE:=		1
PKG_HASH:=		c43ae370932eb8a4789a5b1f9801da15228b0d4c803251785c38d82aef024a4b
PKG_DESCR:=		x fonts
PKG_SECTION:=		x11/fonts
PKG_BUILDDEP:=		font-util
PKG_URL:=		http://www.x.org/
PKG_SITES:=		http://www.x.org/releases/individual/font/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,FONT_BITSTREAM_75DPI,font-bitstream-75dpi,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

font-bitstream-75dpi-install:
	$(INSTALL_DIR) $(IDIR_FONT_BITSTREAM_75DPI)/usr/share/fonts/X11/75dpi
	$(CP) ${WRKINST}/usr/share/fonts/X11/75dpi/* \
		$(IDIR_FONT_BITSTREAM_75DPI)/usr/share/fonts/X11/75dpi

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
