# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

KERNEL_MAKE_OPTS:=	CC="$(TARGET_CC)"
ifeq ($(ADK_TARGET_BINFMT_FDPIC),y)
KERNEL_MAKE_OPTS:=	CC="$(TARGET_CC) -mno-fdpic"
endif
ifeq ($(ADK_TARGET_ARCH_MICROBLAZE),y)
KERNEL_MAKE_OPTS:=	CC="$(TARGET_CC) -fno-tree-loop-distribute-patterns"
endif

KERNEL_MAKE_OPTS+=	V=1 \
			ARCH="$(ADK_TARGET_KARCH)" \
			CROSS_COMPILE="$(TARGET_CROSS)" \
			HOSTCC="${HOST_CC}" \
			HOSTCXX="${HOST_CXX}" \
			SHELL='${SHELL}' \
			CONFIG_SHELL='${SHELL}' \
			HOSTCFLAGS='$(HOST_CPPFLAGS) $(HOST_CFLAGS)'

ifneq ($(ADK_TARGET_KERNEL_LOADADDR),)
KERNEL_MAKE_OPTS+=	LOADADDR=$(ADK_TARGET_KERNEL_LOADADDR)
endif

KERNEL_MAKE_ENV:=	PATH="${TOOLCHAIN_DIR}/usr/bin:${STAGING_HOST_DIR}/usr/bin:$$PATH"
LINUX_BUILD_DIR:=	$(BUILD_DIR)/$(ADK_TARGET_OS)-$(ADK_TARGET_ARCH)

# wrapper to simplify calling make in kernel tree
KERNEL_MAKE:=		env $(KERNEL_MAKE_ENV) $(MAKE) -C "${LINUX_DIR}" $(KERNEL_MAKE_OPTS) -j${ADK_MAKE_JOBS}
