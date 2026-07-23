# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		ntfs-3g
PKG_VERSION:=		2026.7.7
PKG_RELEASE:=		1
PKG_HASH:=		d67b769025d32860549d35c2147e45024d172f81c540d750390ce3602c059dab
PKG_DESCR:=		ntfs filesystem driver using fuse
PKG_SECTION:=		sys/fs
PKG_KDEPENDS:=		fuse-fs
PKG_URL:=		http://tuxera.com
PKG_SITES:=		http://tuxera.com/opensource/

DISTFILES:=		${PKG_NAME}_ntfsprogs-${PKG_VERSION}.tgz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,NTFS_3G,ntfs-3g,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ARGS+=	--disable-ldconfig \
			--disable-library

ntfs-3g-install:
	${INSTALL_DIR} ${IDIR_NTFS_3G}/bin
	${INSTALL_BIN} ${WRKINST}/bin/ntfs-3g ${IDIR_NTFS_3G}/bin
	cd ${IDIR_NTFS_3G}/bin && ln -sf ntfs-3g mount.ntfs-3g

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
