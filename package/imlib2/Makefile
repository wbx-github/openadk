# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		imlib2
PKG_VERSION:=		1.4.7
PKG_RELEASE:=		1
PKG_HASH:=		48e98337a560d8904f685447f41c43914fec1f8cd3745a9fd86cba9fd24a6563
PKG_DESCR:=		advanced replacement library for libraries like libxpm
PKG_SECTION:=		libs/image
PKG_DEPENDS:=		libfreetype zlib libpng libtiff libx11 libxext
PKG_BUILDDEP:=		freetype zlib libpng libtiff libX11 libXext
PKG_URL:=		http://www.enlightenment.org/
PKG_SITES:=		https://sourceforge.net/projects/enlightenment/files/imlib2-src/$(PKG_VERSION)/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,IMLIB2,imlib2,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

imlib2-install:
	$(INSTALL_DIR) $(IDIR_IMLIB2)/usr/lib/imlib2/{filters,loaders}
	${CP} $(WRKINST)/usr/lib/libImlib2.so* $(IDIR_IMLIB2)/usr/lib
	${CP} $(WRKINST)/usr/lib/imlib2/filters/*.so \
		$(IDIR_IMLIB2)/usr/lib/imlib2/filters
	${CP} $(WRKINST)/usr/lib/imlib2/loaders/*.so \
		$(IDIR_IMLIB2)/usr/lib/imlib2/loaders

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
