# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		glibc
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		2.35.90
PKG_GLIBCVER:=		2.35.9000
PKG_SITES:=		git://sourceware.org/git/glibc.git
PKG_RELEASE:=		1
endif
ifeq ($(ADK_TARGET_LIB_GLIBC_2_35),y)
PKG_VERSION:=		2.35
PKG_GLIBCVER:=		2.35
PKG_RELEASE:=		1
PKG_SITES:=		${MASTER_SITE_GNU:=glibc/}
PKG_HASH:=		5123732f6b67ccd319305efd399971d58592122bcc2a6518a1bd2510dd0cf52e
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.xz
