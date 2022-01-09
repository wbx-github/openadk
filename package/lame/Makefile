# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		lame
PKG_VERSION:=		3.100
PKG_RELEASE:=		1
PKG_HASH:=		ddfe36cab873794038ae2c1210557ad34857a4b6bdc515785d1da9e175b1da1e
PKG_DESCR:=		mp3 encoder
PKG_SECTION:=		mm/audio
PKG_DEPENDS:=		libncurses
PKG_BUILDDEP:=		ncurses
PKG_URL:=		http://lame.sourceforge.net/
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=lame/}
PKG_LIBNAME:=		libmp3lame
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_SUBPKGS:=		LAME LIBMP3LAME
PKGSD_LIBMP3LAME:=	mp3 encoding library
PKGSC_LIBMP3LAME:=	libs/audio

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LAME,lame,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,LIBMP3LAME,libmp3lame,$(PKG_VERSION)-${PKG_RELEASE},,${PKGSD_LIBMP3LAME},${PKGSC_LIBMP3LAME},${PKG_OPTS}))

TARGET_LDFLAGS+=	-ltinfo
ifeq ($(ADK_TARGET_ARCH_X86),y)
TARGET_CFLAGS+=		-msse
endif

lame-install:
	$(INSTALL_DIR) $(IDIR_LAME)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/lame $(IDIR_LAME)/usr/bin

libmp3lame-install:
	$(INSTALL_DIR) $(IDIR_LIBMP3LAME)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libmp3lame.so* $(IDIR_LIBMP3LAME)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
