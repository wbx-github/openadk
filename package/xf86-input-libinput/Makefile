# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		xf86-input-libinput
PKG_VERSION:=		1.5.0
PKG_RELEASE:=		1
PKG_HASH:=		2524c35f196554ea11aef3bba1cf324759454e1d49f98ac026ace2f6003580e6
PKG_DESCR:=		x11 driver for libinput
PKG_SECTION:=		x11/drivers
PKG_DEPENDS:=		xorg-server libudev libevdev mtdev libinput
PKG_BUILDDEP:=		xorg-server eudev libevdev mtdev libinput
PKG_SITES:=		https://www.x.org/releases/individual/driver/

PKG_CFLINE_XF86_INPUT_LIBINPUT:= depends on ADK_TARGET_WITH_INPUT

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,XF86_INPUT_LIBINPUT,xf86-input-libinput,$(PKG_VERSION)-$(PKG_RELEASE),${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

xf86-input-libinput-install:
	${INSTALL_DIR} ${IDIR_XF86_INPUT_LIBINPUT}/usr/lib/xorg/modules/input
	${CP} ${WRKINST}/usr/lib/xorg/modules/input/*.so \
		${IDIR_XF86_INPUT_LIBINPUT}/usr/lib/xorg/modules/input/
	${INSTALL_DIR} ${IDIR_XF86_INPUT_LIBINPUT}/usr/share/X11/xorg.conf.d
	${CP} ${WRKINST}/usr/share/X11/xorg.conf.d/40-libinput.conf \
		${IDIR_XF86_INPUT_LIBINPUT}/usr/share/X11/xorg.conf.d

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
