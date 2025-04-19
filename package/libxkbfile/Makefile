# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libxkbfile
PKG_VERSION:=		1.0.9
PKG_RELEASE:=		1
PKG_HASH:=		95df50570f38e720fb79976f603761ae6eff761613eb56f258c3cb6bab4fd5e3
PKG_DESCR:=		keyboard configuration extension library
PKG_SECTION:=		x11/libs
PKG_BUILDDEP:=		kbproto libX11
PKG_SITES:=		http://www.x.org/releases/individual/lib/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,LIBXKBFILE,libxkbfile,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,LIBXKBFILE,libxkbfile,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

libxkbfile-install:
	${INSTALL_DIR} ${IDIR_LIBXKBFILE}/usr/lib
	${CP} ${WRKINST}/usr/lib/libxkbfile.so* ${IDIR_LIBXKBFILE}/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
