# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		xkbcomp
PKG_VERSION:=		1.4.7
PKG_RELEASE:=		1
PKG_HASH:=		0a288114e5f44e31987042c79aecff1ffad53a8154b8ec971c24a69a80f81f77
PKG_DESCR:=		x11 keyboard compiler
PKG_SECTION:=		x11/misc
PKG_BUILDDEP:=		libxkbfile libX11
PKG_DEPENDS:=		libxkbfile libx11
HOST_BUILDDEP:=		libxkbfile-host
PKG_SITES:=		http://xorg.freedesktop.org/releases/individual/app/

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,XKBCOMP,xkbcomp,$(PKG_VERSION)-${PKG_RELEASE}))
$(eval $(call PKG_template,XKBCOMP,xkbcomp,$(PKG_VERSION)-$(PKG_RELEASE),${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

xkbcomp-install:
	${INSTALL_DIR} ${IDIR_XKBCOMP}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/xkbcomp ${IDIR_XKBCOMP}/usr/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
