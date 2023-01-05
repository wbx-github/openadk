# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		bzip2
PKG_VERSION:=		1.0.8
PKG_RELEASE:=		1
PKG_HASH:=		ab5a03176ee106d3f0fa90e381da478ddae405918153cca248e682cd0c4a2269
PKG_DESCR:=		compression utility
PKG_SECTION:=		app/archive
PKG_BUILDDEP:=		bzip2-host
PKG_DEPENDS:=		libbz2
HOST_BUILDDEP:=		patch-host
PKG_URL:=		http://www.bzip.org/
PKG_SITES:=		https://sourceware.org/pub/bzip2/
PKG_LIBNAME:=		libbz2
PKG_OPTS:=		dev

DISTFILES:=             ${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_SUBPKGS:=		BZIP2 LIBBZ2
PKGSD_LIBBZ2:=		bzip2 compression library
PKGSC_LIBBZ2:=		libs/comp

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,BZIP2,bzip2,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,BZIP2,bzip2,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,LIBBZ2,libbz2,${PKG_VERSION}-${PKG_RELEASE},,${PKGSD_LIBBZ2},${PKGSC_LIBBZ2},${PKG_OPTS}))

HOST_STYLE:=		manual
HOST_MAKE_FILE:=	Makefile-libbz2_so

ifneq ($(ADK_TARGET_USE_STATIC_LIBS_ONLY),y)
MAKE_FILE:=		Makefile-libbz2_so
BIN_FILE:=		bzip2-shared
else
BIN_FILE:=		bzip2
endif

CONFIG_STYLE:=		manual
TARGET_CFLAGS+=		-fPIC 
XAKE_FLAGS+=		PREFIX=${WRKINST}/usr CROSS_COMPILE=1
INSTALL_STYLE:=		manual

host-build:
	(cd ${WRKBUILD} && env ${HOST_MAKE_ENV} ${MAKE} -f ${HOST_MAKE_FILE} \
		PREFIX=${HOST_WRKINST}/usr ${HOST_ALL_TARGET})

bzip2-hostinstall:
	${INSTALL_DIR} ${STAGING_HOST_DIR}/usr/include
	$(CP) ${WRKBUILD}/bzlib.h ${STAGING_HOST_DIR}/usr/include
	${INSTALL_DIR} ${STAGING_HOST_DIR}/usr/lib
	$(CP) ${WRKBUILD}/libbz2.so* ${STAGING_HOST_DIR}/usr/lib
	(cd ${STAGING_HOST_DIR}/usr/lib; ln -sf libbz2.so.1.0.8 libbz2.so)
	${INSTALL_DIR} ${STAGING_HOST_DIR}/usr/bin
	$(INSTALL_BIN) ${WRKBUILD}/bzip2-shared ${STAGING_HOST_DIR}/usr/bin/bzip2

do-install:
	${INSTALL_DIR} $(STAGING_TARGET_DIR)/usr/include
	$(CP) $(WRKBUILD)/bzlib.h $(STAGING_TARGET_DIR)/usr/include
ifeq ($(ADK_TARGET_USE_STATIC_LIBS_ONLY),y)
	$(CP) ${WRKBUILD}/libbz2.a ${STAGING_TARGET_DIR}/usr/lib
endif

libbz2-install:
	${INSTALL_DIR} ${IDIR_LIBBZ2}/usr/lib
	$(CP) ${WRKBUILD}/libbz2.so* \
		${IDIR_LIBBZ2}/usr/lib
	$(CP) ${WRKBUILD}/libbz2.so* \
		${STAGING_TARGET_DIR}/usr/lib
	(cd ${STAGING_TARGET_DIR}/usr/lib; ln -sf libbz2.so.1.0.8 libbz2.so)
	${INSTALL_DIR} $(IDIR_LIBBZ2_DEV)/usr/include
	$(CP) $(WRKBUILD)/bzlib.h $(IDIR_LIBBZ2_DEV)/usr/include

bzip2-install:
	${INSTALL_DIR} ${IDIR_BZIP2}/usr/bin
	${INSTALL_BIN} ${WRKBUILD}/$(BIN_FILE) ${IDIR_BZIP2}/usr/bin/bzip2

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
