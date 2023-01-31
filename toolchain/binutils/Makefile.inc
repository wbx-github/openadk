# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		binutils
ifeq ($(ADK_TOOLCHAIN_BINUTILS_2_40),y)
PKG_VERSION:=		2.40
PKG_RELEASE:=		1
PKG_HASH:=		0f8a4c272d7f17f369ded10a4aca28b8e304828e95526da482b0ccc4dfc9d8e1
PKG_SITES:=		${MASTER_SITE_GNU:=binutils/}
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.xz
endif
ifeq ($(ADK_TOOLCHAIN_BINUTILS_2_39),y)
PKG_VERSION:=		2.39
PKG_RELEASE:=		1
PKG_HASH:=		645c25f563b8adc0a81dbd6a41cffbf4d37083a382e02d5d3df4f65c09516d00
PKG_SITES:=		${MASTER_SITE_GNU:=binutils/}
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.xz
endif
ifeq ($(ADK_TOOLCHAIN_BINUTILS_2_38),y)
PKG_VERSION:=		2.38
PKG_RELEASE:=		1
PKG_HASH:=		e316477a914f567eccc34d5d29785b8b0f5a10208d36bbacedcc39048ecfe024
PKG_SITES:=		${MASTER_SITE_GNU:=binutils/}
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.xz
endif
ifeq ($(ADK_TOOLCHAIN_BINUTILS_2_37),y)
PKG_VERSION:=		2.37
PKG_RELEASE:=		1
PKG_HASH:=		820d9724f020a3e69cb337893a0b63c2db161dadcb0e06fc11dc29eb1e84a32c
PKG_SITES:=		${MASTER_SITE_GNU:=binutils/}
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.xz
endif
ifeq ($(ADK_TOOLCHAIN_BINUTILS_2_28),y)
PKG_VERSION:=		2.28
PKG_RELEASE:=		1
PKG_HASH:=		cd717966fc761d840d451dbd58d44e1e5b92949d2073d75b73fccb476d772fcf
PKG_SITES:=		${MASTER_SITE_GNU:=binutils/}
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz
endif
ifeq ($(ADK_TOOLCHAIN_BINUTILS_ARC),y)
PKG_VERSION:=          arc-2021.09
PKG_GIT:=              tag
PKG_RELEASE:=          1
PKG_SITES:=            https://github.com/foss-for-synopsys-dwc-arc-processors/binutils-gdb.git
DISTFILES:=            ${PKG_NAME}-${PKG_VERSION}.tar.xz
endif
ifeq ($(ADK_TOOLCHAIN_BINUTILS_KVX),y)
PKG_VERSION:=		782547a4e2bdf1308728032853678ca69bb154ea
PKG_GIT:=		hash
PKG_RELEASE:=		1
PKG_SITES:=		https://github.com/kalray/gdb-binutils.git
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.xz
endif
ifeq ($(ADK_TOOLCHAIN_BINUTILS_AVR32),y)
PKG_VERSION:=		2.20.1
PKG_RELEASE:=		1
PKG_HASH:=		71d37c96451333c5c0b84b170169fdcb138bbb27397dc06281905d9717c8ed64
PKG_SITES:=		${MASTER_SITE_GNU:=binutils/}
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.bz2
endif
ifeq ($(ADK_TOOLCHAIN_BINUTILS_GIT),y)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		git://sourceware.org/git/binutils-gdb.git
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.xz
endif
