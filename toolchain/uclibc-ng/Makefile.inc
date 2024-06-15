# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		uClibc-ng
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		https://git.uclibc-ng.org/git/uclibc-ng.git
endif
ifeq ($(ADK_TARGET_LIB_UCLIBC_NG_1_0_49),y)
PKG_VERSION:=		1.0.49
PKG_RELEASE:=		1
PKG_SITES:=		http://downloads.uclibc-ng.org/releases/1.0.49/
PKG_HASH:=		4cb65c53b3724ca526fb228c72e29924432294868157ade8fa2667e0622ebd49
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz
