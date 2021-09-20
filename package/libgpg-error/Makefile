# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		libgpg-error
PKG_VERSION:=		1.42
PKG_RELEASE:=		1
PKG_HASH:=		fc07e70f6c615f8c4f590a8e37a9b8dd2e2ca1e9408f8e60459c67452b925e23
PKG_DESCR:=		helper library for common error codes and descriptions
PKG_SECTION:=		libs/misc
PKG_URL:=		http://www.gnupg.org/
PKG_SITES:=		ftp://ftp.gnupg.org/gcrypt/libgpg-error/
PKG_OPTS:=		dev
PKG_NOPARALLEL:=	1

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.bz2

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LIBGPG_ERROR,libgpg-error,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

ifeq ($(ADK_TARGET_ARCH_AARCH64),y)
LIBGPG_PREFIX:=		aarch64-unknown-linux-gnu
endif
ifeq ($(ADK_TARGET_ARCH_ARM),y)
LIBGPG_PREFIX:=		arm-unknown-linux-gnueabi
endif
ifeq ($(ADK_TARGET_ARCH_M68K),y)
LIBGPG_PREFIX:=		m68k-unknown-linux-gnu
endif
ifeq ($(ADK_TARGET_ARCH_MIPS),y)
LIBGPG_PREFIX:=		mips-unknown-linux-gnu
endif
ifeq ($(ADK_TARGET_ARCH_MIPS64),y)
LIBGPG_PREFIX:=		mips64el-unknown-linux-gnuabi64
endif
ifeq ($(ADK_TARGET_ARCH_NIOS2),y)
LIBGPG_PREFIX:=		nios2-unknown-linux-gnu
endif
ifeq ($(ADK_TARGET_ARCH_PPC),y)
LIBGPG_PREFIX:=		powerpc-unknown-linux-gnu
endif
ifeq ($(ADK_TARGET_ARCH_PPC64),y)
LIBGPG_PREFIX:=		powerpc64-unknown-linux-gnu
endif
ifeq ($(ADK_TARGET_ARCH_SH),y)
LIBGPG_PREFIX:=		sh4-unknown-linux-gnu
endif
ifeq ($(ADK_TARGET_ARCH_SPARC),y)
LIBGPG_PREFIX:=		sparc-unknown-linux-gnu
endif
ifeq ($(ADK_TARGET_ARCH_SPARC64),y)
LIBGPG_PREFIX:=		sparc64-unknown-linux-gnu
endif
ifeq ($(ADK_TARGET_ARCH_X86),y)
LIBGPG_PREFIX:=		i686-pc-linux-gnu
endif
ifeq ($(ADK_TARGET_ARCH_X86_64),y)
LIBGPG_PREFIX:=		x86_64-pc-linux-gnu
endif

post-extract:
	cd $(WRKSRC)/src/syscfg && \
	ln -s lock-obj-pub.$(LIBGPG_PREFIX).h \
		lock-obj-pub.$(GNU_TARGET_NAME).h

libgpg-error-install:
	${INSTALL_DIR} ${IDIR_LIBGPG_ERROR}/usr/lib
	${CP} ${WRKINST}/usr/lib/libgpg-error.so* \
		${IDIR_LIBGPG_ERROR}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
