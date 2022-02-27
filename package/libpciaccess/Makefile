# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libpciaccess
PKG_VERSION:=		0.16
PKG_RELEASE:=		1
PKG_HASH:=		84413553994aef0070cf420050aa5c0a51b1956b404920e21b81e96db6a61a27
PKG_DESCR:=		pci access library
PKG_SECTION:=		x11/libs
PKG_SITES:=		http://www.x.org/releases/individual/lib/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBPCIACCESS,libpciaccess,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

libpciaccess-install:
	${INSTALL_DIR} ${IDIR_LIBPCIACCESS}/usr/lib
	${CP} ${WRKINST}/usr/lib/libpciaccess.so* \
		${IDIR_LIBPCIACCESS}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
