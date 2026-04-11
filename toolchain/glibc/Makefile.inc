# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		glibc
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		2.43.90
PKG_GLIBCVER:=		2.43.9000
PKG_SITES:=		https://sourceware.org/git/glibc.git
PKG_RELEASE:=		1
endif
ifeq ($(ADK_TARGET_LIB_GLIBC_2_43),y)
PKG_VERSION:=		2.43
PKG_GLIBCVER:=		2.43
PKG_RELEASE:=		1
PKG_SITES:=		${MASTER_SITE_GNU:=glibc/}
PKG_HASH:=		e1e622cbd635019090fa23260e5d9ec219b12f97ae7ae02f033d4ae42cf2c004
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz
