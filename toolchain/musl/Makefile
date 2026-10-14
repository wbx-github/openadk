# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include ../rules.mk
include Makefile.inc
include ${ADK_TOPDIR}/mk/buildhlp.mk

ifeq ($(ADK_BUILD_COMPILER_GCC),y)
ifeq ($(ADK_TARGET_CPU_ARCH),ppc)
GNU_TARGET_NAME:= $(subst ppc,powerpc,$(GNU_TARGET_NAME))
endif
ifeq ($(ADK_TARGET_CPU_ARCH),ppc64)
GNU_TARGET_NAME:= $(subst ppc64,powerpc64,$(GNU_TARGET_NAME))
endif
ifeq ($(ADK_TARGET_CPU_ARCH),ppc64le)
GNU_TARGET_NAME:= $(subst ppc64le,powerpc64le,$(GNU_TARGET_NAME))
endif
endif

# not yet possible
TARGET_CFLAGS:=		$(filter-out -fstack-protector-all,$(TARGET_CFLAGS))
TARGET_LDFLAGS:=	$(filter-out -fstack-protector-all,$(TARGET_LDFLAGS))
# don't use fast-math for C library
TARGET_CFLAGS:=         $(filter-out -ffast-math,$(TARGET_CFLAGS))

ifeq ($(ADK_BUILD_COMPILER_LLVM),y)
TARGET_LDFLAGS+=	$(TOOLCHAIN_DIR)/usr/lib/clang/23/lib/$(ADK_TARGET_CPU_ARCH)-unknown-linux-musl$(ADK_TARGET_ABI)/libclang_rt.builtins.a
endif

$(WRKBUILD)/.configured:
	(cd $(WRKBUILD); PATH='$(HOST_PATH)' \
		CROSS_COMPILE='$(TARGET_CROSS)' \
		CC='$(TARGET_CC)' \
		CFLAGS='$(TARGET_CFLAGS)' \
		./configure --prefix=/usr \
		--target=$(GNU_TARGET_NAME) \
		--disable-gcc-wrapper \
	)
	PATH='$(HOST_PATH)' $(MAKE) -C $(WRKBUILD) \
		CC='$(TARGET_CC)' CFLAGS='$(TARGET_CFLAGS)' DESTDIR=$(STAGING_TARGET_DIR) install-headers
	touch $@

$(WRKBUILD)/.compiled:
	PATH='$(HOST_PATH)' $(MAKE) -C $(WRKBUILD) \
		CC='$(TARGET_CC)' CFLAGS='$(TARGET_CFLAGS)' LDFLAGS='$(TARGET_LDFLAGS)' all
	touch $@

$(WRKBUILD)/.installed: $(WRKBUILD)/.compiled
	PATH='$(HOST_PATH)' $(MAKE) -C $(WRKBUILD) \
		CC='$(TARGET_CC)' CFLAGS='$(TARGET_CFLAGS)' DESTDIR=$(STAGING_TARGET_DIR) install
	touch $@

include ${ADK_TOPDIR}/mk/toolchain.mk
