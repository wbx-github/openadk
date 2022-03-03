# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		font-adobe-75dpi
PKG_VERSION:=		1.0.3
PKG_RELEASE:=		1
PKG_HASH:=		61eb1fcfec89f7435cb92cd68712fbe4ba412ca562b1f5feec1f6daa1b8544f6
PKG_DESCR:=		x fonts
PKG_SECTION:=		x11/fonts
PKG_DEPENDS:=		font-util
PKG_BUILDDEP:=		font-util
PKG_URL:=		http://www.x.org/
PKG_SITES:=		http://www.x.org/releases/individual/font/

PKG_HOST_DEPENDS:=      !netbsd !openbsd !cygwin !freebsd !mirbsd

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,FONT_ADOBE_75DPI,font-adobe-75dpi,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

XAKE_FLAGS+=		DESTDIR=''

font-adobe-75dpi-install:
	$(INSTALL_DIR) $(IDIR_FONT_ADOBE_75DPI)/usr/share/fonts/X11/75dpi
	$(CP) ${STAGING_TARGET_DIR}/usr/share/fonts/X11/75dpi/* \
		$(IDIR_FONT_ADOBE_75DPI)/usr/share/fonts/X11/75dpi

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
