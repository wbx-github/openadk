# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		gdb
PKG_VERSION:=		14.2
PKG_RELEASE:=		1
PKG_HASH:=		2d4dd8061d8ded12b6c63f55e45344881e8226105f4d2a9b234040efa5ce7772
PKG_DESCR:=		program debugger
PKG_SECTION:=		app/debug
PKG_SITES:=		${MASTER_SITE_GNU:=gdb/}
PKG_DEPENDS:=		libncurses libreadline zlib libexpat libthread-db libgmp mpfr
PKG_BUILDDEP:=		ncurses readline expat zlib gmp mpfr
PKG_NEEDS:=		c++

PKG_ARCH_DEPENDS:=	!cris !avr32 !microblaze !nds32

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,GDB,gdb,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

XAKE_FLAGS+=		MAKEINFO=true V=1

WRKBUILD=		$(WRKDIR)/$(PKG_NAME)-obj

CONFIGURE_ENV+=		host_configargs='--with-libgmp-prefix="${STAGING_TARGET_DIR}/usr"'
# --enable-static is required to build libbfd.a
CONFIGURE_ARGS+=	--enable-static \
			--disable-shared \
			--without-uiout \
			--disable-tui \
			--disable-gdbtk \
			--disable-gdbserver \
			--without-x \
			--with-expat \
			--disable-sim \
			--disable-plugins \
			--disable-werror \
			--without-python \
			--without-included-gettext \
			--without-auto-load-safe-path \
			--disable-install-libiberty \
			--disable-install-libbfd \
			--with-system-zlib \
			--with-system-readline \
			--with-curses \
			--with-libexpat-prefix="${STAGING_TARGET_DIR}/usr" \
			--with-gmp="${STAGING_TARGET_DIR}/usr" \
			--with-mpfr="${STAGING_TARGET_DIR}/usr" \
			--enable-gdbmi

gdb-install:
	${INSTALL_DIR} ${IDIR_GDB}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/gdb \
		${IDIR_GDB}/usr/bin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
