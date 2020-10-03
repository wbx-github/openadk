# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		uClibc-ng
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		git://uclibc-ng.org/git/uclibc-ng
endif
ifeq ($(ADK_TARGET_LIB_UCLIBC_NG_1_0_36),y)
PKG_VERSION:=		1.0.36
PKG_RELEASE:=		1
PKG_SITES:=		http://downloads.uclibc-ng.org/releases/1.0.36/
PKG_HASH:=		010f40841669809422e01b47e7169d49c61bf3382f493c2571a8a96634ed300c
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.xz
