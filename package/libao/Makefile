# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		libao
PKG_VERSION:=		1.2.0
PKG_RELEASE:=		1
PKG_HASH:=		03ad231ad1f9d64b52474392d63c31197b0bc7bd416e58b1c10a329a5ed89caf
PKG_DESCR:=		cross platform audio library
PKG_SECTION:=		libs/audio
PKG_DEPENDS:=		alsa-lib
PKG_BUILDDEP:=		alsa-lib
PKG_URL:=		http://www.xiph.org/ao
PKG_SITES:=		http://downloads.xiph.org/releases/ao/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LIBAO,libao,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIGURE_ARGS+=	--enable-alsa \
			--disable-esd \
			--disable-arts \
			--disable-nas \
			--disable-polyp

libao-install:
	${INSTALL_DIR} ${IDIR_LIBAO}/usr/lib/ao/plugins-4
	${CP} ${WRKINST}/usr/lib/libao.so* ${IDIR_LIBAO}/usr/lib/
	${CP} ${WRKINST}/usr/lib/ao/plugins-4/*.so \
		${IDIR_LIBAO}/usr/lib/ao/plugins-4

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
