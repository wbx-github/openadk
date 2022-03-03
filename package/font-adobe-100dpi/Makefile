# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		font-adobe-100dpi
PKG_VERSION:=		1.0.3
PKG_RELEASE:=		1
PKG_HASH:=		97d9c1e706938838e4134d74f0836ae9d9ca6705ecb405c9a0ac8fdcbd9c2159
PKG_DESCR:=		x fonts
PKG_SECTION:=		x11/fonts
PKG_DEPENDS:=		font-util
PKG_BUILDDEP:=		font-util
PKG_URL:=		http://www.x.org/
PKG_SITES:=		http://www.x.org/releases/individual/font/

PKG_HOST_DEPENDS:=      !netbsd !openbsd !cygwin !freebsd !mirbsd

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,FONT_ADOBE_100DPI,font-adobe-100dpi,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

XAKE_FLAGS+=		DESTDIR=''

font-adobe-100dpi-install:
	$(INSTALL_DIR) $(IDIR_FONT_ADOBE_100DPI)/usr/share/fonts/X11/100dpi
	$(CP) ${STAGING_TARGET_DIR}/usr/share/fonts/X11/100dpi/* \
		$(IDIR_FONT_ADOBE_100DPI)/usr/share/fonts/X11/100dpi

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
