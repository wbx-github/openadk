# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		wdfs
PKG_VERSION:=		1.4.2
PKG_RELEASE:=		6
PKG_HASH:=		fcf2e1584568b07c7f3683a983a9be26fae6534b8109e09167e5dff9114ba2e5
PKG_DESCR:=		webdav filesystem
PKG_SECTION:=		net/fs
PKG_DEPENDS:=		fuse-utils neon glib
PKG_BUILDDEP:=		fuse neon glib
PKG_SITES:=		http://noedler.de/projekte/wdfs/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,WDFS,wdfs,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_CFLAGS+=		-std=c17

wdfs-install:
	${INSTALL_DIR} ${IDIR_WDFS}/usr/bin
	${CP} ${WRKINST}/usr/bin/wdfs ${IDIR_WDFS}/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
