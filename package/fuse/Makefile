# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		fuse
PKG_VERSION:=		2.9.9
PKG_RELEASE:=		1
PKG_HASH:=		d0e69d5d608cc22ff4843791ad097f554dd32540ddc9bed7638cc6fea7c1b4b5
PKG_DESCR:=		filesystem in userspace utility
PKG_SECTION:=		sys/fs
PKG_DEPENDS:=		libfuse
PKG_SITES:=		https://github.com/libfuse/libfuse/releases/download/fuse-$(PKG_VERSION)/
PKG_LIBNAME:=		libfuse
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_SUBPKGS:=		FUSE_UTILS LIBFUSE
PKGSD_LIBFUSE:=		filesystem in userspace library
PKGSC_LIBFUSE:=		libs/misc

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,FUSE_UTILS,fuse-utils,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,LIBFUSE,libfuse,${PKG_VERSION}-${PKG_RELEASE},,${PKGSD_LIBFUSE},${PKGSC_LIBFUSE},${PKG_OPTS}))

CONFIGURE_ARGS+=	--enable-lib \
			--enable-util \
			--with-libiconv-prefix="${STAGING_TARGET_DIR}/usr" \
			--disable-example \
			--disable-mtab \
			--disable-kernel-module

fuse-utils-install:
	${INSTALL_DIR} ${IDIR_FUSE_UTILS}/usr/bin
	${CP} ${WRKINST}/usr/bin/fusermount ${IDIR_FUSE_UTILS}/usr/bin

libfuse-install:
	${INSTALL_DIR} ${IDIR_LIBFUSE}/usr/lib
	${CP} ${WRKINST}/usr/lib/libfuse.so* \
		${IDIR_LIBFUSE}/usr/lib
	${CP} ${WRKINST}/usr/lib/libulockmgr.so* \
		${IDIR_LIBFUSE}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
