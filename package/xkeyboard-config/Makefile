# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		xkeyboard-config
PKG_VERSION:=		2.45
PKG_RELEASE:=		1
PKG_HASH:=		169e075a92d957a57787c199e84e359df2931b7196c1c5b4a3d576ee6235a87c
PKG_DESCR:=		keyboard config
PKG_SECTION:=		x11/misc
PKG_BUILDDEP:=		util-macros-host xkbcomp-host xkbcomp meson-host
PKG_SITES:=		http://www.x.org/releases/individual/data/xkeyboard-config/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,XKEYBOARD_CONFIG,xkeyboard-config,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

xkeyboard-config-install:
	${INSTALL_DIR} ${IDIR_XKEYBOARD_CONFIG}/usr/share/X11
	${INSTALL_DIR} ${IDIR_XKEYBOARD_CONFIG}/usr/share/xkeyboard-config-2
	${CP} ${WRKINST}/usr/share/xkeyboard-config-2/* \
		${IDIR_XKEYBOARD_CONFIG}/usr/share/xkeyboard-config-2
	(cd $(IDIR_XKEYBOARD_CONFIG)/usr/share/X11 && ln -sf ../xkeyboard-config-2 xkb)

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
