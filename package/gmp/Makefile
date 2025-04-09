# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk
include ${ADK_TOPDIR}/toolchain/gmp/Makefile.inc

PKG_NAME:=		gmp
PKG_DESCR:=		multiprecision arithmetic library
PKG_SECTION:=		libs/misc
PKG_BUILDDEP:=		m4-host flex-host bison-host
PKG_URL:=		http://gmplib.org/
PKG_NEEDS:=		c++
PKG_LIBNAME:=		libgmp
PKG_OPTS:=		dev

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,LIBGMP,libgmp,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,LIBGMP,libgmp,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

ifeq ($(ADK_TARGET_CPU_MIPS_MIPS32R6)$(ADK_TARGET_CPU_MIPS_MIPS64R6),y)
CONFIGURE_ARGS+=	--disable-assembly
endif

libgmp-install:
	${INSTALL_DIR} ${IDIR_LIBGMP}/usr/lib
	${CP} ${WRKINST}/usr/lib/libgmp.so* \
		${IDIR_LIBGMP}/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
