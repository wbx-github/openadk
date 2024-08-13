# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		uClibc-ng
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		https://git.uclibc-ng.org/git/uclibc-ng.git
endif
ifeq ($(ADK_TARGET_LIB_UCLIBC_NG_1_0_50),y)
PKG_VERSION:=		1.0.50
PKG_RELEASE:=		1
PKG_SITES:=		http://downloads.uclibc-ng.org/releases/1.0.50/
PKG_HASH:=		7b96bc6d0695ee77370ac49116f1012059de0f37342a68cd437e45d876449664
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz
