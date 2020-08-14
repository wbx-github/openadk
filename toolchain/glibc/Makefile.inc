# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		glibc
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		2.32.90
PKG_GLIBCVER:=		2.32.9000
PKG_SITES:=		git://sourceware.org/git/glibc.git
PKG_RELEASE:=		1
endif
ifeq ($(ADK_TARGET_LIB_GLIBC_2_32),y)
PKG_VERSION:=		2.32
PKG_GLIBCVER:=		2.32
PKG_RELEASE:=		1
PKG_SITES:=		${MASTER_SITE_GNU:=glibc/}
PKG_HASH:=		1627ea54f5a1a8467032563393e0901077626dc66f37f10ee6363bb722222836
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.xz
