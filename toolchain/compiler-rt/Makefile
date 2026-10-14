# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include ../rules.mk
include Makefile.inc

WRKDIST=$(WRKDIR)/llvm-project-llvmorg-$(PKG_VERSION)

include ${ADK_TOPDIR}/mk/buildhlp.mk

ifeq ($(ADK_TARGET_LIB_GLIBC),y)
LLVM_LIBC:=gnu$(ADK_TARGET_ABI)
endif
ifeq ($(ADK_TARGET_LIB_MUSL),y)
LLVM_LIBC:=musl$(ADK_TARGET_ABI)
endif
ifeq ($(ADK_TARGET_LIB_UCLIBC_NG),y)
LLVM_LIBC:=gnu$(ADK_TARGET_ABI)
endif
ifeq ($(ADK_TARGET_ARCH_ARM),y)
LLVM_ASM_FLAGS:=-march=armv7-a
endif

$(WRKBUILD)/.configured:
	cd $(WRKBUILD) && \
	cmake -G Ninja -S compiler-rt -B build \
    		-DCMAKE_BUILD_TYPE=Release \
		-DCMAKE_INSTALL_PREFIX=/usr \
		-DCMAKE_C_COMPILER=$(TOOLCHAIN_DIR)/usr/bin/clang \
		-DCMAKE_C_COMPILER_TARGET=$(GNU_TARGET_NAME) \
		-DCMAKE_CXX_COMPILER=$(TOOLCHAIN_DIR)/usr/bin/clang++ \
		-DCMAKE_CXX_COMPILER_TARGET=$(GNU_TARGET_NAME) \
		-DCMAKE_EXE_LINKER_FLAGS="-fuse-ld=lld" \
		-DCMAKE_SHARED_LINKER_FLAGS="-fuse-ld=lld" \
		-DCMAKE_MODULE_LINKER_FLAGS="-fuse-ld=lld" \
		-DCMAKE_SYSROOT=$(STAGING_TARGET_DIR) \
		-DCMAKE_ASM_COMPILER=$(TOOLCHAIN_DIR)/usr/bin/clang \
		-DCMAKE_ASM_COMPILER_TARGET=$(GNU_TARGET_NAME) \
		-DCMAKE_ASM_FLAGS="--target=$(GNU_TARGET_NAME) $(LLVM_ASM_FLAGS)" \
		-DCOMPILER_RT_INSTALL_PATH=/usr/lib/clang/23 \
		-DCOMPILER_RT_BUILD_BUILTINS=ON \
		-DCOMPILER_RT_BUILTINS_HIDE_SYMBOLS=OFF \
		-DCOMPILER_RT_BUILD_CRT=ON \
		-DCOMPILER_RT_BUILD_ORC=OFF \
		-DCOMPILER_RT_BUILD_SANITIZERS=OFF \
		-DCOMPILER_RT_BUILD_XRAY=OFF \
		-DCOMPILER_RT_BUILD_LIBFUZZER=OFF \
		-DCOMPILER_RT_BUILD_PROFILE=OFF \
		-DCOMPILER_RT_BUILD_MEMPROF=OFF \
		-DCOMPILER_RT_DEFAULT_TARGET_ONLY=ON \
		-DLLVM_ENABLE_PER_TARGET_RUNTIME_DIR=ON \
		-DCMAKE_TRY_COMPILE_TARGET_TYPE=STATIC_LIBRARY
	touch $@

$(WRKBUILD)/.compiled: $(WRKBUILD)/.configured
	cd $(WRKBUILD) && \
		ninja -C build builtins crt
	touch $@

$(WRKBUILD)/.installed: $(WRKBUILD)/.compiled
	cd $(WRKBUILD) && \
		DESTDIR=$(TOOLCHAIN_DIR) ninja -C build install-builtins install-crt
	cd $(TOOLCHAIN_DIR)/usr/lib/clang/23/lib/$(ADK_TARGET_CPU_ARCH)-unknown-linux-$(LLVM_LIBC)/ && \
		ln -sf clang_rt.crtbegin.o crtbegin.o
	cd $(TOOLCHAIN_DIR)/usr/lib/clang/23/lib/$(ADK_TARGET_CPU_ARCH)-unknown-linux-$(LLVM_LIBC)/ && \
		ln -sf clang_rt.crtbegin.o crtbeginS.o
	cd $(TOOLCHAIN_DIR)/usr/lib/clang/23/lib/$(ADK_TARGET_CPU_ARCH)-unknown-linux-$(LLVM_LIBC)/ && \
		ln -sf clang_rt.crtend.o crtend.o
	cd $(TOOLCHAIN_DIR)/usr/lib/clang/23/lib/$(ADK_TARGET_CPU_ARCH)-unknown-linux-$(LLVM_LIBC)/ && \
		ln -sf clang_rt.crtend.o crtendS.o
	touch $@

include ${ADK_TOPDIR}/mk/toolchain.mk
