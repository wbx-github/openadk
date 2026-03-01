# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		uClibc-ng
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		https://git.uclibc-ng.org/git/uclibc-ng.git
endif
ifeq ($(ADK_TARGET_LIB_UCLIBC_NG_1_0_57),y)
PKG_VERSION:=		1.0.57
PKG_RELEASE:=		1
PKG_SITES:=		https://downloads.uclibc-ng.org/releases/1.0.57/
PKG_HASH:=		543c3d8362ae1939b15c4f008f9492e281116ad8d16d8652b1515d2e1fb6437f
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz
