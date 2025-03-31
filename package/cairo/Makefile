# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		cairo
PKG_VERSION:=		1.18.2
PKG_RELEASE:=		1
PKG_HASH:=		a62b9bb42425e844cc3d6ddde043ff39dbabedd1542eba57a2eb79f85889d45a
PKG_DESCR:=		graphics library
PKG_SECTION:=		libs/image
PKG_DEPENDS:=		fontconfig libfreetype libx11 pixman
PKG_DEPENDS+=		libxrender libpng
PKG_BUILDDEP:=		pixman freetype fontconfig libX11 libXrender glib
PKG_BUILDDEP+=		libXext libpng
HOST_BUILDDEP:=		libpng-host pixman-host freetype-host fontconfig-host
PKG_URL:=		http://cairographics.org/
PKG_SITES:=		http://cairographics.org/releases/
PKG_OPTS:=		dev

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,CAIRO,cairo,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,CAIRO,cairo,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

MESON_FLAGS+=		-Dtests=disabled

HOST_STYLE:=		meson
CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

cairo-install:
	${INSTALL_DIR} ${IDIR_CAIRO}/usr/lib/cairo
	${CP} ${WRKINST}/usr/lib/libcairo*.so* ${IDIR_CAIRO}/usr/lib
	${CP} ${WRKINST}/usr/lib/cairo/*.so* ${IDIR_CAIRO}/usr/lib/cairo

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
