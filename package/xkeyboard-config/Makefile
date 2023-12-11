# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		xkeyboard-config
PKG_VERSION:=		2.37
PKG_RELEASE:=		1
PKG_HASH:=		eb1383a5ac4b6210d7c7302b9d6fab052abdf51c5d2c9b55f1f779997ba68c6c
PKG_DESCR:=		keyboard config
PKG_SECTION:=		x11/misc
PKG_BUILDDEP:=		util-macros-host xkbcomp meson-host
PKG_SITES:=		http://www.x.org/releases/individual/data/xkeyboard-config/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,XKEYBOARD_CONFIG,xkeyboard-config,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

xkeyboard-config-install:
	${INSTALL_DIR} ${IDIR_XKEYBOARD_CONFIG}/usr/share/X11/xkb
	${CP} ${WRKINST}/usr/share/X11/xkb/* \
		${IDIR_XKEYBOARD_CONFIG}/usr/share/X11/xkb
	rm -rf ${IDIR_XKEYBOARD_CONFIG}/usr/share/X11/xkb/symbols/sun_vndr

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
