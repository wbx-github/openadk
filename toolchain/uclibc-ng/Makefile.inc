# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		uClibc-ng
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		https://git.uclibc-ng.org/git/uclibc-ng.git
endif
ifeq ($(ADK_TARGET_LIB_UCLIBC_NG_1_0_59),y)
PKG_VERSION:=		1.0.59
PKG_RELEASE:=		1
PKG_SITES:=		https://downloads.uclibc-ng.org/releases/1.0.59/
PKG_HASH:=		d96b2cf4e1c0df284b0e57555f58a43933a089bc97d1f005357aaece292210a3
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz
