# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk
include ${ADK_TOPDIR}/toolchain/gcc/Makefile.inc

PKG_NAME:=		libgcc
PKG_DESCR:=		gcc library
PKG_SECTION:=		base/libs
PKG_OPTS:=		noremove

PKG_DFLT_LIBGCC:=	y if !ADK_APPLIANCE_TOOLCHAIN

NO_DISTFILES:=		1

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LIBGCC,libgcc,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

libgcc-install:
	$(INSTALL_DIR) ${IDIR_LIBGCC}/$(ADK_TARGET_LIBC_PATH)
ifeq ($(ADK_TARGET_USE_STATIC_LIBS_ONLY),)
ifeq ($(ADK_TARGET_ARCH_SH),y)
ifeq ($(ADK_TARGET_CPU_SH_SH3),y)
	${CP} ${STAGING_TARGET_DIR}/usr/lib/!m3*/libgcc*.so* ${IDIR_LIBGCC}/$(ADK_TARGET_LIBC_PATH)
endif
ifeq ($(ADK_TARGET_CPU_SH_SH4),y)
	${CP} ${STAGING_TARGET_DIR}/usr/lib/!m4*/libgcc*.so* ${IDIR_LIBGCC}/$(ADK_TARGET_LIBC_PATH)
endif
else
ifeq ($(ADK_TARGET_ARCH_AVR32),)
ifeq ($(ADK_TARGET_BINFMT_FLAT),)
	-${CP} ${STAGING_TARGET_DIR}/usr/lib/libgcc*.so* ${IDIR_LIBGCC}/$(ADK_TARGET_LIBC_PATH)
endif
endif
endif
endif 

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
