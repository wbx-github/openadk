# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		feh
PKG_VERSION:=		3.12.2
PKG_RELEASE:=		1
PKG_HASH:=		a988c387a8800dddc43d1736c6a475f630e9de032ff11dd1162b8805110d5dd1
PKG_DESCR:=		image viewer
PKG_SECTION:=		mm/image
PKG_BUILDDEP:=		imlib2 libXt
PKG_DEPENDS:=		imlib2
PKG_SITES:=		https://github.com/derf/feh/archive/refs/tags/

DISTFILES:=             ${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,FEH,feh,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

XAKE_FLAGS+=		PREFIX=/usr
CONFIG_STYLE:=		manual
MAKE_FLAGS+=		curl=0 xinerama=0

feh-install:
	$(INSTALL_DIR) $(IDIR_FEH)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/feh $(IDIR_FEH)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
