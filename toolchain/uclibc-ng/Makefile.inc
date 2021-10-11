# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		uClibc-ng
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		git://uclibc-ng.org/git/uclibc-ng
endif
ifeq ($(ADK_TARGET_LIB_UCLIBC_NG_1_0_39),y)
PKG_VERSION:=		1.0.39
PKG_RELEASE:=		1
PKG_SITES:=		http://downloads.uclibc-ng.org/releases/1.0.39/
PKG_HASH:=		cb089dfe14867a38f222d6428e85d0e1191dcbb66dd9b1a671484f6bc7c81920
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.xz
