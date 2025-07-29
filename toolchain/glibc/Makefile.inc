# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		glibc
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		2.42.90
PKG_GLIBCVER:=		2.42.9000
PKG_SITES:=		https://sourceware.org/git/glibc.git
PKG_RELEASE:=		1
endif
ifeq ($(ADK_TARGET_LIB_GLIBC_2_42),y)
PKG_VERSION:=		2.42
PKG_GLIBCVER:=		2.42
PKG_RELEASE:=		1
PKG_SITES:=		${MASTER_SITE_GNU:=glibc/}
PKG_HASH:=		d4468d3e3267068c1b0623ca6424aac9a28766df774c8d8fb4978127fca7125a
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz
