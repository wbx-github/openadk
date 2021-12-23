# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libXrandr
PKG_VERSION:=		1.5.1
PKG_RELEASE:=		1
PKG_HASH:=		2baa7fb3eca78fe7e11a09b373ba898b717f7eeba4a4bfd68187e04b4789b0d3
PKG_DESCR:=		xrandr library
PKG_SECTION:=		x11/libs
PKG_BUILDDEP:=		randrproto libXrender libXext
PKG_SITES:=		http://www.x.org/releases/individual/lib/
PKG_LIBNAME:=		libxrandr
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBXRANDR,libxrandr,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIGURE_ARGS+= 	--disable-malloc0returnsnull

libxrandr-install:
	${INSTALL_DIR} ${IDIR_LIBXRANDR}/usr/lib
	${CP} ${WRKINST}/usr/lib/libXrandr.so* ${IDIR_LIBXRANDR}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
