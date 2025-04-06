# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		uClibc-ng
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		https://git.uclibc-ng.org/git/uclibc-ng.git
endif
ifeq ($(ADK_TARGET_LIB_UCLIBC_NG_1_0_52),y)
PKG_VERSION:=		1.0.52
PKG_RELEASE:=		1
PKG_SITES:=		http://downloads.uclibc-ng.org/releases/1.0.52/
PKG_HASH:=		8c70b76f11d78c6b3b1608d74016387d292c35793efec820a377c74dfc850dad
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz
