# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		uClibc-ng
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		https://git.uclibc-ng.org/git/uclibc-ng.git
endif
ifeq ($(ADK_TARGET_LIB_UCLIBC_NG_1_0_47),y)
PKG_VERSION:=		1.0.47
PKG_RELEASE:=		1
PKG_SITES:=		http://downloads.uclibc-ng.org/releases/1.0.47/
PKG_HASH:=		29a4d684a06da344ee3ee09acc2ca7649d592ae3ff848f698145c46def05efcb
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.xz
