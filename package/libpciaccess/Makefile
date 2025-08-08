# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libpciaccess
PKG_VERSION:=		0.18.1
PKG_RELEASE:=		1
PKG_HASH:=		4af43444b38adb5545d0ed1c2ce46d9608cc47b31c2387fc5181656765a6fa76
PKG_DESCR:=		pci access library
PKG_SECTION:=		x11/libs
PKG_SITES:=		http://xorg.freedesktop.org/releases/individual/lib/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBPCIACCESS,libpciaccess,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

libpciaccess-install:
	${INSTALL_DIR} ${IDIR_LIBPCIACCESS}/usr/lib
	${CP} ${WRKINST}/usr/lib/libpciaccess.so* \
		${IDIR_LIBPCIACCESS}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
