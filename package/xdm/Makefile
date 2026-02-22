# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		xdm
PKG_VERSION:=		1.1.17
PKG_RELEASE:=		1
PKG_HASH:=		b1d1db9ba7fd96d50e0b6cf743be2b9ff954f7969a7a9b74d1951b89ec15ca9c
PKG_DESCR:=		display manager
PKG_SECTION:=		x11/apps
PKG_BUILDDEP:=		libXaw libXmu libXt libSM libICE libXft
PKG_DEPENDS:=		xconsole xsm libxaw libxmu libxt libsm libice libxft
PKG_URL:=		http://xorg.freedesktop.org/
PKG_SITES:=		http://www.x.org/releases/individual/app/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,XDM,xdm,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ARGS+=	--with-random-device=/dev/urandom \
			--with-appdefaultdir=/usr/share/X11/app-defaults \
			--with-utmp-file=/dev/null \
			--with-wtmp-file=/dev/null \
			--with-pam

xdm-install:
	$(INSTALL_DIR) $(IDIR_XDM)/usr/lib/X11
	$(CP) $(WRKINST)/usr/lib/X11/* \
		$(IDIR_XDM)/usr/lib/X11
	$(INSTALL_DIR) $(IDIR_XDM)/usr/share/X11
	$(CP) $(WRKINST)/usr/share/X11/* \
		$(IDIR_XDM)/usr/lib/X11
	$(INSTALL_DIR) $(IDIR_XDM)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/xdm \
		$(IDIR_XDM)/usr/bin
	$(INSTALL_DIR) $(IDIR_XDM)/usr/share/backgrounds
	$(CP) ./files/puppy.png \
		$(IDIR_XDM)/usr/share/backgrounds

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
