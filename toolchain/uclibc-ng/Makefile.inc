# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		uClibc-ng
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		git://uclibc-ng.org/git/uclibc-ng
endif
ifeq ($(ADK_TARGET_LIB_UCLIBC_NG_1_0_37),y)
PKG_VERSION:=		1.0.37
PKG_RELEASE:=		1
PKG_SITES:=		http://downloads.uclibc-ng.org/releases/1.0.37/
PKG_HASH:=		b2b815d20645cf604b99728202bf3ecb62507ce39dfa647884b4453caf86212c
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.xz
