# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk
include ../rules.mk
include Makefile.inc

# disable SSP for libstdc++
ifeq ($(ADK_TARGET_LIB_MUSL),y)
TARGET_CFLAGS:=		$(filter-out -fstack-protector-all,$(TARGET_CFLAGS))
TARGET_CXXFLAGS:=	$(filter-out -fstack-protector-all,$(TARGET_CXXFLAGS))
endif

# disable lto for gcc
TARGET_CFLAGS:=		$(filter-out -flto,$(TARGET_CFLAGS))
TARGET_CXXFLAGS:=	$(filter-out -flto,$(TARGET_CXXFLAGS))

# for uClinux, we need to filter out some flags
ifeq ($(ADK_TARGET_UCLINUX),y)
TARGET_CFLAGS:=		$(filter-out -msep-data,$(TARGET_CFLAGS))
TARGET_CXXFLAGS:=	$(filter-out -msep-data,$(TARGET_CXXFLAGS))
endif

ifeq ($(ADK_TARGET_USE_STATIC_AND_SHARED_LIBS),y)
TARGET_CFLAGS:=		$(filter-out -static,$(TARGET_CFLAGS))
TARGET_CXXFLAGS:=	$(filter-out -static,$(TARGET_CXXFLAGS))
endif

GCC_CONFOPTS:=		--prefix=$(TOOLCHAIN_DIR)/usr \
			--with-bugurl="$(ADK_VENDOR_URL)" \
			--build=$(GNU_HOST_NAME) \
			--host=$(GNU_HOST_NAME) \
			--target=$(GNU_TARGET_NAME) \
			--with-gmp=$(STAGING_HOST_DIR)/usr \
			--with-mpfr=$(STAGING_HOST_DIR)/usr \
			--enable-__cxa_atexit \
			--with-system-zlib \
			--with-gnu-ld \
			--with-gnu-as \
			--disable-libsanitizer \
			--disable-install-libiberty \
			--disable-libitm \
			--disable-libmudflap \
			--disable-libgomp \
			--disable-libcc1 \
			--disable-libmpx \
			--disable-libcilkrts \
			--disable-libquadmath \
			--disable-libquadmath-support \
			--disable-decimal-float \
			--disable-libstdcxx-pch \
			--disable-ppl-version-check \
			--disable-cloog-version-check \
			--without-ppl \
			--without-cloog \
			--without-isl \
			--disable-werror \
			--disable-nls \
			--enable-obsolete

ifeq ($(ADK_TARGET_OS_LINUX),y)
ifeq ($(ADK_TARGET_LIB_UCLIBC_NG),y)
ifeq ($(ADK_TARGET_WITH_NPTL),y)
GCC_FINAL_CONFOPTS:=	--enable-tls --enable-threads --enable-libatomic
GCC_TLS_CONFOPTS:=	--enable-tls
endif
ifeq ($(ADK_TARGET_WITH_LT),y)
GCC_FINAL_CONFOPTS:=	--disable-tls --enable-threads --disable-libatomic
GCC_TLS_CONFOPTS:=	--disable-tls
endif
ifeq ($(ADK_TARGET_LIB_WITHOUT_THREADS)$(ADK_TARGET_WITHOUT_THREADS),y)
GCC_FINAL_CONFOPTS:=	--disable-tls --disable-threads --disable-libatomic
GCC_TLS_CONFOPTS:=	--disable-tls
endif
else
GCC_FINAL_CONFOPTS:=	--enable-tls --enable-threads --enable-libatomic
GCC_TLS_CONFOPTS:=	--enable-tls
endif
endif

ifeq ($(ADK_TARGET_OS_BAREMETAL),y)
GCC_FINAL_CONFOPTS:=	--disable-libatomic
endif

ifeq ($(ADK_TARGET_LIB_NEWLIB),y)
GCC_FINAL_CONFOPTS+=	--with-newlib
endif

ifeq ($(ADK_TARGET_USE_STATIC_LIBS_ONLY),y)
GCC_FINAL_CONFOPTS+=	--disable-shared
else
GCC_FINAL_CONFOPTS+=	--enable-shared --enable-cxx-flags='-fPIC'
endif

ifeq ($(ADK_TOOLCHAIN_WITH_SSP),y)
GCC_FINAL_CONFOPTS+=	--enable-libssp
else
GCC_FINAL_CONFOPTS+=	--disable-libssp
endif

ifeq ($(ADK_TOOLCHAIN_WITH_LTO),y)
GCC_CONFOPTS+=		--enable-lto
else
GCC_CONFOPTS+=		--disable-lto
endif

#
# architecture specific
#
ifneq ($(ADK_TARGET_GCC_CPU),)
GCC_CONFOPTS+=		--with-cpu=$(ADK_TARGET_GCC_CPU)
endif

ifneq ($(ADK_TARGET_GCC_ARCH),)
GCC_CONFOPTS+=		--with-arch=$(ADK_TARGET_GCC_ARCH)
endif

ifneq ($(ADK_TARGET_FLOAT),)
GCC_CONFOPTS+=		--with-float=$(ADK_TARGET_FLOAT)
endif

ifneq ($(ADK_TARGET_FPU),)
GCC_CONFOPTS+=		--with-fpu=$(ADK_TARGET_FPU)
endif

ifneq ($(ADK_TARGET_INSTRUCTION_SET),)
GCC_CONFOPTS+=		--with-mode=$(ADK_TARGET_INSTRUCTION_SET)
endif

ifneq ($(ADK_TARGET_NAN_MODE),)
GCC_CONFOPTS+=		--with-nan=$(ADK_TARGET_NAN_MODE)
endif

# .symver is broken for Blackfin, simple C++ apps fail to link
ifeq ($(ADK_TARGET_ARCH_BFIN),y)
GCC_CONFOPTS+=		--disable-symvers
endif

ifeq ($(ADK_TARGET_ARCH_CSKY),y)
GCC_CONFOPTS+=		--with-cskyabi=abiv2 --disable-multilib
ifeq ($(ADK_TARGET_LITTLE_ENDIAN),y)
GCC_CONFOPTS+=		--with-endian=little
else
GCC_CONFOPTS+=          --with-endian=big
endif
endif

ifeq ($(ADK_TARGET_ARCH_METAG),y)
GCC_CONFOPTS+=		--with-cpu=2.1 --enable-meta-default --disable-symvers
endif

ifeq ($(ADK_TARGET_CPU_CF),y)
GCC_CONFOPTS+=		--with-arch=cf --disable-multilib
endif

ifeq ($(ADK_TARGET_ARCH_NDS32),y)
GCC_CONFOPTS+=		--with-arch=v3
endif

ifeq ($(ADK_TARGET_ARCH_M68K)$(ADK_TARGET_ARCH_X86_64)$(ADK_TARGET_ARCH_X86),)
GCC_FINAL_CONFOPTS+=	--disable-biarch --disable-multilib
endif

ifeq ($(ADK_TARGET_ARCH_SH),y)

ifeq ($(ADK_TARGET_LITTLE_ENDIAN),y)
GCC_CONFOPTS+=		--with-endian=little
else
GCC_CONFOPTS+=          --with-endian=big
endif
ifeq ($(ADK_TARGET_BINFMT_FDPIC),y)
GCC_CONFOPTS+=          --enable-fdpic
endif

ifeq ($(ADK_TARGET_CPU_SH_J2),y)
GCC_CONFOPTS+=	--with-multilib-list=mj2
endif
ifeq ($(ADK_TARGET_CPU_SH_SH2),y)
GCC_CONFOPTS+=	--with-multilib-list=m2
endif
ifeq ($(ADK_TARGET_CPU_SH_SH2A),y)
GCC_CONFOPTS+=	--with-multilib-list=m2a,m2a-nofpu
endif
ifeq ($(ADK_TARGET_CPU_SH_SH3),y)
GCC_CONFOPTS+=	--with-multilib-list=m3
endif
ifeq ($(ADK_TARGET_CPU_SH_SH4),y)
GCC_CONFOPTS+=	--with-multilib-list=m4,m4-nofpu
endif
ifeq ($(ADK_TARGET_CPU_SH_SH4A),y)
GCC_CONFOPTS+=	--with-multilib-list=m4a,m4a-nofpu
endif

endif

ifeq ($(ADK_TARGET_ARCH_X86),y)
ifeq ($(ADK_TARGET_KERNEL_64),y)
GCC_FINAL_CONFOPTS+=	--enable-biarch --enable-targets=all --disable-multilib
else
GCC_FINAL_CONFOPTS+=    --disable-biarch --disable-multilib
endif
endif

ifeq ($(ADK_TARGET_ARCH_X86_64),y)
ifneq ($(ADK_TARGET_ABI_X32),)
GCC_CONFOPTS+=		--with-abi=x32 --enable-multilib
else
GCC_CONFOPTS+=		--disable-biarch --disable-multilib
endif
endif

ifeq ($(ADK_TARGET_ARCH_ALPHA),y)
GCC_CONFOPTS+=		--without-long-double-128
endif

ifeq ($(ADK_TARGET_ARCH_PPC),y)
GCC_CONFOPTS+=		--with-long-double-64 --enable-secureplt
endif

ifeq ($(ADK_TARGET_ARCH_PPC64),y)
ifeq ($(ADK_TARGET_LIB_GLIBC),y)
GCC_CONFOPTS+=		--with-long-double-128 --with-abi=elfv2
else
GCC_CONFOPTS+=		--without-long-double-128 --with-abi=elfv2
endif
endif

ifeq ($(ADK_TARGET_ARCH_S390),y)
GCC_CONFOPTS+=		--with-long-double-128
endif

ifneq ($(ADK_TARGET_ABI_MIPS64),)
GCC_CONFOPTS+=		--with-abi=${ADK_TARGET_ABI_MIPS64}
endif

ifneq ($(ADK_TARGET_ABI_RISCV),)
GCC_CONFOPTS+=		--with-abi=${ADK_TARGET_ABI_RISCV}
endif

ifeq (${ADK_MAKE_PARALLEL},y)
GCC_MAKEOPTS+=		-j${ADK_MAKE_JOBS}
endif

USE_LANG:=c
ifeq ($(ADK_TOOLCHAIN_WITH_CXX),y)
USE_LANG+=c++
endif
ifeq ($(ADK_TOOLCHAIN_WITH_OBJC),y)
USE_LANG+=objc
endif
ifeq ($(ADK_TOOLCHAIN_WITH_FORTRAN),y)
USE_LANG+=fortran
endif
ifeq ($(ADK_TOOLCHAIN_WITH_GO),y)
USE_LANG+=go
endif

LANGUAGES=$(shell echo ${USE_LANG} |tr ' ' ',')

include ${ADK_TOPDIR}/mk/buildhlp.mk

GCC_BUILD_DIR_INITIAL:=	$(WRKBUILD)-initial
GCC_BUILD_DIR_FINAL:=	$(WRKBUILD)-final

$(GCC_BUILD_DIR_INITIAL)/.configured:
ifeq ($(ADK_TARGET_ARCH_XTENSA),y)
	tar xf $(ADK_TOPDIR)/target/xtensa/overlay/xtensa_$(ADK_TARGET_CPU_TYPE).tar \
		--strip-components=1 -C $(WRKSRC) gcc
endif
	mkdir -p $(GCC_BUILD_DIR_INITIAL)
	# these symlinks are very important, do not remove
	rm -rf $(TOOLCHAIN_DIR)/usr/$(GNU_TARGET_NAME)/sys-include
	mkdir -p $(TOOLCHAIN_DIR)/usr/$(GNU_TARGET_NAME)
	(cd $(TOOLCHAIN_DIR)/usr/$(GNU_TARGET_NAME); \
		ln -s ../$(STAGING_HOST2TARGET)/usr/include sys-include)
	rm -rf ${TOOLCHAIN_DIR}/usr/$(GNU_TARGET_NAME)/lib
	(cd $(TOOLCHAIN_DIR)/usr/$(GNU_TARGET_NAME); \
		ln -s ../$(STAGING_HOST2TARGET)/usr/lib lib)
ifeq ($(ADK_TARGET_ARCH_SH),y)
ifeq ($(ADK_TARGET_CPU_SH_SH2),y)
	(cd ${STAGING_TARGET_DIR}/ && ln -sf . m2)
endif
ifeq ($(ADK_TARGET_CPU_SH_SH2A),y)
	(cd ${STAGING_TARGET_DIR}/ && ln -sf . m2a)
endif
ifeq ($(ADK_TARGET_CPU_SH_SH3),y)
	(cd ${STAGING_TARGET_DIR}/ && ln -sf . m3)
endif
ifeq ($(ADK_TARGET_CPU_SH_SH4),y)
	(cd ${STAGING_TARGET_DIR}/ && ln -sf . m4)
endif
ifeq ($(ADK_TARGET_CPU_SH_SH4A),y)
	(cd ${STAGING_TARGET_DIR}/ && ln -sf . m4a)
endif
endif
	$(SED) '/k prot/agcc_cv_libc_provides_ssp=yes' $(WRKBUILD)/gcc/configure
	cd $(GCC_BUILD_DIR_INITIAL); \
		PATH='$(TARGET_PATH)' \
		CC='$(HOST_CC)' \
		CXX='$(HOST_CXX)' \
		CFLAGS="-O0 -g0 -fomit-frame-pointer" \
		CXXFLAGS="-O0 -g0 -fomit-frame-pointer" \
		$(WRKBUILD)/configure \
			${GCC_CONFOPTS} \
			${GCC_TLS_CONFOPTS} \
			--enable-languages=c \
			--with-newlib \
			--disable-shared \
			--disable-threads \
			--disable-multilib \
			--without-headers
	touch $@

$(GCC_BUILD_DIR_INITIAL)/.compiled: $(GCC_BUILD_DIR_INITIAL)/.configured
ifeq ($(ADK_TOOLCHAIN_GCC_METAG),y)
	PATH='$(TARGET_PATH)' \
		$(MAKE) ${GCC_MAKEOPTS} -C $(GCC_BUILD_DIR_INITIAL) all-gcc
else
	PATH='$(TARGET_PATH)' \
		$(MAKE) ${GCC_MAKEOPTS} -C $(GCC_BUILD_DIR_INITIAL) all-gcc all-target-libgcc
endif
	touch $@

$(WRKBUILD)/.configured: $(GCC_BUILD_DIR_INITIAL)/.compiled
ifeq ($(ADK_TOOLCHAIN_GCC_METAG),y)
	PATH='$(TARGET_PATH)' \
		$(MAKE) -C $(GCC_BUILD_DIR_INITIAL) install-gcc
else
	PATH='$(TARGET_PATH)' \
		$(MAKE) -C $(GCC_BUILD_DIR_INITIAL) install-gcc install-target-libgcc
endif
	# required for newlib
	(cd $(TOOLCHAIN_DIR)/usr/bin && \
		ln -sf $(GNU_TARGET_NAME)-gcc $(GNU_TARGET_NAME)-cc \
	)
	touch $@

$(WRKBUILD)/.compiled:
	mkdir -p $(GCC_BUILD_DIR_FINAL)
	cd $(GCC_BUILD_DIR_FINAL); \
		PATH='$(TARGET_PATH)' \
		CC='$(HOST_CC)' \
		CXX='$(HOST_CXX)' \
		CFLAGS_FOR_TARGET='$(TARGET_CFLAGS)' \
		CXXFLAGS_FOR_TARGET='$(TARGET_CXXFLAGS)' \
		$(WRKBUILD)/configure \
			${GCC_CONFOPTS} \
			${GCC_FINAL_CONFOPTS} \
			--enable-languages=$(LANGUAGES) \
			--with-build-sysroot='$${prefix}/${STAGING_HOST2TARGET}' \
			--with-sysroot='$${prefix}/${STAGING_HOST2TARGET}'
	PATH='$(TARGET_PATH)' $(MAKE) -C $(GCC_BUILD_DIR_FINAL) configure-host
	cd $(GCC_BUILD_DIR_FINAL); \
		PATH='$(TARGET_PATH)' \
		$(MAKE) ${GCC_MAKEOPTS} all
	touch $@

$(WRKBUILD)/.installed: $(WRKBUILD)/.compiled
	cd $(GCC_BUILD_DIR_FINAL); \
		PATH='$(TARGET_PATH)' \
		$(MAKE) install
	# remove duplicate tools, convert hardlinks to symlinks
	set -e; \
	cd $(TOOLCHAIN_DIR)/usr/$(GNU_TARGET_NAME)/bin; \
		for app in ar as c++ g++ gcc ld ld.gold ld.bfd nm objcopy objdump ranlib strip; do \
			ln -sf ../../bin/$(GNU_TARGET_NAME)-$${app} $${app}; \
		done;
	(cd $(TOOLCHAIN_DIR)/usr/bin && \
		ln -sf $(GNU_TARGET_NAME)-gcc $(GNU_TARGET_NAME)-gcc-${PKG_VERSION} && \
		ln -sf $(GNU_TARGET_NAME)-g++ $(GNU_TARGET_NAME)-g++-${PKG_VERSION} \
	)
	touch $@

$(WRKBUILD)/.final:
ifeq ($(ADK_TARGET_CPU_CF),y)
	find $(STAGING_TARGET_DIR) -name libgcc.a -print | while read t; do $(GNU_TARGET_NAME)-ar dv "$t" _ctors.o; done
endif
	# cleanup unneeded docs
	rm -rf $(TOOLCHAIN_DIR)/usr/share
	# cleanup unneeded libtool files
	-find $(STAGING_TARGET_DIR) $(STAGING_HOST_DIR) -name \*.la -exec rm {} \;
	# strip target libs and host tools for toolchain builds in non-Debug mode
ifeq ($(ADK_DEBUG),)
	PATH="$(TARGET_PATH)" debug='0' prefix='${TARGET_CROSS}' ${BASH} ${SCRIPT_DIR}/rstrip.sh \
		$(STAGING_TARGET_DIR) $(TOOLCHAIN_DIR)/usr/lib/gcc/$(GNU_TARGET_NAME)
	debug='0' prefix=' ' ${BASH} ${SCRIPT_DIR}/rstrip.sh $(TOOLCHAIN_DIR)/usr/bin
endif
	touch $@

include ${ADK_TOPDIR}/mk/toolchain.mk
