# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		uClibc-ng
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		https://git.uclibc-ng.org/git/uclibc-ng.git
endif
ifeq ($(ADK_TARGET_LIB_UCLIBC_NG_1_0_42),y)
PKG_VERSION:=		1.0.42
PKG_RELEASE:=		1
PKG_SITES:=		http://downloads.uclibc-ng.org/releases/1.0.42/
PKG_HASH:=		ec6dae44ce86558885e56bc3bef6bd4d082397114e6e1fc15795f71e804d7016
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.xz
