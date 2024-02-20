# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk
include ${ADK_TOPDIR}/toolchain/binutils/Makefile.inc

PKG_NAME:=		binutils
PKG_DESCR:=		binary utilities (nm, objdump, as, ..)
PKG_SECTION:=		dev/tools
PKG_DEPENDS:=		libbfd
PKG_LIBNAME:=		libbfd
PKG_OPTS:=		dev

PKG_SUBPKGS:=		BINUTILS LIBBFD
PKGSD_LIBBFD:=		binary file descriptor library
PKGSC_LIBBFD:=		libs/misc

PKG_HOST_DEPENDS:=      !cygwin

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,BINUTILS,${PKG_NAME},${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,LIBBFD,libbfd,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_LIBBFD},${PKGSD_LIBBFD},${PKGSC_LIBBFD},${PKG_OPTS}))

ifeq ($(ADK_TARGET_ARCH_BFIN),y)
TARGET_CFLAGS:=		$(subst Os,O1,$(TARGET_CFLAGS))
TARGET_CXXFLAGS:=	$(subst Os,O1,$(TARGET_CFLAGS))
endif

TARGET_CFLAGS+=		-fPIC
CONFIGURE_ENV+=		ac_cv_prog_MAKEINFO=missing

ifeq ($(ADK_TARGET_ARCH_SH)$(ADK_TARGET_ARCH_X86_64),)
CONFIGURE_ARGS+=	--disable-multilib
else
CONFIGURE_ARGS+=	--enable-multilib
endif
CONFIGURE_ARGS+=	--disable-werror \
			--disable-gprofng \
			--disable-gdb \
			--disable-sim \
			--disable-install-libiberty \
			--host=$(GNU_TARGET_NAME) \
			--target=$(GNU_TARGET_NAME)

libbfd-install:
	${INSTALL_DIR} ${IDIR_LIBBFD}/usr/lib
	$(CP) ${WRKINST}/usr/lib/*.so* ${IDIR_LIBBFD}/usr/lib
	# for oprofile
	${INSTALL_DIR} ${STAGING_TARGET_DIR}/usr/lib/binutils
	$(CP) ${WRKBUILD}/libiberty/libiberty.a \
		${STAGING_TARGET_DIR}/usr/lib/binutils

binutils-install:
	${INSTALL_DIR} ${IDIR_BINUTILS}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/{ar,as,ld,strip,strings,size,nm} \
		${IDIR_BINUTILS}/usr/bin/
	${INSTALL_BIN} ${WRKINST}/usr/bin/{objcopy,ranlib,readelf,objdump} \
		 ${IDIR_BINUTILS}/usr/bin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
