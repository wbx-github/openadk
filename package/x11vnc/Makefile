# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		x11vnc
PKG_VERSION:=		0.9.17
PKG_RELEASE:=		1
PKG_HASH:=		3ab47c042bc1c33f00c7e9273ab674665b85ab10592a8e0425589fe7f3eb1a69
PKG_DESCR:=		vnc server for x11 displays
PKG_SECTION:=		x11/apps
PKG_DEPENDS:=		libvncserver libpng libjpeg-turbo zlib liblzo
PKG_DEPENDS+=		libgnutls libxi libxdamage libxtst cairo
PKG_DEPENDS+=		libxfixes libxrandr
PKG_BUILDDEP:=		libX11 libXtst libjpeg-turbo libvncserver
PKG_SITES:=		https://github.com/LibVNC/x11vnc/archive/refs/tags/

PKG_CFLINE_X11VNC:=	depends on ADK_BROKEN

DISTFILES:=		${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,X11VNC,x11vnc,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_LDFLAGS+=	-lssl -lcrypto

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ARGS+=	--without-ssl \
			--without-crypto


x11vnc-install:
	$(INSTALL_DIR) $(IDIR_X11VNC)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/x11vnc \
		$(IDIR_X11VNC)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
