# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/prereq.mk
-include $(ADK_TOPDIR)/.config

ifeq ($(ADK_VERBOSE),1)
START_TRACE:=		:
END_TRACE:=		:
TRACE:=			:
CMD_TRACE:=		:
PKG_TRACE:=		:
MAKE_TRACE:=
DL_TRACE:=
EXTRA_MAKEFLAGS:=
SET_DASHX:=		set -x
else
START_TRACE:=		echo -n " ---> "
END_TRACE:=		echo
TRACE:=			echo " ---> "
CMD_TRACE:=		echo -n
PKG_TRACE:=		echo "------> "
EXTRA_MAKEFLAGS:=	-s
MAKE_TRACE:=		>/dev/null 2>&1 || { echo "Build failed. Please re-run make with v to see what's going on"; false; }
DL_TRACE:=		>/dev/null 2>&1
SET_DASHX:=		:
endif

# Strip off the annoying quoting
ADK_TARGET_OS:=				$(strip $(subst ",, $(ADK_TARGET_OS)))
ADK_TARGET_ARCH:=			$(strip $(subst ",, $(ADK_TARGET_ARCH)))
ADK_TARGET_SYSTEM:=			$(strip $(subst ",, $(ADK_TARGET_SYSTEM)))
ADK_TARGET_BOARD:=			$(strip $(subst ",, $(ADK_TARGET_BOARD)))
ADK_TARGET_CPU_ARCH:=			$(strip $(subst ",, $(ADK_TARGET_CPU_ARCH)))
ADK_TARGET_CPU_TYPE:=			$(strip $(subst ",, $(ADK_TARGET_CPU_TYPE)))
ADK_TARGET_KERNEL:=			$(strip $(subst ",, $(ADK_TARGET_KERNEL)))
ADK_TARGET_LIBC:=			$(strip $(subst ",, $(ADK_TARGET_LIBC)))
ADK_TARGET_LIBC_PATH:=			$(strip $(subst ",, $(ADK_TARGET_LIBC_PATH)))
ADK_TARGET_LIBC_ABI_PATH:=		$(strip $(subst ",, $(ADK_TARGET_LIBC_ABI_PATH)))
ADK_TARGET_ENDIAN:=			$(strip $(subst ",, $(ADK_TARGET_ENDIAN)))
ADK_TARGET_ENDIAN_SUFFIX:=		$(strip $(subst ",, $(ADK_TARGET_ENDIAN_SUFFIX)))
ADK_TARGET_GCC_CPU:=			$(strip $(subst ",, $(ADK_TARGET_GCC_CPU)))
ADK_TARGET_GCC_ARCH:=			$(strip $(subst ",, $(ADK_TARGET_GCC_ARCH)))
ADK_TARGET_BINFMT:=			$(strip $(subst ",, $(ADK_TARGET_BINFMT)))
ADK_TARGET_FLOAT:=			$(strip $(subst ",, $(ADK_TARGET_FLOAT)))
ADK_TARGET_FPU:=			$(strip $(subst ",, $(ADK_TARGET_FPU)))
ADK_TARGET_INSTRUCTION_SET:=		$(strip $(subst ",, $(ADK_TARGET_INSTRUCTION_SET)))
ADK_TARGET_CFLAGS:=			$(strip $(subst ",, $(ADK_TARGET_CFLAGS)))
ADK_TARGET_CPU_FLAGS:=			$(strip $(subst ",, $(ADK_TARGET_CPU_FLAGS)))
ADK_TARGET_CFLAGS_OPT:=			$(strip $(subst ",, $(ADK_TARGET_CFLAGS_OPT)))
ADK_TARGET_ABI_CFLAGS:=			$(strip $(subst ",, $(ADK_TARGET_ABI_CFLAGS)))
ADK_TARGET_ABI:=			$(strip $(subst ",, $(ADK_TARGET_ABI)))
ADK_TARGET_ABI_MIPS64:=			$(strip $(subst ",, $(ADK_TARGET_ABI_MIPS64)))
ADK_TARGET_ABI_RISCV:=			$(strip $(subst ",, $(ADK_TARGET_ABI_RISCV)))
ADK_TARGET_IP:=				$(strip $(subst ",, $(ADK_TARGET_IP)))
ADK_TARGET_SUFFIX:=			$(strip $(subst ",, $(ADK_TARGET_SUFFIX)))
ADK_TARGET_CMDLINE:=			$(strip $(subst ",, $(ADK_TARGET_CMDLINE)))
ADK_TOOLCHAIN_LLVM_VERSION:=		$(strip $(subst ",, $(ADK_TOOLCHAIN_LLVM_VERSION)))
ADK_QEMU_ARGS:=				$(strip $(subst ",, $(ADK_QEMU_ARGS)))
ADK_RUNTIME_TMPFS_SIZE:=		$(strip $(subst ",, $(ADK_RUNTIME_TMPFS_SIZE)))
ADK_RUNTIME_CONSOLE_SERIAL_SPEED:=	$(strip $(subst ",, $(ADK_RUNTIME_CONSOLE_SERIAL_SPEED)))
ADK_RUNTIME_CONSOLE_SERIAL_DEVICE:=	$(strip $(subst ",, $(ADK_RUNTIME_CONSOLE_SERIAL_DEVICE)))
ADK_RUNTIME_CONSOLE_VGA_DEVICE:=	$(strip $(subst ",, $(ADK_RUNTIME_CONSOLE_VGA_DEVICE)))
ADK_RUNTIME_DEFAULT_LOCALE:=		$(strip $(subst ",, $(ADK_RUNTIME_DEFAULT_LOCALE)))
ADK_HOST:=				$(strip $(subst ",, $(ADK_HOST)))
ADK_VENDOR:=				$(strip $(subst ",, $(ADK_VENDOR)))
ADK_DL_DIR:=				$(strip $(subst ",, $(ADK_DL_DIR)))
ADK_COMPRESSION_TOOL:=			$(strip $(subst ",, $(ADK_COMPRESSION_TOOL)))
ADK_LIBC_VERSION:=			$(strip $(subst ",, $(ADK_LIBC_VERSION)))
ADK_PARAMETER_NETCONSOLE_SRC_IP:=	$(strip $(subst ",, $(ADK_PARAMETER_NETCONSOLE_SRC_IP)))
ADK_PARAMETER_NETCONSOLE_DST_IP:=	$(strip $(subst ",, $(ADK_PARAMETER_NETCONSOLE_DST_IP)))
ADK_JFFS2_OPTS:=			$(strip $(subst ",, $(ADK_JFFS2_OPTS)))
ADK_TARGET_LINUX_KERNEL_VERSION:=	$(strip $(subst ",, $(ADK_TARGET_LINUX_KERNEL_VERSION)))
ADK_TARGET_LINUX_KERNEL_GIT:=		$(strip $(subst ",, $(ADK_TARGET_LINUX_KERNEL_GIT)))
ADK_TARGET_LINUX_KERNEL_GIT_VER:=	$(strip $(subst ",, $(ADK_TARGET_LINUX_KERNEL_GIT_VER)))
ADK_TARGET_LINUX_KERNEL_GIT_TYPE:=	$(strip $(subst ",, $(ADK_TARGET_LINUX_KERNEL_GIT_TYPE)))
ADK_TARGET_LINUX_KERNEL_DEFCONFIG:=	$(strip $(subst ",, $(ADK_TARGET_LINUX_KERNEL_DEFCONFIG)))
ADK_TARGET_GENIMAGE_FILENAME:=		$(strip $(subst ",, $(ADK_TARGET_GENIMAGE_FILENAME)))
ADK_TARGET_EXTLINUX_FILENAME:=		$(strip $(subst ",, $(ADK_TARGET_EXTLINUX_FILENAME)))
ADK_TARGET_ROOTDEV:=			$(strip $(subst ",, $(ADK_TARGET_ROOTDEV)))

ADK_TARGET_KARCH:=$(ADK_TARGET_ARCH)

# translate toolchain arch to kernel arch
ifeq ($(ADK_TARGET_ARCH),aarch64)
ADK_TARGET_KARCH:=arm64
endif
ifeq ($(ADK_TARGET_ARCH),bfin)
ADK_TARGET_KARCH:=blackfin
endif
ifeq ($(ADK_TARGET_ARCH),or1k)
ADK_TARGET_KARCH:=openrisc
endif
ifeq ($(ADK_TARGET_ARCH),ppc)
ADK_TARGET_KARCH:=powerpc
endif
ifeq ($(ADK_TARGET_ARCH),ppc64)
ADK_TARGET_KARCH:=powerpc
endif
ifeq ($(ADK_TARGET_ARCH),mips64)
ADK_TARGET_KARCH:=mips
endif
ifeq ($(ADK_TARGET_ARCH),hppa)
ADK_TARGET_KARCH:=parisc
endif
ifeq ($(ADK_TARGET_ARCH),riscv32)
ADK_TARGET_KARCH:=riscv
endif
ifeq ($(ADK_TARGET_ARCH),riscv64)
ADK_TARGET_KARCH:=riscv
endif

include $(ADK_TOPDIR)/mk/vars.mk

ifneq (${show},)
.DEFAULT_GOAL:=		show
show:
	@$(info ${${show}})
else ifneq (${dump},)
__shquote=		'$(subst ','\'',$(1))'
__dumpvar=		echo $(call __shquote,$(1)=$(call __shquote,${$(1)}))
.DEFAULT_GOAL:=		show
show:
	@$(foreach _s,${dump},$(call __dumpvar,${_s});)
endif
