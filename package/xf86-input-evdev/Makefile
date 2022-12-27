# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		xf86-input-evdev
PKG_VERSION:=		2.10.4
PKG_RELEASE:=		1
PKG_HASH:=		1a1b69daf41eac965f1cf0be721ebc340b2860c066147cb483f0e8f0ab7dd6a2
PKG_DESCR:=		x11 driver for evdev
PKG_SECTION:=		x11/drivers
PKG_DEPENDS:=		xorg-server libudev libevdev mtdev
PKG_BUILDDEP:=		xorg-server eudev libevdev mtdev
PKG_SITES:=		http://www.x.org/releases/individual/driver/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_CFLINE_XF86_INPUT_EVDEV:= depends on ADK_TARGET_WITH_INPUT

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,XF86_INPUT_EVDEV,xf86-input-evdev,$(PKG_VERSION)-$(PKG_RELEASE),${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

xf86-input-evdev-install:
	${INSTALL_DIR} ${IDIR_XF86_INPUT_EVDEV}/usr/lib/xorg/modules/input
	${CP} ${WRKINST}/usr/lib/xorg/modules/input/evdev_drv.so \
		${IDIR_XF86_INPUT_EVDEV}/usr/lib/xorg/modules/input/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
