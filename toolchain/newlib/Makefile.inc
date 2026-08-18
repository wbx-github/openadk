# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		newlib
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		git://sourceware.org/git/newlib-cygwin.git
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.xz
endif
ifeq ($(ADK_TARGET_LIB_NEWLIB_4_6_0),y)
PKG_VERSION:=		4.6.0.20260123
PKG_RELEASE:=		1
PKG_HASH:=		6ff27e3bf022666f43f7802255be680eeff722ac181b1725d21e2e8318604ee3
PKG_SITES:=		ftp://sourceware.org/pub/newlib/
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz
endif
