# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		tiff
PKG_VERSION:=		4.3.0
PKG_RELEASE:=		1
PKG_HASH:=		0e46e5acb087ce7d1ac53cf4f56a09b221537fc86dfc5daaad1c2e89e1b37ac8
PKG_DESCR:=		library for reading/writing tiff images
PKG_SECTION:=		libs/image
PKG_NEEDS:=		c++
PKG_BUILDDEP:=		cmake-host zlib xz
PKG_URL:=		http://simplesystems.org/libtiff/
PKG_SITES:=		http://download.osgeo.org/libtiff/
PKG_LIBNAME:=		libtiff
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LIBTIFF,libtiff,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIG_STYLE:=		cmake

libtiff-install:
	${INSTALL_DIR} ${IDIR_LIBTIFF}/usr/lib
	${CP} ${WRKINST}/usr/lib/libtiff.so* ${IDIR_LIBTIFF}/usr/lib/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
