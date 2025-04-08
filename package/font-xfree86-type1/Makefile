# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		font-xfree86-type1
PKG_VERSION:=		1.0.4
PKG_RELEASE:=		1
PKG_HASH:=		02b3839ae79ba6a7750525bb3b0c281305664b95bf63b4a0baa230a277b4f928
PKG_DESCR:=		x fonts
PKG_SECTION:=		x11/fonts
PKG_BUILDDEP:=		font-util
PKG_URL:=		http://www.x.org/
PKG_SITES:=		http://www.x.org/releases/individual/font/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,FONT_XFREE86_TYPE1,font-xfree86-type1,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

font-xfree86-type1-install:
	$(INSTALL_DIR) $(IDIR_FONT_XFREE86_TYPE1)/usr/share/fonts/X11/Type1
	$(CP) ${WRKINST}/usr/share/fonts/X11/Type1/* \
		$(IDIR_FONT_XFREE86_TYPE1)/usr/share/fonts/X11/Type1

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
