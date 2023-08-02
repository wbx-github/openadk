# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		glibc
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		2.38.90
PKG_GLIBCVER:=		2.38.9000
PKG_SITES:=		https://sourceware.org/git/glibc.git
PKG_RELEASE:=		1
endif
ifeq ($(ADK_TARGET_LIB_GLIBC_2_38),y)
PKG_VERSION:=		2.38
PKG_GLIBCVER:=		2.38
PKG_RELEASE:=		1
PKG_SITES:=		${MASTER_SITE_GNU:=glibc/}
PKG_HASH:=		fb82998998b2b29965467bc1b69d152e9c307d2cf301c9eafb4555b770ef3fd2
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.xz
