# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		dialog
PKG_VERSION:=		1.3-20250116
PKG_RELEASE:=		1
PKG_HASH:=		68406329827b783d0a8959cc20a94c6e1791ac861a27f854e06e9020541816dd
PKG_DESCR:=		text gui interface
PKG_SECTION:=		sys/misc
PKG_DEPENDS:=		libncurses
PKG_BUILDDEP:=		ncurses
PKG_URL:=		http://invisible-island.net/dialog/dialog.html
PKG_SITES:=		http://deb.debian.org/debian/pool/main/d/dialog/

DISTFILES:=		${PKG_NAME}_${PKG_VERSION}.orig.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,DIALOG,dialog,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

MAKE_FILE:=		makefile
# Should detect this automatically but while doing so it tries to add /lib64 which breaks build so specify this explicitely
CONFIGURE_ARGS+=	--with-ncursesw

dialog-install:
	$(INSTALL_DIR) $(IDIR_DIALOG)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/dialog $(IDIR_DIALOG)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
