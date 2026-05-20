# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		libtool
PKG_VERSION:=		2.5.4
PKG_RELEASE:=		1
PKG_HASH:=		f81f5860666b0bc7d84baddefa60d1cb9fa6fceb2398cc3baca6afaa60266675
PKG_DESCR:=		generic dynamic object loading library
PKG_SECTION:=		dev/tools
PKG_BUILDDEP:=		m4-host libtool-host
HOST_BUILDDEP:=		automake-host
PKG_URL:=		http://www.gnu.org/software/libtool/
PKG_SITES:=		${MASTER_SITE_GNU:=libtool/}
PKG_LIBNAME:=		libltdl
PKG_OPTS:=		dev

PKG_SUBPKGS:=		LIBTOOL LIBLTDL
PKGSC_LIBLTDL:=		libs/misc

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,LIBTOOL,libtool,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,LIBTOOL,libtool,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,LIBLTDL,libltdl,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKGSC_LIBLTDL},${PKG_OPTS}))

CONFIGURE_ARGS+=	--enable-ltdl-install
XAKE_FLAGS+=		HELP2MAN=/bin/echo
HOST_CONFIGURE_ARGS+=	--enable-ltdl-install --disable-shared
HOST_XAKE_FLAGS+=	HELP2MAN=/bin/echo

libtool-install:
	${INSTALL_DIR} ${IDIR_LIBTOOL}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/libtool ${IDIR_LIBTOOL}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/libtoolize ${IDIR_LIBTOOL}/usr/bin

libltdl-install:
	${INSTALL_DIR} ${IDIR_LIBLTDL}/usr/lib
	${CP} ${WRKINST}/usr/lib/libltdl.so* ${IDIR_LIBLTDL}/usr/lib/

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
