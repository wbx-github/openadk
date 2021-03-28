# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		uClibc-ng
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		git://uclibc-ng.org/git/uclibc-ng
endif
ifeq ($(ADK_TARGET_LIB_UCLIBC_NG_1_0_38),y)
PKG_VERSION:=		1.0.38
PKG_RELEASE:=		1
PKG_SITES:=		http://downloads.uclibc-ng.org/releases/1.0.38/
PKG_HASH:=		b1a3328330d2c94a2bec8c1436a8f15673f3a9b5895e155efc2e91d4e1882570
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.xz
