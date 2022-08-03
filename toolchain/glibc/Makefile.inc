# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		glibc
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		2.36.90
PKG_GLIBCVER:=		2.36.9000
PKG_SITES:=		git://sourceware.org/git/glibc.git
PKG_RELEASE:=		1
endif
ifeq ($(ADK_TARGET_LIB_GLIBC_2_36),y)
PKG_VERSION:=		2.36
PKG_GLIBCVER:=		2.36
PKG_RELEASE:=		1
PKG_SITES:=		${MASTER_SITE_GNU:=glibc/}
PKG_HASH:=		1c959fea240906226062cb4b1e7ebce71a9f0e3c0836c09e7e3423d434fcfe75
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.xz
