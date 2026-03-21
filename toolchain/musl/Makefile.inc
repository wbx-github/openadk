# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		musl
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		git://git.musl-libc.org/musl
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz
endif
ifeq ($(ADK_TARGET_LIB_MUSL_1_2_6),y)
PKG_VERSION:=		1.2.6
PKG_RELEASE:=		1
PKG_HASH:=		d585fd3b613c66151fc3249e8ed44f77020cb5e6c1e635a616d3f9f82460512a
PKG_SITES:=		http://www.musl-libc.org/releases/
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz
endif
