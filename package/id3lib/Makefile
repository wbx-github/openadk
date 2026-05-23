# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		id3lib
PKG_VERSION:=		3.8.3
PKG_RELEASE:=		2
PKG_HASH:=		2749cc3c0cd7280b299518b1ddf5a5bcfe2d1100614519b68702230e26c7d079
PKG_DESCR:=		id3 tagging library
PKG_SECTION:=		libs/audio
PKG_DEPENDS:=		zlib
PKG_BUILDDEP:=		zlib
PKG_NEEDS:=		c++
PKG_URL:=		http://id3lib.sourceforge.net/
PKG_SITES:=		https://sourceforge.net/projects/id3lib/files/id3lib/$(PKG_VERSION)/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,ID3LIB,id3lib,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

TARGET_CFLAGS+=		-fPIC
TARGET_LDFLAGS+=	-shared
CONFIGURE_ARGS+=	--enable-cxx-warnings=no

ifeq ($(ADK_TARGET_USE_SSP),y)
LIBRARIES+=		-lssp -fstack-protector
endif

id3lib-install:
	${INSTALL_DIR} ${IDIR_ID3LIB}/usr/lib
	${CP} ${WRKINST}/usr/lib/libid3-*.so* ${IDIR_ID3LIB}/usr/lib/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
