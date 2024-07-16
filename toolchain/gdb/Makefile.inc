# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

PKG_NAME:=		gdb
ifeq ($(ADK_TOOLCHAIN_GDB_15_1),y)
PKG_VERSION:=		15.1
PKG_RELEASE:=		1
PKG_HASH:=		8b61b0c2bdd9d9c83b113c9167866bdb474651d291fedcaa5eb7cde49bd47036
PKG_SITES:=		${MASTER_SITE_GNU:=gdb/}
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz
endif
ifeq ($(ADK_TOOLCHAIN_GDB_14_2),y)
PKG_VERSION:=		14.2
PKG_RELEASE:=		1
PKG_HASH:=		2de5174762e959a5e529e20c20d88a04735469d8fffd98f61664e70b341dc47c
PKG_SITES:=		${MASTER_SITE_GNU:=gdb/}
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz
endif
ifeq ($(ADK_TOOLCHAIN_GDB_13_2),y)
PKG_VERSION:=		13.2
PKG_RELEASE:=		1
PKG_HASH:=		7ead13d9e19fa0c57bb19104e1a5f67eefa9fc79f2e6360de491e8fddeda1e30
PKG_SITES:=		${MASTER_SITE_GNU:=gdb/}
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz
endif
ifeq ($(ADK_TOOLCHAIN_GDB_6_7_1),y)
PKG_VERSION:=		6.7.1
PKG_RELEASE:=		1
PKG_HASH:=		a34c65163a2428e24891466b1f095249bc6301b64cfe9480f3aba341b58c3434
PKG_SITES:=		http://distfiles.openadk.org/
DISTFILES:=		gdb-6.7.1-avr32-2.1.5.tar.bz2
WRKDIST=		$(WRKDIR)/gdb-6.7.1-avr32-2.1.5
endif
ifeq ($(ADK_TOOLCHAIN_GDB_H8300_GIT),y)
PKG_VERSION:=		ysato-h8300
PKG_RELEASE:=		1
PKG_GIT:=		branch
PKG_SITES:=		git://git.pf.osdn.jp/gitroot/y/ys/ysato/binutils_gdb.git
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz
endif
ifeq ($(ADK_TOOLCHAIN_GDB_GIT),y)
PKG_VERSION:=		git
PKG_RELEASE:=		1
PKG_SITES:=		git://sourceware.org/git/binutils-gdb.git
DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz
endif
