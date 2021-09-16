# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		glibc
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		2.34.90
PKG_GLIBCVER:=		2.34.9000
PKG_SITES:=		git://sourceware.org/git/glibc.git
PKG_RELEASE:=		1
endif
ifeq ($(ADK_TARGET_LIB_GLIBC_2_34),y)
PKG_VERSION:=		2.34
PKG_GLIBCVER:=		2.34
PKG_RELEASE:=		1
PKG_SITES:=		${MASTER_SITE_GNU:=glibc/}
PKG_HASH:=		44d26a1fe20b8853a48f470ead01e4279e869ac149b195dda4e44a195d981ab2
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.xz
