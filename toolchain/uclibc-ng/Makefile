# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

_IN_CVTC=		1

include $(ADK_TOPDIR)/rules.mk
include ../rules.mk
include Makefile.inc
include ${ADK_TOPDIR}/mk/buildhlp.mk

# disable LTO
TARGET_CFLAGS:=	$(filter-out -flto,$(TARGET_CFLAGS))
# handled by uClibc-ng makefiles
TARGET_CFLAGS:=	$(filter-out -fstack-protector-all,$(TARGET_CFLAGS))
TARGET_LDFLAGS:=$(filter-out -fstack-protector-all,$(TARGET_LDFLAGS))
# don't use fast-math for C library
TARGET_CFLAGS:=	$(filter-out -ffast-math,$(TARGET_CFLAGS))

ifeq ($(ADK_TARGET_USE_STATIC_AND_SHARED_LIBS),y)
TARGET_CFLAGS:=	$(filter-out -static,$(TARGET_CFLAGS))
TARGET_LDFLAGS:=$(filter-out -static,$(TARGET_LDFLAGS))
endif

ifeq ($(ADK_BUILD_COMPILER_GCC),y)
ifeq ($(ADK_TARGET_HARD_FLOAT),y)
ifeq ($(ADK_TARGET_HARD_FLOAT_SP),y)
ifeq ($(ADK_TARGET_HARD_FLOAT_DP),y)
ifeq ($(ADK_TARGET_ARCH_ARM),y)
TARGET_CFLAGS+=		-Wa,-mfloat-abi=hard
endif
endif
endif
ifeq ($(ADK_TARGET_ARCH_MIPS),y)
TARGET_CFLAGS+=		-Wa,-mhard-float
endif
endif

ifeq ($(ADK_TARGET_SOFT_FLOAT),y)
ifeq ($(ADK_TARGET_ARCH_ARM),y)
TARGET_CFLAGS+=		-Wa,-mfloat-abi=soft
endif
ifeq ($(ADK_TARGET_ARCH_MIPS),y)
TARGET_CFLAGS+=		-Wa,-msoft-float
endif
endif
endif

ifeq (${ADK_MAKE_PARALLEL},y)
UCLIBC_MAKEOPTS+=	-j${ADK_MAKE_JOBS}
endif

$(WRKBUILD)/.configured: $(WRKBUILD)/.prepared
	PATH='$(HOST_PATH)' sed -e 's^KERNEL_HEADERS.*$$KERNEL_HEADERS=\"${STAGING_TARGET_DIR}/usr/include\"' \
	    $(ADK_TOPDIR)/target/$(ADK_TARGET_ARCH)/uclibc-ng.config >${WRKBUILD}/.config
	$(SED) 's^.*\(CROSS_COMPILER_PREFIX\).*^\1=\"$(TARGET_CROSS)\"^' ${WRKBUILD}/.config
ifeq ($(ADK_TARGET_ENDIAN),little)
	$(SED) 's/.*\(ARCH_LITTLE_ENDIAN\).*/\1=y/' ${WRKBUILD}/.config
	$(SED) 's/.*\(ARCH_WANTS_LITTLE_ENDIAN\).*/\1=y/' ${WRKBUILD}/.config
	$(SED) 's/.*\(ARCH_BIG_ENDIAN\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(ARCH_WANTS_BIG_ENDIAN\).*/# \1 is not set/' ${WRKBUILD}/.config
else
	$(SED) 's/.*\(ARCH_BIG_ENDIAN\).*/\1=y/' ${WRKBUILD}/.config
	$(SED) 's/.*\(ARCH_WANTS_BIG_ENDIAN\).*/\1=y/' ${WRKBUILD}/.config
	$(SED) 's/.*\(ARCH_LITTLE_ENDIAN\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(ARCH_WANTS_LITTLE_ENDIAN\).*/# \1 is not set/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_SOFT_FLOAT),y)
	$(SED) 's/.*\(UCLIBC_HAS_FPU\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_HAS_SOFT_FLOAT\).*/#\1=y/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_HARD_FLOAT),y)
	$(SED) 's/.*\(UCLIBC_HAS_FPU\).*/\1=y/' ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_HAS_SOFT_FLOAT\).*/# \1 is not set/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_HARD_FLOAT_SP),y)
	$(SED) 's/.*\(UCLIBC_HAS_FPU\).*/\1=y/' ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_HAS_SOFT_FLOAT\).*/# \1 is not set/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_HARD_FLOAT_DP),y)
	$(SED) 's/.*\(UCLIBC_HAS_FPU\).*/\1=y/' ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_HAS_SOFT_FLOAT\).*/# \1 is not set/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_BINFMT_FDPIC),y)
	$(SED) 's/.*\(UCLIBC_FORMAT_FDPIC_ELF\).*/\1=y/' ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_FORMAT_ELF\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_FORMAT_FLAT\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_FORMAT_FLAT_SEP_DATA\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_FORMAT_SHARED_FLAT\).*/# \1 is not set/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_BINFMT_FLAT),y)
	echo '# UCLIBC_FORMAT_FLAT is not set' >> ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_FORMAT_FLAT\).*/\1=y/' ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_FORMAT_FLAT_SEP_DATA\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_FORMAT_SHARED_FLAT\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_FORMAT_FDPIC_ELF\).*/# \1 is not set/' ${WRKBUILD}/.config
ifeq ($(ADK_TARGET_BINFMT_FLAT_SEP_DATA),y)
	echo '# UCLIBC_FORMAT_FLAT_SEP_DATA is not set' >> ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_FORMAT_FLAT_SEP_DATA\).*/\1=y/' ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_FORMAT_FLAT \).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_FORMAT_SHARED_FLAT\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_FORMAT_FDPIC_ELF\).*/# \1 is not set/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_BINFMT_FLAT_SHARED),y)
	echo '# UCLIBC_FORMAT_SHARED_FLAT is not set' >> ${WRKBUILD}/.config
	echo '# HAVE_NO_SHARED is not set' >> ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_FORMAT_SHARED_FLAT\).*/\1=y/' ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_FORMAT_FLAT \).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_FORMAT_FLAT_SEP_DATA\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_FORMAT_FDPIC_ELF\).*/# \1 is not set/' ${WRKBUILD}/.config
endif
endif
ifeq ($(ADK_TARGET_LIBC_WITH_LIBICONV),y)
	$(SED) 's/.*\(UCLIBC_HAS_LIBICONV\).*/\1=y/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_LIBC_WITH_LIBINTL),y)
	$(SED) 's/.*\(UCLIBC_HAS_LIBINTL\).*/\1=y/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_LIBC_WITH_LOCALE),y)
	$(SED) 's/.*\(UCLIBC_HAS_LOCALE\).*/\1=y/' ${WRKBUILD}/.config
	echo 'UCLIBC_HAS_XLOCALE=y' >> ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_UCLINUX),y)
	$(SED) 's/.*\(ARCH_USE_MMU\).*/# \1 is not set/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_WITH_MMU),)
	$(SED) 's/.*\(ARCH_USE_MMU\).*/# \1 is not set/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_WITH_NPTL),y)
	$(SED) 's/.*\(UCLIBC_HAS_THREADS_NATIVE\).*/\1=y/' ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_HAS_TLS\).*/\1=y/' ${WRKBUILD}/.config
	$(SED) 's/.*\(PTHREADS_DEBUG_SUPPORT\).*/\1=y/' ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_HAS_LINUXTHREADS\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(HAS_NO_THREADS\).*/# \1 is not set/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_WITH_LT),y)
	echo '# UCLIBC_HAS_THREADS is not set' >> ${WRKBUILD}/.config
	echo '# UCLIBC_HAS_LINUXTHREADS is not set' >> ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_HAS_THREADS_NATIVE\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_HAS_TLS\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_HAS_THREADS\).*/\1=y/' ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_HAS_LINUXTHREADS\).*/\1=y/' ${WRKBUILD}/.config
	$(SED) 's/.*\(HAS_NO_THREADS\).*/# \1 is not set/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_LIB_WITHOUT_THREADS)$(ADK_TARGET_WITHOUT_THREADS),y)
	$(SED) 's/.*\(UCLIBC_HAS_LINUXTHREADS\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_HAS_THREADS_NATIVE\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(UCLIBC_HAS_TLS\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(PTHREADS_DEBUG_SUPPORT\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(HAS_NO_THREADS\).*/\1=y/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_USE_STATIC_LIBS_ONLY)$(ADK_TARGET_BINFMT_FLAT),)
	$(SED) 's/.*\(HAVE_SHARED\).*/\1=y/' ${WRKBUILD}/.config
else
	$(SED) 's/.*\(HAVE_SHARED\).*/# \1 is not set/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_USE_GNU_HASHSTYLE),y)
	$(SED) 's/.*\(LDSO_GNU_HASH_SUPPORT\).*/\1=y/' ${WRKBUILD}/.config
else
	$(SED) 's/.*\(LDSO_GNU_HASH_SUPPORT\).*/# \1 is not set/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_USE_SSP),y)
	$(SED) 's,.*UCLIBC_HAS_SSP,UCLIBC_HAS_SSP=y,' ${WRKBUILD}/.config
	echo "UCLIBC_HAS_SSP_COMPAT=n" >> ${WRKBUILD}/.config
	echo "SSP_QUICK_CANARY=n" >> ${WRKBUILD}/.config
	echo "UCLIBC_BUILD_SSP=y" >> ${WRKBUILD}/.config
endif
ifeq ($(ADK_DEBUG),y)
	$(SED) 's/.*\(DODEBUG\).*/\1=y/' ${WRKBUILD}/.config
endif

#
# architecture specific options
#

# arc
ifeq ($(ADK_TARGET_ARCH_ARC),y)
ifeq ($(ADK_TARGET_CPU_ARC_ARC700),y)
	$(SED) 's/.*\(CONFIG_ARC_PAGE_SIZE_16K\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_ARC_PAGE_SIZE_4K\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_ARC_PAGE_SIZE_8K\).*/\1=y/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_CPU_ARC_ARCHS),y)
	$(SED) 's/.*\(CONFIG_ARC_PAGE_SIZE_16K\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_ARC_PAGE_SIZE_4K\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_ARC_PAGE_SIZE_8K\).*/\1=y/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_CPU_ARC_ARC32),y)
	$(SED) 's/.*\(CONFIG_ARC_PAGE_SIZE_16K\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_ARC_PAGE_SIZE_8K\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_ARC_PAGE_SIZE_4K\).*/\1=y/' ${WRKBUILD}/.config
endif
endif

# arm
ifeq ($(ADK_TARGET_ARCH_ARM),y)
ifeq ($(ADK_TARGET_WITH_MMU),)
	$(SED) 's/.*\(DOPIC\).*/# \1 is not set/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_ARCH_ARM_WITH_THUMB),y)
	$(SED) 's/.*\(UCLIBC_HAS_CONTEXT_FUNCS\).*/# \1 is not set/' ${WRKBUILD}/.config
endif
endif

# cris
ifeq ($(ADK_TARGET_ARCH_CRIS),y)
ifeq ($(ADK_TARGET_CPU_CRIS_CRISV32),y)
	$(SED) 's/.*\(CONFIG_CRIS=\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_CRISV32\).*/\1=y/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_CPU_CRIS_CRISV10),y)
	$(SED) 's/.*\(CONFIG_CRIS=\).*/\1=y/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_CRISV32\).*/# \1 is not set/' ${WRKBUILD}/.config
endif
endif

# h8300
ifeq ($(ADK_TARGET_ARCH_H8300),y)
ifeq ($(ADK_TARGET_CPU_H8300H),y)
	$(SED) 's/.*\(CONFIG_H8S\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_H8300H\).*/\1=y/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_CPU_H8S),y)
	$(SED) 's/.*\(CONFIG_H8S\).*/\1=y/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_H8300H\).*/# \1 is not set/' ${WRKBUILD}/.config
endif
endif

# sh
ifeq ($(ADK_TARGET_ARCH_SH),y)
ifeq ($(ADK_TARGET_CPU_SH_SH4A),y)
	$(SED) 's/.*\(CONFIG_SH2A\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_SH2\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_SH3\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_SH4=\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_SH4A\).*/\1=y/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_CPU_SH_SH4),y)
	$(SED) 's/.*\(CONFIG_SH2A\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_SH2\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_SH3\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_SH4A\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_SH4\).*/\1=y/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_CPU_SH_SH3),y)
	$(SED) 's/.*\(UCLIBC_HAS_FPU\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_SH2A\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_SH2\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_SH4\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_SH4A\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_SH3\).*/\1=y/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_CPU_SH_SH2)$(ADK_TARGET_CPU_SH_J2),y)
	$(SED) 's/.*\(UCLIBC_HAS_FPU\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_SH2A\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_SH3\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_SH4\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_SH4A\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_SH2\).*/\1=y/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_CPU_SH_SH2A),y)
	$(SED) 's/.*\(UCLIBC_HAS_FPU\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_SH2\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_SH3\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_SH4\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_SH4A\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_SH2A\).*/\1=y/' ${WRKBUILD}/.config
endif
endif

# x86
ifeq ($(ADK_TARGET_ARCH_X86),y)
ifeq ($(ADK_TARGET_CPU_X86_I486),y)
	$(SED) 's/.*\(CONFIG_686\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_586\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_486\).*/\1=y/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_CPU_X86_I586),y)
	$(SED) 's/.*\(CONFIG_686\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_586\).*/\1=y/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_486\).*/# \1 is not set/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_CPU_X86_I686),y)
	$(SED) 's/.*\(CONFIG_686\).*/\1=y/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_586\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_486\).*/# \1 is not set/' ${WRKBUILD}/.config
endif
endif

# m68k
ifeq ($(ADK_TARGET_ARCH_M68K),y)
ifeq ($(ADK_TARGET_WITH_MMU),)
ifeq ($(ADK_TARGET_BINFMT_FLAT_ONE)$(ADK_TARGET_BINFMT_FLAT_SEP_DATA),y)
	$(SED) 's/.*\(DOPIC\).*/# \1 is not set/' ${WRKBUILD}/.config
endif
endif
endif

# mips/mips64 NaN
ifeq ($(ADK_TARGET_ARCH_MIPS_WITH_NAN_2008),y)
	$(SED) 's/.*\(CONFIG_MIPS_NAN_LEGACY\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_MIPS_NAN_2008\).*/\1=y/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_ARCH_MIPS_WITH_NAN_LEGACY),y)
	$(SED) 's/.*\(CONFIG_MIPS_NAN_2008\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_MIPS_NAN_LEGACY\).*/\1=y/' ${WRKBUILD}/.config
endif

# mips64 abi
ifeq ($(ADK_TARGET_ARCH_MIPS64),y)
ifeq ($(ADK_TARGET_ABI_N64),y)
	$(SED) 's/.*\(CONFIG_MIPS_N64_ABI\).*/\1=y/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_MIPS_O32_ABI\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_MIPS_N32_ABI\).*/# \1 is not set/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_ABI_N32),y)
	$(SED) 's/.*\(CONFIG_MIPS_N32_ABI\).*/\1=y/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_MIPS_O32_ABI\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_MIPS_N64_ABI\).*/# \1 is not set/' ${WRKBUILD}/.config
endif
ifeq ($(ADK_TARGET_ABI_O32),y)
	$(SED) 's/.*\(CONFIG_MIPS_O32_ABI\).*/\1=y/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_MIPS_N32_ABI\).*/# \1 is not set/' ${WRKBUILD}/.config
	$(SED) 's/.*\(CONFIG_MIPS_N64_ABI\).*/# \1 is not set/' ${WRKBUILD}/.config
endif
endif
	echo N|PATH='$(HOST_PATH)' $(MAKE) -C $(WRKBUILD) \
		HOSTCC="$(HOST_CC)" \
		CC='$(TARGET_CC)' \
		PREFIX=$(STAGING_TARGET_DIR) \
		DEVEL_PREFIX=/usr/ \
		RUNTIME_PREFIX=$(STAGING_TARGET_DIR) \
		UCLIBC_EXTRA_CFLAGS="$(TARGET_CFLAGS)" \
		UCLIBC_EXTRA_LDFLAGS="$(TARGET_LDFLAGS)" \
		oldconfig
ifeq ($(ADK_TARGET_LIBC_WITH_LOCALE),y)
	$(SED) 's/.*\(UCLIBC_BUILD_MINIMAL_LOCALES\).*/\1="$(ADK_RUNTIME_DEFAULT_LOCALE)"/' ${WRKBUILD}/.config
endif
	touch $@

$(WRKBUILD)/.compiled: $(WRKBUILD)/.configured
	PATH='$(HOST_PATH)' $(MAKE) $(UCLIBC_MAKEOPTS) -C $(WRKBUILD) \
		ARCH="$(ADK_TARGET_ARCH)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		HOSTCC="$(HOST_CC)" \
		PREFIX=$(STAGING_TARGET_DIR) \
		DEVEL_PREFIX=/usr/ \
		RUNTIME_PREFIX=/ \
		UCLIBC_EXTRA_CFLAGS="$(TARGET_CFLAGS)" \
		UCLIBC_EXTRA_LDFLAGS="$(TARGET_LDFLAGS)" \
		VERBOSE=1 \
		all
ifeq ($(ADK_TARGET_LIBC_UTILS),y)
	PATH='$(HOST_PATH)' $(MAKE) $(UCLIBC_MAKEOPTS) -C $(WRKBUILD) \
		ARCH="$(ADK_TARGET_ARCH)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		HOSTCC="$(HOST_CC)" \
		PREFIX=$(STAGING_TARGET_DIR) \
		DEVEL_PREFIX=/usr/ \
		RUNTIME_PREFIX=/ \
		UCLIBC_EXTRA_CFLAGS="$(TARGET_CFLAGS)" \
		UCLIBC_EXTRA_LDFLAGS="$(TARGET_LDFLAGS)" \
		VERBOSE=1 \
		utils
endif
	touch $@

$(WRKBUILD)/.installed: $(WRKBUILD)/.compiled
	PATH='$(HOST_PATH)' $(MAKE) -C $(WRKBUILD) \
		ARCH="$(ADK_TARGET_ARCH)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		HOSTCC="$(HOST_CC)" \
		PREFIX=$(STAGING_TARGET_DIR) \
		DEVEL_PREFIX=/usr/ \
		RUNTIME_PREFIX=/ \
		UCLIBC_EXTRA_CFLAGS="$(TARGET_CFLAGS)" \
		UCLIBC_EXTRA_LDFLAGS="$(TARGET_LDFLAGS)" \
		VERBOSE=1 \
		install_runtime install_dev
ifeq ($(ADK_TARGET_LIBC_UTILS),y)
	PATH='$(HOST_PATH)' $(MAKE) -C $(WRKBUILD) \
		ARCH="$(ADK_TARGET_ARCH)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		HOSTCC="$(HOST_CC)" \
		PREFIX=$(STAGING_TARGET_DIR) \
		DEVEL_PREFIX=/usr/ \
		RUNTIME_PREFIX=/ \
		UCLIBC_EXTRA_CFLAGS="$(TARGET_CFLAGS)" \
		UCLIBC_EXTRA_LDFLAGS="$(TARGET_LDFLAGS)" \
		VERBOSE=1 \
		install_utils
endif
	touch $@

include ${ADK_TOPDIR}/mk/toolchain.mk
