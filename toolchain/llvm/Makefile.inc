# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		llvm
ifeq ($(ADK_TOOLCHAIN_LLVM_23),y)
PKG_VERSION:=		23.1.6
PKG_HASH:=		66b37a51976c46ad86f49a2304c4dfd64be971f858846dfffaa8a32632474bb8
PKG_SITES:=		https://github.com/llvm/llvm-project/archive/refs/tags/
PKG_RELEASE:=		1
DISTFILES:=		llvmorg-${PKG_VERSION}.tar.gz
endif

# all LLVM sub-projects share one tarball and one extracted source tree
FULLDISTDIR=		${DL_DIR}/llvm
LLVM_WRKDIR=		${TOOLCHAIN_BUILD_DIR}/w-llvm-${PKG_VERSION}-${PKG_RELEASE}
LLVM_SRCDIR=		${LLVM_WRKDIR}/llvm-project-llvmorg-${PKG_VERSION}
