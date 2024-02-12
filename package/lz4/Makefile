# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		lz4
PKG_VERSION:=		1.9.4
PKG_RELEASE:=		1
PKG_HASH:=		0b0e3aa07c8c063ddf40b082bdf7e37a1562bda40a0ff5272957f3e987e0e54b
PKG_DESCR:=		compression utility
PKG_SECTION:=		app/archive
PKG_DEPENDS:=		liblz4
PKG_URL:=		http://lz4.github.io/lz4/
PKG_SITES:=		https://github.com/lz4/lz4/archive/
PKG_OPTS:=		dev
PKG_LIBNAME:=		liblz4

DISTFILES:=		v$(PKG_VERSION).tar.gz

PKG_SUBPKGS:=		LZ4 LIBLZ4
PKGSD_LIBLZ4:=		lz4 compression library
PKGSC_LIBLZ4:=		libs/comp

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,LZ4,lz4,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,LZ4,lz4,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,LIBLZ4,liblz4,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_LIBLZ4},${PKGSD_LIBLZ4},${PKGSC_LIBLZ4},${PKG_OPTS}))

HOST_STYLE:=		manual
CONFIG_STYLE:=		manual
XAKE_FLAGS+=		PREFIX=/usr OS=Linux
HOST_XAKE_FLAGS+=	PREFIX=/usr
ALL_TARGET:=		lib lz4

host-build:
	(cd ${WRKBUILD} && env ${HOST_MAKE_ENV} ${MAKE} -f ${MAKE_FILE} \
		${HOST_MAKE_FLAGS} ${HOST_ALL_TARGET}) $(MAKE_TRACE)

lz4-hostinstall:
	cd ${WRKBUILD} && env ${HOST_MAKE_ENV} ${MAKE} -f ${MAKE_FILE} \
		${HOST_FAKE_FLAGS} DESTDIR='${STAGING_HOST_DIR}' ${HOST_INSTALL_TARGET} $(MAKE_TRACE)

lz4-install:
	${INSTALL_DIR} ${IDIR_LZ4}/usr/bin
	${CP} ${WRKINST}/usr/bin/* ${IDIR_LZ4}/usr/bin

liblz4-install:
	${INSTALL_DIR} ${IDIR_LIBLZ4}/usr/lib
	${CP} ${WRKINST}/usr/lib/liblz4.so* ${IDIR_LIBLZ4}/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
