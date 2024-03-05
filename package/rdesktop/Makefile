# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		rdesktop
PKG_VERSION:=		1.9.0
PKG_RELEASE:=		1
PKG_HASH:=		d547c2e6f3e4c818a7e69a0f39adb39fac303633e0c25aa804bb588507ffc230
PKG_DESCR:=		client for windows terminal services
PKG_SECTION:=		x11/apps
PKG_DEPENDS:=		libsamplerate alsa-lib libao libgnutls
PKG_BUILDDEP:=		libsamplerate alsa-lib libao gnutls
PKG_URL:=		http://www.rdesktop.org/
PKG_SITES:=		https://github.com/rdesktop/rdesktop/archive/refs/tags/

DISTFILES:=		v${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,RDESKTOP,rdesktop,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_CFLAGS+=		-D_GNU_SOURCE -D_POSIX_SOURCE
AUTOTOOL_STYLE:=	bootstrap
CONFIGURE_ARGS+=	--disable-smartcard \
			--disable-credssp

rdesktop-install:
	$(INSTALL_DIR) $(IDIR_RDESKTOP)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/rdesktop \
		$(IDIR_RDESKTOP)/usr/bin
	$(INSTALL_DIR) $(IDIR_RDESKTOP)/usr/share/rdesktop/keymaps
	${INSTALL_DATA} ${WRKINST}/usr/share/rdesktop/keymaps/* \
		$(IDIR_RDESKTOP)/usr/share/rdesktop/keymaps

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
