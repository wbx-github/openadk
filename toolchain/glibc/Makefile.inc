# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		glibc
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		2.40.90
PKG_GLIBCVER:=		2.40.9000
PKG_SITES:=		https://sourceware.org/git/glibc.git
PKG_RELEASE:=		1
endif
ifeq ($(ADK_TARGET_LIB_GLIBC_2_40),y)
PKG_VERSION:=		2.40
PKG_GLIBCVER:=		2.40
PKG_RELEASE:=		1
PKG_SITES:=		${MASTER_SITE_GNU:=glibc/}
PKG_HASH:=		2abc038f5022949cb67e996c3cae0e7764f99b009f0b9b7fd954dfc6577b599e
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz
