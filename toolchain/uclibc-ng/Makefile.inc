# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		uClibc-ng
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		https://git.uclibc-ng.org/git/uclibc-ng.git
endif
ifeq ($(ADK_TARGET_LIB_UCLIBC_NG_1_0_56),y)
PKG_VERSION:=		1.0.56
PKG_RELEASE:=		1
PKG_SITES:=		http://downloads.uclibc-ng.org/releases/1.0.56/
PKG_HASH:=		e954b6de4b751ecb4a5e50430a2a51150dc0e13b31ea550d173c65fc5ced81ed
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz
