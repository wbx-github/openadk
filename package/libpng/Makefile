# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		libpng
PKG_VERSION:=		1.6.55
PKG_RELEASE:=		1
PKG_HASH:=		d925722864837ad5ae2a82070d4b2e0603dc72af44bd457c3962298258b8e82d
PKG_DESCR:=		library for reading/writing png images
PKG_SECTION:=		libs/image
PKG_DEPENDS:=		zlib
PKG_BUILDDEP:=		zlib
PKG_URL:=		http://www.libpng.org/pub/png/libpng.html
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=libpng/}
PKG_OPTS:=		dev

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,LIBPNG,libpng,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,LIBPNG,libpng,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

HOST_STYLE:=		auto

libpng-install:
	${INSTALL_DIR} ${IDIR_LIBPNG}/usr/lib
	${CP} ${WRKINST}/usr/lib/libpng*.so* ${IDIR_LIBPNG}/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
