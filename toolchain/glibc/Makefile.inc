# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		glibc
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		2.41.90
PKG_GLIBCVER:=		2.41.9000
PKG_SITES:=		https://sourceware.org/git/glibc.git
PKG_RELEASE:=		1
endif
ifeq ($(ADK_TARGET_LIB_GLIBC_2_41),y)
PKG_VERSION:=		2.41
PKG_GLIBCVER:=		2.41
PKG_RELEASE:=		1
PKG_SITES:=		${MASTER_SITE_GNU:=glibc/}
PKG_HASH:=		c7be6e25eeaf4b956f5d4d56a04d23e4db453fc07760f872903bb61a49519b80
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz
