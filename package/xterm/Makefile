# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		xterm
PKG_VERSION:=		369
PKG_RELEASE:=		1
PKG_HASH:=		71ed6a48d064893d2149741a002781a973496fd24d52dadd364f63439a764e26
PKG_DESCR:=		terminal emulator
PKG_SECTION:=		x11/apps
PKG_DEPENDS:=		libxaw libxt libncurses libxft fontconfig libuuid
PKG_BUILDDEP:=		ncurses libXt libXmu libXaw libXft util-linux libSM
PKG_URL:=		http://invisible-island.net/xterm/xterm.html
PKG_SITES:=		https://invisible-island.net/datafiles/release/

DISTFILES:=             ${PKG_NAME}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,XTERM,xterm,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_LDFLAGS+=	-ltinfo
CONFIGURE_ARGS+=	--with-app-defaults=/usr/lib/X11/app-defaults \
			--x-includes="$(STAGING_TARGET_DIR)/usr/include" \
			--x-libraries="$(STAGING_TARGET_DIR)/usr/lib" \
			--with-freetype-cflags="-I$(STAGING_TARGET_DIR)/usr/include/freetype2" \
			--disable-regex \
			--disable-pty-handshake

xterm-install:
	$(INSTALL_DIR) $(IDIR_XTERM)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/{koi8rxterm,resize,uxterm,xterm} \
		$(IDIR_XTERM)/usr/bin/
	$(INSTALL_DIR) $(IDIR_XTERM)/usr/lib/X11/app-defaults
	$(INSTALL_DATA) ${WRKINST}/usr/lib/X11/app-defaults/{KOI8RXTerm,KOI8RXTerm-color,UXTerm,UXTerm-color,XTerm,XTerm-color} \
		${IDIR_XTERM}/usr/lib/X11/app-defaults/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
