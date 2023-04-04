# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		uClibc-ng
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		https://git.uclibc-ng.org/git/uclibc-ng.git
endif
ifeq ($(ADK_TARGET_LIB_UCLIBC_NG_1_0_43),y)
PKG_VERSION:=		1.0.43
PKG_RELEASE:=		1
PKG_SITES:=		http://downloads.uclibc-ng.org/releases/1.0.43/
PKG_HASH:=		8c1f550f14728a9c06ff1fb3e85069f7f10f4d684b03e163f4d9d41727124047
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.xz
