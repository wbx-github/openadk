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
PKG_HASH:=		c58640ba7c2ce70f09574365bc8039cf580b52e1ce369db527376891b2249028
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz
