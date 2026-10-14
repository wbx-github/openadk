# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include ../rules.mk
include Makefile.inc

WRKDIST=$(WRKDIR)/llvm-project-llvmorg-$(PKG_VERSION)

include ${ADK_TOPDIR}/mk/buildhlp.mk

$(WRKBUILD)/.configured:
	cd $(WRKBUILD) && \
	cmake -G Ninja -S libunwind -B build-libunwind \
	    -DCMAKE_BUILD_TYPE=Release \
	    -DCMAKE_INSTALL_PREFIX=/usr \
	    -DCMAKE_C_COMPILER=$(TOOLCHAIN_DIR)/usr/bin/clang \
	    -DCMAKE_C_COMPILER_TARGET=$(GNU_TARGET_NAME) \
	    -DCMAKE_CXX_COMPILER=$(TOOLCHAIN_DIR)/usr/bin/clang \
	    -DCMAKE_CXX_COMPILER_TARGET=$(GNU_TARGET_NAME) \
            -DCMAKE_ASM_FLAGS="--target=$(GNU_TARGET_NAME)" \
	    -DCMAKE_SYSROOT=$(STAGING_TARGET_DIR) \
	    -DCMAKE_EXE_LINKER_FLAGS="-fuse-ld=lld" \
	    -DCMAKE_SHARED_LINKER_FLAGS="-fuse-ld=lld" \
	    -DCMAKE_MODULE_LINKER_FLAGS="-fuse-ld=lld" \
	    -DCMAKE_C_FLAGS="--target=$(GNU_TARGET_NAME) -rtlib=compiler-rt" \
	    -DCMAKE_CXX_FLAGS="--target=$(GNU_TARGET_NAME) -rtlib=compiler-rt" \
	    -DLIBUNWIND_ENABLE_SHARED=OFF \
	    -DLIBUNWIND_ENABLE_STATIC=ON \
	    -DLIBUNWIND_ENABLE_CXX=OFF \
	    -DCMAKE_TRY_COMPILE_TARGET_TYPE=STATIC_LIBRARY \
	    -DLIBUNWIND_USE_COMPILER_RT=ON
	touch $@

$(WRKBUILD)/.compiled: $(WRKBUILD)/.configured
	cd $(WRKBUILD) && \
		ninja -C build-libunwind
	touch $@

$(WRKBUILD)/.installed: $(WRKBUILD)/.compiled
	cd $(WRKBUILD) && \
		DESTDIR="$(TOOLCHAIN_DIR)" ninja -C build-libunwind install
	touch $@

include ${ADK_TOPDIR}/mk/toolchain.mk
