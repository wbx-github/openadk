# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libpsl
PKG_VERSION:=		0.21.5
PKG_RELEASE:=		1
PKG_HASH:=		1dcc9ceae8b128f3c0b3f654decd0e1e891afc6ff81098f227ef260449dae208
PKG_DESCR:=		C library for the Public Suffix List
PKG_SECTION:=		libs/misc
PKG_SITES:=		https://github.com/rockdaboot/libpsl/releases/download/$(PKG_VERSION)/
PKG_OPTS:=		dev

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBPSL,libpsl,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

libpsl-install:
	$(INSTALL_DIR) $(IDIR_LIBPSL)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libpsl*.so* \
		$(IDIR_LIBPSL)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
