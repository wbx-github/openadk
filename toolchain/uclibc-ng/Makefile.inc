# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		uClibc-ng
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		git://uclibc-ng.org/git/uclibc-ng
endif
ifeq ($(ADK_TARGET_LIB_UCLIBC_NG_1_0_35),y)
PKG_VERSION:=		1.0.35
PKG_RELEASE:=		1
PKG_SITES:=		http://downloads.uclibc-ng.org/releases/1.0.35/
PKG_HASH:=		4d0ee138f037017695a66b556b70f77a0eab8a238819bcb60af890b7b3382a2b
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.xz
