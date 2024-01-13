# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

CP=			cp -fpR
INSTALL_DIR=		install -d -m0755
INSTALL_DATA=		install -m0644
INSTALL_BIN=		install -m0755
INSTALL_SCRIPT=		install -m0755
MAKEFLAGS=		$(EXTRA_MAKEFLAGS)
BUILD_USER=		$(shell id -un)
BUILD_GROUP=		$(shell id -gn)
ADK_SUFFIX:=		${ADK_TARGET_SYSTEM}
ifneq ($(ADK_TARGET_LIBC),)
ADK_SUFFIX:=		$(ADK_SUFFIX)_$(ADK_TARGET_LIBC)
endif
ifneq ($(ADK_TARGET_CPU_TYPE),)
ADK_SUFFIX:=		$(ADK_SUFFIX)_$(ADK_TARGET_CPU_TYPE)
endif
ifneq ($(ADK_TARGET_ENDIAN_SUFFIX),)
ADK_SUFFIX:=		$(ADK_SUFFIX)$(ADK_TARGET_ENDIAN_SUFFIX)
endif
ifneq ($(ADK_TARGET_FLOAT),)
ADK_SUFFIX:=		$(ADK_SUFFIX)_$(ADK_TARGET_FLOAT)
endif
ifneq ($(ADK_TARGET_ABI),)
ADK_SUFFIX:=		$(ADK_SUFFIX)_$(ADK_TARGET_ABI)
endif
ifneq ($(ADK_TARGET_BINFMT),)
ADK_SUFFIX:=		$(ADK_SUFFIX)_$(ADK_TARGET_BINFMT)
endif
ifneq ($(ADK_TARGET_INSTRUCTION_SET),)
ADK_SUFFIX:=		$(ADK_SUFFIX)_$(ADK_TARGET_INSTRUCTION_SET)
endif
ifeq ($(ADK_TARGET_WITH_MMU),)
ADK_SUFFIX:=		$(ADK_SUFFIX)_nommu
endif

# some global dirs
BASE_DIR:=		$(ADK_TOPDIR)
ifeq ($(ADK_DL_DIR),)
DL_DIR?=		$(BASE_DIR)/dl
else
DL_DIR?=		$(ADK_DL_DIR)
endif
SCRIPT_DIR:=		$(BASE_DIR)/scripts
STAGING_HOST_DIR:=	${BASE_DIR}/host_${GNU_HOST_NAME}
HOST_BUILD_DIR:=	${BASE_DIR}/host_build_${GNU_HOST_NAME}
TOOLCHAIN_DIR:=		${BASE_DIR}/toolchain_${ADK_SUFFIX}

# dirs for cleandir
FW_DIR_PFX:=		$(BASE_DIR)/firmware
BUILD_DIR_PFX:=		$(BASE_DIR)/build_*
STAGING_PKG_DIR_PFX:=	${BASE_DIR}/pkg_*
STAGING_TARGET_DIR_PFX:=${BASE_DIR}/target_*
TOOLCHAIN_DIR_PFX=	$(BASE_DIR)/toolchain_*
STAGING_HOST_DIR_PFX:=	${BASE_DIR}/host_*
TARGET_DIR_PFX:=	$(BASE_DIR)/root_*

TARGET_DIR:=		$(BASE_DIR)/root_${ADK_SUFFIX}
FW_DIR:=		$(BASE_DIR)/firmware/${ADK_SUFFIX}
BUILD_DIR:=		${BASE_DIR}/build_${ADK_SUFFIX}
STAGING_TARGET_DIR:=	${BASE_DIR}/target_${ADK_SUFFIX}
STAGING_PKG_DIR:=	${BASE_DIR}/pkg_${ADK_SUFFIX}
STAGING_HOST2TARGET:=	../../target_${ADK_SUFFIX}
TOOLCHAIN_BUILD_DIR=	$(BASE_DIR)/toolchain_build_${ADK_SUFFIX}
PACKAGE_DIR:=		$(FW_DIR)/packages
SCRIPT_TARGET_DIR:=	${STAGING_TARGET_DIR}/scripts

# PATH variables
TARGET_PATH=		${SCRIPT_DIR}:${STAGING_TARGET_DIR}/scripts:${TOOLCHAIN_DIR}/usr/bin:${STAGING_HOST_DIR}/usr/bin:${_PATH}
HOST_PATH=		${SCRIPT_DIR}:${TOOLCHAIN_DIR}/usr/bin:${STAGING_HOST_DIR}/usr/bin:${STAGING_HOST_DIR}/usr/sbin:${_PATH}
AUTOTOOL_PATH=		${TOOLCHAIN_DIR}/usr/bin:${STAGING_HOST_DIR}/usr/bin:${STAGING_TARGET_DIR}/scripts:${_PATH}

ifeq ($(ADK_TARGET_UCLINUX),y)
ADK_TARGET_LINUXTYPE:=	uclinux
else
ADK_TARGET_LINUXTYPE:=	linux
endif

GNU_TARGET_NAME:=	$(ADK_TARGET_CPU_ARCH)-$(ADK_VENDOR)-$(ADK_TARGET_LINUXTYPE)-$(ADK_TARGET_SUFFIX)
ifeq ($(ADK_TARGET_ARCH_C6X),y)
GNU_TARGET_NAME:=	ti$(ADK_TARGET_CPU_ARCH)-$(ADK_VENDOR)-$(ADK_TARGET_LINUXTYPE)
endif
ifeq ($(ADK_TARGET_ARCH_ARM)$(ADK_TARGET_BINFMT_FDPIC),yy)
GNU_TARGET_NAME:=	$(ADK_TARGET_CPU_ARCH)-$(ADK_VENDOR)-$(ADK_TARGET_SUFFIX)
endif
ifeq ($(ADK_TARGET_OS_BAREMETAL),y)
GNU_TARGET_NAME:=	$(ADK_TARGET_CPU_ARCH)-$(ADK_TARGET_SUFFIX)
endif

TARGET_CROSS:=		$(TOOLCHAIN_DIR)/usr/bin/$(GNU_TARGET_NAME)-
TARGET_COMPILER_PREFIX?=${TARGET_CROSS}
CONFIGURE_TRIPLE:=	--build=${GNU_HOST_NAME} \
			--host=${GNU_TARGET_NAME} \
			--target=${GNU_TARGET_NAME}

# target tools
ifeq ($(ADK_BUILD_COMPILER_GCC),y)
TARGET_CC:=		${TARGET_COMPILER_PREFIX}gcc
TARGET_CXX:=		${TARGET_COMPILER_PREFIX}g++
TARGET_CC_NO_CCACHE:=	${TARGET_CC}
TARGET_CXX_NO_CCACHE:=	${TARGET_CXX}
endif
ifeq ($(ADK_BUILD_COMPILER_LLVM),y)
TARGET_CC:=		clang --target=${GNU_TARGET_NAME} --sysroot=$(STAGING_TARGET_DIR)
TARGET_CXX:=		clang++ --target=${GNU_TARGET_NAME} --sysroot=$(STAGING_TARGET_DIR)
TARGET_LDFLAGS:=	-fuse-ld=lld -stdlib=libc++
endif

# gcc specific
ifeq ($(ADK_BUILD_COMPILER_GCC),y)
ifneq ($(strip ${ADK_USE_CCACHE}),)
TARGET_CC:=		$(STAGING_HOST_DIR)/usr/bin/ccache ${TARGET_CC_NO_CCACHE}
TARGET_CXX:=		$(STAGING_HOST_DIR)/usr/bin/ccache ${TARGET_CXX_NO_CCACHE}
endif

# for x86_64 x32 ABI we need to extend TARGET_CC/TARGET_CXX
ifeq ($(ADK_TARGET_ABI_X32),y)
TARGET_CC+=            $(ADK_TARGET_ABI_CFLAGS)
TARGET_CXX+=           $(ADK_TARGET_ABI_CFLAGS)
endif

TARGET_LD:=		${TARGET_COMPILER_PREFIX}ld
ifneq ($(ADK_TARGET_USE_LTO),)
TARGET_AR:=		${TARGET_COMPILER_PREFIX}gcc-ar
TARGET_RANLIB:=		${TARGET_COMPILER_PREFIX}gcc-ranlib
else
TARGET_AR:=		${TARGET_COMPILER_PREFIX}ar
TARGET_RANLIB:=		${TARGET_COMPILER_PREFIX}ranlib
endif

TARGET_CPPFLAGS:=	
TARGET_CFLAGS:=		-fwrapv -fno-ident
TARGET_CXXFLAGS:=	-fwrapv -fno-ident
TARGET_LDFLAGS:=	-L$(STAGING_TARGET_DIR)/lib -L$(STAGING_TARGET_DIR)/usr/lib \
			-Wl,-O1 -Wl,-rpath -Wl,/usr/lib \
			-Wl,-rpath-link -Wl,${STAGING_TARGET_DIR}/usr/lib

# for architectures where gcc --with-cpu matches -mcpu=
ifneq ($(ADK_TARGET_GCC_CPU),)
TARGET_CFLAGS+=		-mcpu=$(ADK_TARGET_GCC_CPU)
TARGET_CXXFLAGS+=	-mcpu=$(ADK_TARGET_GCC_CPU)
endif

# for architectures where gcc --with-arch matches -march=
ifneq ($(ADK_TARGET_GCC_ARCH),)
TARGET_CFLAGS+=		-march=$(ADK_TARGET_GCC_ARCH)
TARGET_CXXFLAGS+=	-march=$(ADK_TARGET_GCC_ARCH)
endif

ifneq ($(ADK_TARGET_CPU_FLAGS),)
TARGET_CFLAGS+=		$(ADK_TARGET_CPU_FLAGS)
TARGET_CXXFLAGS+=	$(ADK_TARGET_CPU_FLAGS)
TARGET_LDFLAGS+=	$(ADK_TARGET_CPU_FLAGS)
endif

ifneq ($(ADK_TARGET_FPU),)
TARGET_CFLAGS+=		-mfpu=$(ADK_TARGET_FPU)
TARGET_CXXFLAGS+=	-mfpu=$(ADK_TARGET_FPU)
endif

ifneq ($(ADK_TARGET_FLOAT),)
ifeq ($(ADK_TARGET_ARCH_ARM),y)
TARGET_CFLAGS+=		-mfloat-abi=$(ADK_TARGET_FLOAT)
TARGET_CXXFLAGS+=	-mfloat-abi=$(ADK_TARGET_FLOAT)
endif
ifeq ($(ADK_TARGET_ARCH_MIPS),y)
TARGET_CFLAGS+=		-m$(ADK_TARGET_FLOAT)-float
TARGET_CXXFLAGS+=	-m$(ADK_TARGET_FLOAT)-float
endif
endif

ifeq ($(ADK_TARGET_BINFMT_FLAT),y)
TARGET_LDFLAGS+=	-Wl,-elf2flt=-r
TARGET_CFLAGS+=		-Wl,-elf2flt=-r
TARGET_CXXFLAGS+=	-Wl,-elf2flt=-r
endif

ifeq ($(ADK_TARGET_BINFMT_FLAT_SEP_DATA),y)
TARGET_CFLAGS+=		-msep-data
TARGET_CXXFLAGS+=	-msep-data
endif

ifeq ($(ADK_TARGET_BINFMT_FLAT_SHARED),y)
TARGET_LDFLAGS+=	-mid-shared-library
endif

ifeq ($(ADK_TARGET_BINFMT_DSBT),y)
TARGET_CFLAGS+=		-mdsbt
TARGET_CXXFLAGS+=	-mdsbt
endif

# security optimization, see http://www.akkadia.org/drepper/dsohowto.pdf
ifneq ($(ADK_TARGET_USE_LD_RELRO),)
TARGET_LDFLAGS+=	-Wl,-z,relro
endif
ifneq ($(ADK_TARGET_USE_LD_BIND_NOW),)
TARGET_LDFLAGS+=	-Wl,-z,now
endif

ifeq ($(ADK_TARGET_ARCH_RISCV64)$(ADK_TARGET_ARCH_RISCV32),y)
ifeq ($(ADK_TARGET_BINFMT_FLAT),y)
TARGET_CFLAGS+=		-fPIC
TARGET_CXXFLAGS+=	-fPIC
endif
endif

# needed for musl ppc 
ifeq ($(ADK_TARGET_ARCH_PPC),y)
ifeq ($(ADK_TARGET_LIB_MUSL),y)
TARGET_LDFLAGS+=	-Wl,--secure-plt
endif
endif

ifneq ($(ADK_TARGET_BINFMT_ELF)$(ADK_TARGET_WITH_MMU),y)
ifeq ($(ADK_TARGET_USE_STATIC_LIBS_ONLY)$(ADK_TARGET_USE_STATIC_AND_SHARED_LIBS),y)
TARGET_CFLAGS+=		-static
TARGET_CXXFLAGS+=	-static
TARGET_LDFLAGS+=	-static
endif
endif

ifneq ($(ADK_TARGET_USE_SSP),)
TARGET_CFLAGS+=		-fstack-protector-all --param=ssp-buffer-size=4
TARGET_CXXFLAGS+=	-fstack-protector-all --param=ssp-buffer-size=4
TARGET_LDFLAGS+=	-fstack-protector-all
endif

ifneq ($(ADK_TARGET_USE_LD_GC),)
TARGET_CFLAGS+=		-fdata-sections -ffunction-sections
TARGET_CXXFLAGS+=	-fdata-sections -ffunction-sections
TARGET_LDFLAGS+=	-Wl,--gc-sections
endif

ifneq ($(ADK_TARGET_USE_LTO),)
TARGET_CFLAGS+=		-flto
TARGET_CXXFLAGS+=	-flto
TARGET_LDFLAGS+=	-flto
endif

# performance optimization, see http://www.akkadia.org/drepper/dsohowto.pdf
ifneq ($(ADK_TARGET_USE_GNU_HASHSTYLE),)
TARGET_LDFLAGS+=	-Wl,--hash-style=gnu
endif

# special architecture optimization flags
ifeq ($(ADK_TARGET_ARCH_XTENSA),y)
ifeq ($(ADK_TARGET_LIB_NEWLIB),)
TARGET_CFLAGS+=		-mlongcalls -mauto-litpools
TARGET_CXXFLAGS+=	-mlongcalls -mauto-litpools
endif
endif
ifeq ($(ADK_TARGET_ARCH_MICROBLAZE),y)
TARGET_CFLAGS+=		-mxl-barrel-shift -fno-tree-loop-distribute-patterns
TARGET_CXXFLAGS+=	-mxl-barrel-shift -fno-tree-loop-distribute-patterns
endif

endif
# end gcc specific

# add configured compiler flags for optimization
TARGET_CFLAGS+=		$(ADK_TARGET_CFLAGS_OPT)
TARGET_CXXFLAGS+=	$(ADK_TARGET_CFLAGS_OPT)

# add compiler flags for debug information
ifneq ($(ADK_DEBUG),)
TARGET_CFLAGS+=		-g3
TARGET_CXXFLAGS+=	-g3
endif

ifneq ($(ADK_DEBUG),)
ifeq ($(ADK_TARGET_ARCH_ARM_WITH_THUMB),)
TARGET_CFLAGS+=		-fno-omit-frame-pointer
TARGET_CXXFLAGS+=	-fno-omit-frame-pointer
endif
TARGET_CFLAGS+=		-funwind-tables -fasynchronous-unwind-tables
TARGET_CXXFLAGS+=	-funwind-tables -fasynchronous-unwind-tables
else
TARGET_CPPFLAGS+=	-DNDEBUG
TARGET_CFLAGS+=		-fomit-frame-pointer
TARGET_CXXFLAGS+=	-fomit-frame-pointer
endif

# stop generating eh_frame stuff, do not use it for C++
ifeq ($(ADK_TARGET_CFLAGS_DISABLE_EH),y)
TARGET_CFLAGS+=		-fno-unwind-tables -fno-asynchronous-unwind-tables
TARGET_CXXFLAGS+=	-fno-unwind-tables -fno-asynchronous-unwind-tables
endif

# workaround gcc bug for m68k/coldfire
ifeq ($(ADK_TARGET_CPU_CF),y)
TARGET_CFLAGS+=		-fno-dwarf2-cfi-asm -mxgot
TARGET_CXXFLAGS+=	-fno-dwarf2-cfi-asm -mxgot
endif

ifeq ($(ADK_TARGET_ARCH_ARM),y)
ifeq ($(ADK_TARGET_ARCH_ARM_WITH_NEON),y)
TARGET_CFLAGS+=		-ffast-math -funsafe-math-optimizations
TARGET_CXXFLAGS+=	-ffast-math -funsafe-math-optimizations
endif
ifeq ($(ADK_TARGET_ARCH_ARM_WITH_THUMB),y)
TARGET_CFLAGS+=		-mthumb -Wa,-mimplicit-it=thumb -mno-thumb-interwork
TARGET_CXXFLAGS+=	-mthumb -Wa,-mimplicit-it=thumb -mno-thumb-interwork
else
TARGET_CFLAGS+=		-marm
TARGET_CXXFLAGS+=	-marm
endif
endif

# host compiler and linker flags
HOST_CPPFLAGS:=		-I$(STAGING_HOST_DIR)/usr/include
ifeq ($(OS_FOR_BUILD),Darwin)
HOST_LDFLAGS:=		-L$(STAGING_HOST_DIR)/usr/lib
else
HOST_LDFLAGS:=		-L$(STAGING_HOST_DIR)/usr/lib -Wl,-rpath -Wl,${STAGING_HOST_DIR}/usr/lib
endif

ifneq (${ADK_UPDATE_PATCHES_GIT},)
PATCH=			PATH='${HOST_PATH}' ${BASH} $(SCRIPT_DIR)/patch_git.sh
else
PATCH=			PATH='${HOST_PATH}' ${BASH} $(SCRIPT_DIR)/patch.sh
endif
PATCHP0=		PATH='${HOST_PATH}' patch -p0

ifeq ($(ADK_STATIC_TOOLCHAIN),y)
HOST_STATIC_CFLAGS:=   -static -Wl,-static
HOST_STATIC_CXXFLAGS:= -static -Wl,-static
HOST_STATIC_LDFLAGS:=  -Wl,-static
endif

SED:=			PATH='${HOST_PATH}' sed -i -e
XZ:=			PATH='${HOST_PATH}' xz
CPIO:=			PATH='${HOST_PATH}' cpio
LINUX_DIR:=		$(BUILD_DIR)/$(ADK_TARGET_OS)
KERNEL_MODULE_FLAGS:=	ARCH=${ADK_TARGET_KARCH} \
			PREFIX=/usr \
			KERNEL_PATH=${LINUX_DIR} \
			KERNELDIR=${LINUX_DIR} \
			CROSS_COMPILE="${TARGET_CROSS}" \
			V=1

COMMON_ENV=		CONFIG_SHELL='$(strip ${SHELL})' \
			AUTOM4TE='${STAGING_HOST_DIR}/usr/bin/autom4te' \
			M4='${STAGING_HOST_DIR}/usr/bin/m4' \
			LIBTOOLIZE='${STAGING_HOST_DIR}/usr/bin/libtoolize'

ifneq ($(ADK_TARGET_USE_LTO),)
TOOLS_ENV=		AR='$(TARGET_CROSS)gcc-ar' \
			RANLIB='$(TARGET_CROSS)gcc-ranlib' \
			NM='$(TARGET_CROSS)gcc-nm'
else
TOOLS_ENV=		AR='$(TARGET_CROSS)ar' \
			RANLIB='$(TARGET_CROSS)ranlib' \
			NM='$(TARGET_CROSS)nm'
endif

TARGET_ENV=		$(TOOLS_ENV) \
			AS='$(TARGET_CROSS)as' \
			LD='$(TARGET_CROSS)ld' \
			STRIP='$(TARGET_CROSS)strip' \
			OBJCOPY='$(TARGET_CROSS)objcopy' \
			CC='$(TARGET_CC)' \
			GCC='$(TARGET_CC)' \
			CXX='$(TARGET_CXX)' \
			CROSS='$(TARGET_CROSS)' \
			CROSS_COMPILE='$(TARGET_CROSS)' \
			CFLAGS='$(TARGET_CFLAGS)' \
			CXXFLAGS='$(TARGET_CXXFLAGS)' \
			CPPFLAGS='$(TARGET_CPPFLAGS)' \
			LDFLAGS='$(TARGET_LDFLAGS)' \
			CC_FOR_BUILD='$(HOST_CC)' \
			CXX_FOR_BUILD='$(HOST_CXX)' \
			CPPFLAGS_FOR_BUILD='$(HOST_CPPFLAGS)' \
			CFLAGS_FOR_BUILD='$(HOST_CFLAGS)' \
			CXXFLAGS_FOR_BUILD='$(HOST_CXXFLAGS)' \
			LDFLAGS_FOR_BUILD='$(HOST_LDFLAGS)' \
			LIBS_FOR_BUILD='$(HOST_LIBS)'

HOST_ENV=		CC='$(HOST_CC)' \
			CXX='$(HOST_CXX)' \
			CPPFLAGS='$(HOST_CPPFLAGS)' \
			CFLAGS='$(HOST_CFLAGS)' \
			CXXFLAGS='$(HOST_CXXFLAGS)' \
			LDFLAGS='$(HOST_LDFLAGS)' \
			CC_FOR_BUILD='$(HOST_CC)' \
			CFLAGS_FOR_BUILD='$(HOST_CFLAGS)'

PKG_SUFFIX:=		$(strip $(subst ",, $(ADK_PACKAGE_SUFFIX)))

ifeq ($(ADK_TARGET_PACKAGE_IPKG),y)
PKG_BUILD:=		${BASH} ${SCRIPT_DIR}/ipkg-build
PKG_INSTALL:=		PATH='${HOST_PATH}' \
			IPKG_TMP=$(BUILD_DIR)/tmp \
			IPKG_INSTROOT=$(TARGET_DIR) \
			IPKG_CONF_DIR=$(STAGING_TARGET_DIR)/etc \
			IPKG_OFFLINE_ROOT=$(TARGET_DIR) \
			BIN_DIR=$(STAGING_HOST_DIR)/usr/bin \
			${BASH} ${SCRIPT_DIR}/ipkg \
			-force-defaults -force-depends install
PKG_STATE_DIR:=		$(TARGET_DIR)/usr/lib/ipkg
endif

ifeq ($(ADK_TARGET_PACKAGE_OPKG),y)
PKG_BUILD:=		${BASH} ${SCRIPT_DIR}/ipkg-build
PKG_INSTALL:=		PATH='${HOST_PATH}' \
			IPKG_TMP=$(BUILD_DIR)/tmp \
			IPKG_INSTROOT=$(TARGET_DIR) \
			IPKG_CONF_DIR=$(STAGING_TARGET_DIR)/etc \
			IPKG_OFFLINE_ROOT=$(TARGET_DIR) \
			BIN_DIR=$(STAGING_HOST_DIR)/usr/bin \
			${BASH} ${SCRIPT_DIR}/ipkg \
			-force-defaults -force-depends install
PKG_STATE_DIR:=		$(TARGET_DIR)/usr/lib/opkg
endif

ifeq ($(ADK_TARGET_PACKAGE_TXZ),y)
PKG_BUILD:=		${BASH} ${SCRIPT_DIR}/tarpkg build
PKG_INSTALL:=		PKG_INSTROOT='$(TARGET_DIR)' \
			PATH='${HOST_PATH}' ${BASH} ${SCRIPT_DIR}/tarpkg install
PKG_STATE_DIR:=		$(TARGET_DIR)/usr/lib/pkg
endif

RSTRIP:=		PATH="$(TARGET_PATH)" prefix='${TARGET_CROSS}' ${BASH} ${SCRIPT_DIR}/rstrip.sh

STATCMD:=$(shell if stat -qs .>/dev/null 2>&1; then echo 'stat -f %z';else echo 'stat -c %s';fi)

EXTRACT_CMD=		PATH='${HOST_PATH}'; mkdir -p ${WRKDIR}; \
			cd ${WRKDIR} && \
			for file in ${FULLDISTFILES}; do case $$file in \
			*.cpio) \
				cat $$file | cpio -i -d ;; \
			*.tar) \
				PATH='$(HOST_PATH)' tar -xf $$file ;; \
			*.cpio.Z | *.cpio.gz | *.cgz | *.mcz) \
				gzip -dc $$file | cpio -i -d ;; \
			*.tar.xz | *.txz) \
				xz -dc $$file | PATH='$(HOST_PATH)' tar -xf - ;; \
			*.tar.Z | *.tar.gz | *.taz | *.tgz) \
				gzip -dc $$file | PATH='$(HOST_PATH)' tar -xf - ;; \
			*.cpio.bz2 | *.cbz) \
				bzip2 -dc $$file | cpio -i -d ;; \
			*.tar.bz2 | *.tbz | *.tbz2) \
				bzip2 -dc $$file | PATH='$(HOST_PATH)' tar -xf - ;; \
			*.tar.lz | *.tlz) \
				lzip -dc $$file | PATH='$(HOST_PATH)' tar -xf - ;; \
			*.zip) \
				unzip -d ${WRKDIR} $$file ;; \
			*.arm|*.jar|*.ids.gz) \
				mkdir ${WRKBUILD}; cp $$file ${WRKBUILD} ;; \
			*.bin) \
				sh $$file --force --auto-accept ;; \
			*) \
				echo "Cannot extract '$$file'" >&2; \
				false ;; \
			esac; done

ifneq (,$(filter CYGWIN%,${OS_FOR_BUILD}))
EXEEXT:=		.exe
endif

include $(ADK_TOPDIR)/mk/mirrors.mk
