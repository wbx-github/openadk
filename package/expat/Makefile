# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		expat
PKG_VERSION:=		2.8.1
PKG_RELEASE:=		1
PKG_HASH:=		10b195ee78160a908388180a8fe3603d4e9a12f4755fbf5f3816b23a9d750da0
PKG_DESCR:=		xml parsing library
PKG_SECTION:=		libs/data
PKG_SITES:=		https://github.com/libexpat/libexpat/releases/download/R_2_8_1/
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
