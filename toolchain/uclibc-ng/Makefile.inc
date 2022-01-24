# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		uClibc-ng
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		https://git.uclibc-ng.org/git/uclibc-ng.git
endif
ifeq ($(ADK_TARGET_LIB_UCLIBC_NG_1_0_40),y)
PKG_VERSION:=		1.0.40
PKG_RELEASE:=		1
PKG_SITES:=		http://downloads.uclibc-ng.org/releases/1.0.40/
PKG_HASH:=		d863f01815a64174d5019c73475e8aff5b60848a13876e79daf5d3d83ce7f889
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.xz
