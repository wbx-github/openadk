# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		gdbserver
PKG_VERSION:=		17.1
PKG_RELEASE:=		1
PKG_HASH:=		14996f5f74c9f68f5a543fdc45bca7800207f91f92aeea6c2e791822c7c6d876
PKG_DESCR:=		remote program debugger utility
PKG_SECTION:=		app/debug
PKG_NEEDS:=		c++ iconv
PKG_SITES:=		${MASTER_SITE_GNU:=gdb/}
PKG_DEPENDS:=		libthread-db libgmp
PKG_BUILDDEP:=		gmp

PKG_LIBC_DEPENDS:=	!musl
PKG_ARCH_DEPENDS:=	!microblaze !nds32

ifeq ($(ADK_TOOLCHAIN_GDB_6_7_1),y)
DISTFILES:=		gdb-6.7.1-avr32-2.1.5.tar.bz2
WRKDIST=		$(WRKDIR)/gdb-6.7.1-avr32-2.1.5
else
DISTFILES:=		gdb-${PKG_VERSION}.tar.xz
WRKDIST=		${WRKDIR}/gdb-${PKG_VERSION}
endif
WRKBUILD=		${WRKSRC}/build

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,GDBSERVER,gdbserver,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ARGS+=	--enable-static \
			--disable-shared \
			--disable-gdb \
			--disable-sim \
			--disable-install-libiberty \
			--disable-install-libbfd \
			--without-curses \
			--without-system-zlib

gdbserver-install:
	${INSTALL_DIR} ${IDIR_GDBSERVER}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/gdbserver ${IDIR_GDBSERVER}/usr/bin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
