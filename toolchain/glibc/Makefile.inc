# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		glibc
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		2.39.90
PKG_GLIBCVER:=		2.39.9000
PKG_SITES:=		https://sourceware.org/git/glibc.git
PKG_RELEASE:=		1
endif
ifeq ($(ADK_TARGET_LIB_GLIBC_2_39),y)
PKG_VERSION:=		2.39
PKG_GLIBCVER:=		2.39
PKG_RELEASE:=		1
PKG_SITES:=		${MASTER_SITE_GNU:=glibc/}
PKG_HASH:=		f77bd47cf8170c57365ae7bf86696c118adb3b120d3259c64c502d3dc1e2d926
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.xz
