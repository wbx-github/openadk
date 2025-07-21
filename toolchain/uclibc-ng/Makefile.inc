# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		uClibc-ng
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		https://git.uclibc-ng.org/git/uclibc-ng.git
endif
ifeq ($(ADK_TARGET_LIB_UCLIBC_NG_1_0_53),y)
PKG_VERSION:=		1.0.53
PKG_RELEASE:=		1
PKG_SITES:=		http://downloads.uclibc-ng.org/releases/1.0.53/
PKG_HASH:=		570e491075f1d6592480f65b1dcbb01f24f0681ddba1bf418ebb25687cd13682
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz
