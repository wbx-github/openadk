# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk
include ${ADK_TOPDIR}/toolchain/gcc/Makefile.inc

PKG_NAME:=		libatomic
PKG_DESCR:=		gcc atomic library
PKG_SECTION:=		base/libs
PKG_OPTS:=		noremove

PKG_DFLT_LIBATOMIC:=	y if !ADK_APPLIANCE_TOOLCHAIN

NO_DISTFILES:=		1

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LIBATOMIC,libatomic,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

libatomic-install:
	$(INSTALL_DIR) ${IDIR_LIBATOMIC}/$(ADK_TARGET_LIBC_PATH)
ifeq ($(ADK_TARGET_USE_STATIC_LIBS_ONLY),)
	# XXX: properly install libatomic
	${CP} ${TOOLCHAIN_BUILD_DIR}/w-gcc*/gcc-*-final/*/libatomic/.libs/libatomic*.so* ${IDIR_LIBATOMIC}/$(ADK_TARGET_LIBC_PATH)
endif

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
