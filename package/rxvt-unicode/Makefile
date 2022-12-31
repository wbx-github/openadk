# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		rxvt-unicode
PKG_VERSION:=		9.30
PKG_RELEASE:=		1
PKG_HASH:=		fe1c93d12f385876457a989fc3ae05c0915d2692efc59289d0f70fabe5b44d2d
PKG_DESCR:=		terminal emulator with unicode support
PKG_SECTION:=		x11/apps
PKG_DEPENDS:=		libx11 fontconfig libxft libxml2 gdk-pixbuf libptytty
PKG_DEPENDS+=		libffi libmount
PKG_BUILDDEP:=		libX11 fontconfig libXft libxml2 gdk-pixbuf libptytty
PKG_BUILDDEP+=		libffi util-linux
PKG_NEEDS:=		c++
PKG_URL:=		http://software.schmorp.de/pkg/rxvt-unicode.html
PKG_SITES:=		http://dist.schmorp.de/rxvt-unicode/

DISTFILES:=             ${PKG_NAME}-${PKG_VERSION}.tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,RXVT_UNICODE,rxvt-unicode,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_LDFLAGS+=	-lpthread
CONFIGURE_ARGS+=	--disable-perl

rxvt-unicode-install:
	$(INSTALL_DIR) $(IDIR_RXVT_UNICODE)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/urxvt \
		$(IDIR_RXVT_UNICODE)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
