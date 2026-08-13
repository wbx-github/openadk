# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		expat
PKG_VERSION:=		2.8.3
PKG_RELEASE:=		1
PKG_HASH:=		f6256df90c906773d344da084402b7d3e4f22ed41b1a59c989098a83d3ea0c85
PKG_DESCR:=		xml parsing library
PKG_SECTION:=		libs/data
PKG_SITES:=		https://github.com/libexpat/libexpat/releases/download/R_2_8_3/
PKG_LIBNAME:=		libexpat
PKG_OPTS:=		dev

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,LIBEXPAT,libexpat,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,LIBEXPAT,libexpat,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

ifeq ($(ADK_TARGET_USE_STATIC_AND_SHARED_LIBS),y)
TARGET_CFLAGS:=	$(filter-out -static,$(TARGET_CFLAGS))
TARGET_LDFLAGS:=$(filter-out -static,$(TARGET_LDFLAGS))
endif

CONFIGURE_ARGS+=	--without-docbook \
			--without-tests

libexpat-install:
	${INSTALL_DIR} ${IDIR_LIBEXPAT}/usr/lib
	${CP} ${WRKINST}/usr/lib/libexpat.so* ${IDIR_LIBEXPAT}/usr/lib/

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
