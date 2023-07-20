# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		glibc
ifeq ($(ADK_LIBC_VERSION),git)
PKG_VERSION:=		2.37.90
PKG_GLIBCVER:=		2.37.9000
PKG_SITES:=		https://sourceware.org/git/glibc.git
PKG_RELEASE:=		1
endif
ifeq ($(ADK_TARGET_LIB_GLIBC_2_37),y)
PKG_VERSION:=		2.37
PKG_GLIBCVER:=		2.37
PKG_RELEASE:=		1
PKG_SITES:=		${MASTER_SITE_GNU:=glibc/}
PKG_HASH:=		2257eff111a1815d74f46856daaf40b019c1e553156c69d48ba0cbfc1bb91a43
endif
DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.xz
