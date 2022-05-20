# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		uClibc-ng
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		https://git.uclibc-ng.org/git/uclibc-ng.git
endif
ifeq ($(ADK_TARGET_LIB_UCLIBC_NG_1_0_41),y)
PKG_VERSION:=		1.0.41
PKG_RELEASE:=		1
PKG_SITES:=		http://downloads.uclibc-ng.org/releases/1.0.41/
PKG_HASH:=		b32a92a0218d95922d6976464e6ef51e2ebacfbcdb605820458d9dbb8a61e025
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.xz
