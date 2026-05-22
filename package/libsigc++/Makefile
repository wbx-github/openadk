# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		libsigc++
PKG_VERSION:=		3.6.0
PKG_RELEASE:=		1
PKG_HASH:=		c3d23b37dfd6e39f2e09f091b77b1541fbfa17c4f0b6bf5c89baef7229080e17
PKG_DESCR:=		callback framework for c++
PKG_SECTION:=		libs/misc
PKG_SITES:=		https://download.gnome.org/sources/libsigc++/3.6/
PKG_OPTS:=		dev

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LIBSIGCXX,libsigc++,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

libsigc++-install:
	${INSTALL_DIR} ${IDIR_LIBSIGCXX}/usr/lib
	${CP} ${WRKINST}/usr/lib/libsigc-3.0.so.* ${IDIR_LIBSIGCXX}/usr/lib/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
