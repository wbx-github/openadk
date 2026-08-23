# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk
include ${ADK_TOPDIR}/toolchain/gcc/Makefile.inc

PKG_NAME:=		libstdcxx
PKG_DESCR:=		c++ support library
PKG_SECTION:=		base/libs
PKG_OPTS:=		noremove
NO_DISTFILES:=		1

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LIBSTDCXX,libstdcxx,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

do-install:
ifeq ($(ADK_TARGET_BINFMT_FLAT)$(ADK_TARGET_USE_STATIC_LIBS_ONLY)$(ADK_TARGET_ARCH_METAG),)
	${INSTALL_DIR} ${IDIR_LIBSTDCXX}/usr/${ADK_TARGET_LIBC_PATH}
ifeq ($(ADK_TARGET_CPU_SH_SH3),y)
	$(CP) ${STAGING_TARGET_DIR}/usr/${ADK_TARGET_LIBC_PATH}/!m3/libstdc++.so* \
		${IDIR_LIBSTDCXX}/usr/${ADK_TARGET_LIBC_PATH}
endif
ifeq ($(ADK_TARGET_CPU_SH_SH4),y)
	$(CP) ${STAGING_TARGET_DIR}/usr/${ADK_TARGET_LIBC_PATH}/!m4/libstdc++.so* \
		${IDIR_LIBSTDCXX}/usr/${ADK_TARGET_LIBC_PATH}
endif
	$(CP) ${STAGING_TARGET_DIR}/usr/${ADK_TARGET_LIBC_PATH}/libstdc++.so* \
		${IDIR_LIBSTDCXX}/usr/${ADK_TARGET_LIBC_PATH}
	-@rm ${IDIR_LIBSTDCXX}/usr/${ADK_TARGET_LIBC_PATH}/libstdc++.so.*-gdb.py 2>/dev/null
endif

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
