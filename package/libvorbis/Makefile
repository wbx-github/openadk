# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		libvorbis
PKG_VERSION:=		1.3.5
PKG_RELEASE:=		1
PKG_HASH:=		54f94a9527ff0a88477be0a71c0bab09a4c3febe0ed878b24824906cd4b0e1d1
PKG_DESCR:=		vorbis general audio compression codec library
PKG_SECTION:=		libs/audio
PKG_BUILDDEP:=		libogg
PKG_URL:=		http://www.xiph.org/vorbis/
PKG_SITES:=		http://downloads.xiph.org/releases/vorbis/
PKG_OPTS:=		dev

PKG_SUBPKGS:=		LIBVORBIS LIBVORBISENC

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LIBVORBIS,libvorbis,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))
$(eval $(call PKG_template,LIBVORBISENC,libvorbisenc,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIGURE_ENV+=		LIBS="-lm -logg"
CONFIGURE_ARGS+=	--with-ogg="${STAGING_TARGET_DIR}/usr" \
			--with-ogg-includes="${STAGING_TARGET_DIR}/usr/include" \
			--with-ogg-libraries="${STAGING_TARGET_DIR}/usr/lib"

libvorbis-install:
	${INSTALL_DIR} ${IDIR_LIBVORBIS}/usr/lib
	${CP} ${WRKINST}/usr/lib/libvorbis.so* ${IDIR_LIBVORBIS}/usr/lib
	${CP} ${WRKINST}/usr/lib/libvorbisfile.so* ${IDIR_LIBVORBIS}/usr/lib

libvorbisenc-install:
	${INSTALL_DIR} ${IDIR_LIBVORBISENC}/usr/lib
	${CP} ${WRKINST}/usr/lib/libvorbisenc.so* ${IDIR_LIBVORBISENC}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
