# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		mariadb
PKG_VERSION:=		10.11.7
PKG_RELEASE:=		1
PKG_HASH:=		5239a245ed90517e96396605cd01ccd8f73cd7442d1b3076b6ffe258110e5157
PKG_DESCR:=		sql client library
PKG_SECTION:=		libs/db
PKG_DEPENDS:=		libncurses zlib libevent libpcre boost libfmt libkrb5
PKG_BUILDDEP:=		cmake-host mariadb-host ncurses zlib readline libevent
PKG_BUILDDEP+=		boost fmt gnutls pcre2 krb5
HOST_BUILDDEP:=		cmake-host
PKG_NEEDS:=		c++
PKG_URL:=		http://www.mariadb.org/
PKG_SITES=		https://downloads.mariadb.org/interstitial/mariadb-$(PKG_VERSION)/source/
PKG_LIBNAME:=		libmariadbclient
PKG_OPTS:=		dev

PKG_CFLINE_MARIADB:=	select ADK_PACKAGE_BOOST_DATE_TIME

# atomic ops not implemented
PKG_ARCH_DEPENDS:=	!mips

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,MARIADB,mariadb,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,LIBMARIADBCLIENT,libmariadbclient,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

MAKE_ENV+=		VERBOSE=1

HOST_STYLE:=		manual
HOST_ALL_TARGET:=	import_executables

CONFIG_STYLE:=		cmake
CMAKE_FLAGS+=		-DCMAKE_CROSSCOMPILING=ON \
			-DIMPORT_EXECUTABLES=${BASE_DIR}/host_build_${GNU_HOST_NAME}/w-$(PKG_NAME)-$(PKG_VERSION)-$(PKG_RELEASE)-host/$(PKG_NAME)-$(PKG_VERSION)/import_executables.cmake \
			-DWITHOUT_SERVER=OFF \
			-DWITH_SSL=bundled \
			-DWITH_SYSTEMD=auto \
			-DSECURITY_HARDENED=OFF \
			-DWITHOUT_DYNAMIC_PLUGINS=ON \
			-DWITHOUT_MROONGA=ON \
			-DWITHOUT_TOKUDB=ON \
			-DSTACK_DIRECTION=-1 \
			-DWITH_JEMALLOC=OFF \
			-DWITH_UNIT_TESTS=OFF

host-configure:
	cd ${WRKBUILD} && PATH='${HOST_PATH}' cmake .

host-build:
	cd ${WRKBUILD} && env ${HOST_MAKE_ENV} ${MAKE} -f ${MAKE_FILE} \
		${HOST_MAKE_FLAGS} ${HOST_ALL_TARGET} $(MAKE_TRACE)

mariadb-hostinstall:
	@echo

libmariadbclient-install:
	${INSTALL_DIR} ${IDIR_LIBMARIADBCLIENT}/usr/lib
	${CP} ${WRKINST}/usr/lib/libmysqlclient.so* \
	    ${IDIR_LIBMARIADBCLIENT}/usr/lib
	${CP} ${WRKINST}/usr/lib/libmariadb.so* \
	    ${IDIR_LIBMARIADBCLIENT}/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
