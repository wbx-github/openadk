# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		flac
PKG_VERSION:=		1.5.0
PKG_RELEASE:=		1
PKG_HASH:=		f2c1c76592a82ffff8413ba3c4a1299b6c7ab06c734dee03fd88630485c2b920
PKG_DESCR:=		free lossless audio codec utility
PKG_SECTION:=		mm/audio
PKG_DEPENDS:=		libflac
PKG_URL:=		https://xiph.org/flac/
PKG_SITES:=		https://ftp.osuosl.org/pub/xiph/releases/flac/
PKG_LIBNAME:=		libflac
PKG_OPTS:=		dev

PKG_SUBPKGS:=		FLAC LIBFLAC
PKGSD_LIBFLAC:=		free lossless audio codec library
PKGSC_LIBFLAC:=		libs/audio

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,FLAC,flac,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,LIBFLAC,libflac,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIGURE_ARGS+=	--enable-asm-optimizations \
			--disable-stack-smash-protection \
			--disable-xmms-plugin \
			--disable-cpplibs \
			--disable-ogg

flac-install:
	${INSTALL_DIR} ${IDIR_FLAC}/usr/bin
	${CP} ${WRKINST}/usr/bin/flac \
		${IDIR_FLAC}/usr/bin

libflac-install:
	${INSTALL_DIR} ${IDIR_LIBFLAC}/usr/lib
	${CP} ${WRKINST}/usr/lib/libFLAC.so* \
		${IDIR_LIBFLAC}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
