# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		fuse
PKG_VERSION:=		3.16.2
PKG_RELEASE:=		1
PKG_HASH:=		1bc306be1a1f4f6c8965fbdd79c9ccca021fdc4b277d501483a711cbd7dbcd6c
PKG_DESCR:=		filesystem in userspace utility
PKG_SECTION:=		sys/fs
PKG_DEPENDS:=		libfuse
PKG_SITES:=		https://github.com/libfuse/libfuse/archive/refs/tags/
PKG_LIBNAME:=		libfuse
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz
WRKDIST=		$(WRKDIR)/libfuse-$(PKG_NAME)-$(PKG_VERSION)

PKG_SUBPKGS:=		FUSE_UTILS LIBFUSE
PKGSD_LIBFUSE:=		filesystem in userspace library
PKGSC_LIBFUSE:=		libs/misc

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,FUSE_UTILS,fuse-utils,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,LIBFUSE,libfuse,${PKG_VERSION}-${PKG_RELEASE},,${PKGSD_LIBFUSE},${PKGSC_LIBFUSE},${PKG_OPTS}))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

MESON_FLAGS+=		-Dinitscriptdir="" \
			-Dudevrulesdir=""

fuse-utils-install:
	${INSTALL_DIR} ${IDIR_FUSE_UTILS}/usr/bin
	${CP} ${WRKINST}/usr/bin/fusermount3 ${IDIR_FUSE_UTILS}/usr/bin

libfuse-install:
	${INSTALL_DIR} ${IDIR_LIBFUSE}/usr/lib
	${CP} ${WRKINST}/usr/lib/libfuse3.so* \
		${IDIR_LIBFUSE}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
