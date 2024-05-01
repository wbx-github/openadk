# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		uClibc-ng
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		https://git.uclibc-ng.org/git/uclibc-ng.git
endif
ifeq ($(ADK_TARGET_LIB_UCLIBC_NG_1_0_48),y)
PKG_VERSION:=		1.0.48
PKG_RELEASE:=		1
PKG_SITES:=		http://downloads.uclibc-ng.org/releases/1.0.48/
PKG_HASH:=		c8ac74fb6c53f96cf9ecde05c3e37a4e03a67aee013b2f3c388a3c43d20b311d
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz
