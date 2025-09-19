# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		uClibc-ng
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		https://git.uclibc-ng.org/git/uclibc-ng.git
endif
ifeq ($(ADK_TARGET_LIB_UCLIBC_NG_1_0_55),y)
PKG_VERSION:=		1.0.55
PKG_RELEASE:=		1
PKG_SITES:=		http://downloads.uclibc-ng.org/releases/1.0.55/
PKG_HASH:=		005aed346789fad2c043f76e99425258a95af3121ebf3e255d33086930ad1272
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz
