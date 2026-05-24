# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		uClibc-ng
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		https://git.uclibc-ng.org/git/uclibc-ng.git
endif
ifeq ($(ADK_TARGET_LIB_UCLIBC_NG_1_0_58),y)
PKG_VERSION:=		1.0.58
PKG_RELEASE:=		1
PKG_SITES:=		https://downloads.uclibc-ng.org/releases/1.0.58/
PKG_HASH:=		197c81c0bebc7deac478be117ef7cd15b33f1de9d58c3e3ab5ba8fbe309ce6de
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz
