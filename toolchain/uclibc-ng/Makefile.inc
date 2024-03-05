# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		uClibc-ng
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		https://git.uclibc-ng.org/git/uclibc-ng.git
endif
ifeq ($(ADK_TARGET_LIB_UCLIBC_NG_1_0_46),y)
PKG_VERSION:=		1.0.46
PKG_RELEASE:=		1
PKG_SITES:=		http://downloads.uclibc-ng.org/releases/1.0.46/
PKG_HASH:=		d6eb01fced11c5e3b319bf4132d67685b1c33494426e9426032e31979d7d8ad7
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.xz
