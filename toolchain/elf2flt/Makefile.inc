# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		elf2flt
ifeq ($(ADK_TOOLCHAIN_ELF2FLT_2021_08),y)
PKG_VERSION:=		v2021.08
PKG_GIT:=		tag
PKG_RELEASE:=		1
PKG_SITES:=		https://github.com/uclinux-dev/elf2flt.git
endif
ifeq ($(ADK_TOOLCHAIN_ELF2FLT_OLD),y)
PKG_VERSION:=		453398f917d167f8c308c8f997270c48ae8f8b12
PKG_GIT:=		hash
PKG_RELEASE:=		1
PKG_SITES:=		https://github.com/uclinux-dev/elf2flt.git
endif
ifeq ($(ADK_TOOLCHAIN_ELF2FLT_LM32),y)
PKG_VERSION:=		3051fec89bbd30de6f952dc3100712feff3ca076
PKG_GIT:=		hash
PKG_RELEASE:=		1
PKG_SITES:=		https://github.com/m-labs/elf2flt-lm32.git
endif
