# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		uClibc-ng
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		https://git.uclibc-ng.org/git/uclibc-ng.git
endif
ifeq ($(ADK_TARGET_LIB_UCLIBC_NG_1_0_54),y)
PKG_VERSION:=		1.0.54
PKG_RELEASE:=		1
PKG_SITES:=		http://downloads.uclibc-ng.org/releases/1.0.54/
PKG_HASH:=		6c46d8e75b466dcb0882ab652ac45b2606af4d8cb892b9182795ba5f3ccec24f
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz
