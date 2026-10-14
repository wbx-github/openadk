# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		libunwind
ifeq ($(ADK_TOOLCHAIN_LLVM_23),y)
PKG_VERSION:=		23.1.3
PKG_HASH:=		791b560dee8f65fdf7b19ad5db0b4ac627467824d8b687957d8a437b806103f0
PKG_SITES:=		https://github.com/llvm/llvm-project/archive/refs/tags/
PKG_RELEASE:=		1
DISTFILES:=		llvmorg-${PKG_VERSION}.tar.gz
endif
