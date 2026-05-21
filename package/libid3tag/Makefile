# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		libid3tag
PKG_VERSION:=		0.15.1b
PKG_RELEASE:=		3
PKG_HASH:=		63da4f6e7997278f8a3fef4c6a372d342f705051d1eeb6a46a86b03610e26151
PKG_DESCR:=		id3 tag manipulation library
PKG_SECTION:=		libs/audio
PKG_DEPENDS:=		zlib
PKG_BUILDDEP:=		zlib
PKG_SITES:=		https://sourceforge.net/projects/mad/files/libid3tag/$(PKG_VERSION)/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LIBID3TAG,libid3tag,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIGURE_ARGS+=	--disable-debugging \
			--disable-profiling

pre-install:
	${INSTALL_DIR} ${WRKINST}/usr/lib/pkgconfig
	${CP} ./files/id3tag.pc ${WRKINST}/usr/lib/pkgconfig

libid3tag-install:
	${INSTALL_DIR} ${IDIR_LIBID3TAG}/usr/lib
	${CP} ${WRKINST}/usr/lib/libid3tag.so* ${IDIR_LIBID3TAG}/usr/lib/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
