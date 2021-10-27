# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		gdbserver
PKG_VERSION:=		11.1
PKG_RELEASE:=		1
PKG_HASH:=		cccfcc407b20d343fb320d4a9a2110776dd3165118ffd41f4b1b162340333f94
PKG_DESCR:=		remote program debugger utility
PKG_SECTION:=		app/debug
PKG_NEEDS:=		c++
PKG_SITES:=		${MASTER_SITE_GNU:=gdb/}
PKG_DEPENDS:=		libthread-db libgmp
PKG_BUILDDEP:=		gmp

PKG_LIBC_DEPENDS:=	!musl
PKG_ARCH_DEPENDS:=	!microblaze

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

CONFIGURE_ARGS+=	--enable-static
ifneq ($(ADK_TARGET_BINFMT_FLAT)$(ADK_TARGET_USE_STATIC_LIBS_ONLY)$(ADK_TARGET_USE_STATIC_AND_SHARED_LIBS),)
TARGET_LDFLAGS+=	-static-libstdc++
CONFIGURE_ARGS+=	--disable-build-with-cxx --with-libthread-db=$(STAGING_TARGET_DIR)/usr/lib/libthread_db.a --disable-source-highlight
endif

gdbserver-install:
	${INSTALL_DIR} ${IDIR_GDBSERVER}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/gdbserver ${IDIR_GDBSERVER}/usr/bin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
