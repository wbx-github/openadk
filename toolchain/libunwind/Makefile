# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include ../rules.mk
include Makefile.inc

include ${ADK_TOPDIR}/mk/buildhlp.mk

$(WRKBUILD)/.configured:
	# required for llvm-libgcc
	echo "--target=$(GNU_TARGET_NAME)" > $(TOOLCHAIN_DIR)/usr/bin/clang.cfg
	mkdir -p $(WRKBUILD) && \
	cmake -G Ninja -S $(WRKSRC)/runtimes -B $(WRKBUILD) \
	    -DCMAKE_BUILD_TYPE=Release \
	    -DCMAKE_INSTALL_PREFIX=/usr \
	    -DLLVM_ENABLE_RUNTIMES=llvm-libgcc \
	    -DLLVM_LIBGCC_EXPLICIT_OPT_IN=Yes \
	    -DCMAKE_C_COMPILER=$(TOOLCHAIN_DIR)/usr/bin/clang \
	    -DCMAKE_C_COMPILER_TARGET=$(GNU_TARGET_NAME) \
	    -DCMAKE_CXX_COMPILER=$(TOOLCHAIN_DIR)/usr/bin/clang \
	    -DCMAKE_CXX_COMPILER_TARGET=$(GNU_TARGET_NAME) \
	    -DCMAKE_ASM_COMPILER=$(TOOLCHAIN_DIR)/usr/bin/clang \
	    -DCMAKE_ASM_COMPILER_TARGET=$(GNU_TARGET_NAME) \
            -DCMAKE_ASM_FLAGS="--target=$(GNU_TARGET_NAME)" \
	    -DCMAKE_SYSROOT=$(STAGING_TARGET_DIR) \
	    -DCMAKE_EXE_LINKER_FLAGS="-fuse-ld=lld" \
	    -DCMAKE_SHARED_LINKER_FLAGS="-fuse-ld=lld" \
	    -DCMAKE_MODULE_LINKER_FLAGS="-fuse-ld=lld" \
	    -DCMAKE_C_FLAGS="--target=$(GNU_TARGET_NAME) -rtlib=compiler-rt" \
	    -DCMAKE_CXX_FLAGS="--target=$(GNU_TARGET_NAME) -rtlib=compiler-rt" \
	    -DCOMPILER_RT_BUILD_BUILTINS=ON \
	    -DCOMPILER_RT_BUILTINS_HIDE_SYMBOLS=OFF \
	    -DCOMPILER_RT_BUILD_CRT=OFF \
	    -DCOMPILER_RT_BUILD_MEMPROF=OFF \
	    -DCOMPILER_RT_BUILD_CTX_PROFILE=OFF \
	    -DCOMPILER_RT_BUILD_ORC=OFF \
	    -DCOMPILER_RT_BUILD_SANITIZERS=OFF \
	    -DCOMPILER_RT_BUILD_XRAY=OFF \
	    -DCOMPILER_RT_BUILD_LIBFUZZER=OFF \
	    -DCOMPILER_RT_BUILD_PROFILE=OFF \
	    -DCOMPILER_RT_BUILD_MEMPROF=OFF \
	    -DCOMPILER_RT_DEFAULT_TARGET_ONLY=ON \
	    -DLIBUNWIND_ENABLE_SHARED=ON \
	    -DLIBUNWIND_ENABLE_STATIC=ON \
	    -DLIBUNWIND_USE_COMPILER_RT=ON
	touch $@

$(WRKBUILD)/.compiled: $(WRKBUILD)/.configured
	ninja -C $(WRKBUILD)
	touch $@

$(WRKBUILD)/.installed: $(WRKBUILD)/.compiled
	DESTDIR="$(STAGING_TARGET_DIR)" ninja -C $(WRKBUILD) install
	touch $@

include ${ADK_TOPDIR}/mk/toolchain.mk
