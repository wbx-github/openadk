# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		xsm
PKG_VERSION:=		1.0.3
PKG_RELEASE:=		1
PKG_HASH:=		f70815139d62416dbec5915ec37db66f325932a69f6350bb1a74c0940cdc796a
PKG_DESCR:=		session manager
PKG_SECTION:=		x11/utils
PKG_DEPENDS:=		libxaw
PKG_BUILDDEP:=		libXaw
PKG_URL:=		http://xorg.freedesktop.org/
PKG_SITES:=		http://www.x.org/releases/individual/app/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,XSM,xsm,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ARGS+=	--with-appdefaultdir=/usr/share/X11/app-defaults

xsm-install:
	$(INSTALL_DIR) $(IDIR_XSM)/usr/share/X11
	$(CP) $(WRKINST)/usr/share/X11/* \
		$(IDIR_XSM)/usr/share/X11
	$(INSTALL_DIR) $(IDIR_XSM)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/xsm \
		$(IDIR_XSM)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
