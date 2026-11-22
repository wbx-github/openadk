# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/toolchain/llvm/Makefile.inc

PKG_NAME:=		compiler-rt

# build out of the shared llvm source tree, extracted by toolchain/llvm
WRKDIR=			${LLVM_WRKDIR}
WRKDIST=		${LLVM_SRCDIR}
WRKBUILD=		${WRKDIR}/build-compiler-rt
# never wipe the shared tree from here
TOOLCHAIN_CLEAN_DIR=	${WRKBUILD}
