# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		sqlite
PKG_VERSION:=		3.37.1
PKG_RELEASE:=		1
PKG_HASH:=		40f22a13bf38bbcd4c7ac79bcfb42a72d5aa40930c1f3f822e30ccce295f0f2e
PKG_DESCR:=		embeddable sql database cli
PKG_SECTION:=		sys/misc
PKG_BUILDDEP:=		ncurses readline
PKG_DEPENDS:=		libsqlite libreadline libncurses
PKG_URL:=		http://www.sqlite.org/
PKG_SITES:=		http://www.sqlite.org/2021/
PKG_LIBNAME:=		libsqlite
PKG_OPTS:=		dev
PKG_NOPARALLEL:=	1

DISTFILES:=		sqlite-autoconf-3370100.tar.gz
WRKDIST=		${WRKDIR}/sqlite-autoconf-3370100

PKG_SUBPKGS:=		SQLITE_CLI LIBSQLITE
PKGSD_LIBSQLITE:=	emeddable sql library
PKGSC_LIBSQLITE:=	libs/db

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,SQLITE,sqlite,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,LIBSQLITE,libsqlite,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_LIBSQLITE},${PKGSD_LIBSQLITE},${PKGSC_LIBSQLITE},${PKG_OPTS}))
$(eval $(call PKG_template,SQLITE_CLI,sqlite-cli,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_CFLAGS:=		$(filter-out -ffast-math,$(TARGET_CFLAGS))

ifeq ($(ADK_TARGET_USE_STATIC_LIBS_ONLY),y)
CONFIGURE_ARGS+=	--enable-dynamic-extensions=no
endif

CONFIGURE_ENV+=		config_BUILD_CC="${CC_FOR_BUILD}" \
			config_BUILD_CFLAGS="${CFLAGS_FOR_BUILD}" \
			config_TARGET_CC="${TARGET_CC}" \
			config_TARGET_CFLAGS="${TARGET_CFLAGS}" \
			config_TARGET_READLINE_INC="-I${STAGING_TARGET_DIR}/usr/include" \
			config_TARGET_READLINE_LIBS="-L${STAGING_TARGET_DIR}/usr/lib -lreadline -lncurses"

MAKE_FLAGS+=		LIBPTHREAD=-lm
TARGET_CPPFLAGS+=	-DSQLITE_SECURE_DELETE=1 \
			-DSQLITE_THREADSAFE=1 \
			-DSQLITE_ENABLE_FTS3=1 \
			-DSQLITE_ENABLE_UNLOCK_NOTIFY=1 \
			-DSQLITE_ENABLE_DBSTAT_VTAB=1

libsqlite-install:
	${INSTALL_DIR} ${IDIR_LIBSQLITE}/usr/lib
	${CP} ${WRKINST}/usr/lib/libsqlite3.so* ${IDIR_LIBSQLITE}/usr/lib

sqlite-cli-install:
	${INSTALL_DIR} ${IDIR_SQLITE_CLI}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/sqlite3 ${IDIR_SQLITE_CLI}/usr/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
