# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk
include ${ADK_TOPDIR}/toolchain/llvm/Makefile.inc

PKG_NAME:=		llvm-libgcc
PKG_DESCR:=		llvm libgcc replacement library
PKG_SECTION:=		base/libs
PKG_OPTS:=		noremove

NO_DISTFILES:=		1

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LLVM_LIBGCC,llvm-libgcc,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

llvm-libgcc-install:
	${INSTALL_DIR} ${IDIR_LLVM_LIBGCC}/$(ADK_TARGET_LIBC_PATH)
	${CP} ${STAGING_TARGET_DIR}/usr/lib/libgcc*.so* ${IDIR_LLVM_LIBGCC}/$(ADK_TARGET_LIBC_PATH)
	${CP} ${STAGING_TARGET_DIR}/usr/lib/libunwind.so* ${IDIR_LLVM_LIBGCC}/$(ADK_TARGET_LIBC_PATH)

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
