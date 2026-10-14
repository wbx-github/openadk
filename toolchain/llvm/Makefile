# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include ../rules.mk
include Makefile.inc

WRKDIST=$(WRKDIR)/llvm-project-llvmorg-$(PKG_VERSION)

include ${ADK_TOPDIR}/mk/buildhlp.mk

ifeq ($(ADK_TARGET_ARCH_AARCH64),y)
LLVM_ARCH:=AArch64
endif
ifeq ($(ADK_TARGET_ARCH_ARM),y)
LLVM_ARCH:=ARM
endif
ifeq ($(ADK_TARGET_ARCH_MIPS),y)
LLVM_ARCH:=Mips
endif
ifeq ($(ADK_TARGET_ARCH_PPC),y)
LLVM_ARCH:=PowerPC
endif
ifeq ($(ADK_TARGET_ARCH_RISCV64),y)
LLVM_ARCH:=RISCV
endif
ifeq ($(ADK_TARGET_ARCH_X86_64),y)
LLVM_ARCH:=X86
endif

$(WRKBUILD)/.configured:
	cd $(WRKBUILD) && \
	cmake -G Ninja -S llvm -B build \
    		-DCMAKE_BUILD_TYPE=Release \
		-DCMAKE_INSTALL_PREFIX=/usr \
    		-DLLVM_ENABLE_PROJECTS="clang;lld" \
    		-DLLVM_TARGETS_TO_BUILD="$(LLVM_ARCH)" \
		-DCLANG_DEFAULT_LINKER=lld
	touch $@

$(WRKBUILD)/.compiled: $(WRKBUILD)/.configured
	cd $(WRKBUILD) && \
		ninja -C build
	touch $@

$(WRKBUILD)/.installed: $(WRKBUILD)/.compiled
	cd $(WRKBUILD) && \
		DESTDIR=$(TOOLCHAIN_DIR) ninja -C build install
	# fake binutils via symlinks to llvm tools
	cd $(TOOLCHAIN_DIR)/usr/bin && ln -sf llvm-ar $(GNU_TARGET_NAME)-ar
	cd $(TOOLCHAIN_DIR)/usr/bin && ln -sf llvm-nm $(GNU_TARGET_NAME)-nm
	cd $(TOOLCHAIN_DIR)/usr/bin && ln -sf llvm-ranlib $(GNU_TARGET_NAME)-ranlib
	cd $(TOOLCHAIN_DIR)/usr/bin && ln -sf llvm-objcopy $(GNU_TARGET_NAME)-objcopy
	cd $(TOOLCHAIN_DIR)/usr/bin && ln -sf llvm-objdump $(GNU_TARGET_NAME)-objdump
	cd $(TOOLCHAIN_DIR)/usr/bin && ln -sf llvm-readelf $(GNU_TARGET_NAME)-readelf
	cd $(TOOLCHAIN_DIR)/usr/bin && ln -sf llvm-strip $(GNU_TARGET_NAME)-strip
	touch $@

$(WRKBUILD)/.final:
	touch $@

include ${ADK_TOPDIR}/mk/toolchain.mk
