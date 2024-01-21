# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		dosfstools
PKG_VERSION:=		4.2
PKG_RELEASE:=		1
PKG_HASH:=		64926eebf90092dca21b14259a5301b7b98e7b1943e8a201c7d726084809b527
PKG_DESCR:=		utilities to create and check fat filesystems
PKG_SECTION:=		sys/fs
PKG_URL:=		http://www.daniel-baumann.ch/software/dosfstools/
PKG_SITES:=		https://github.com/dosfstools/dosfstools/releases/download/v4.2/

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_CFLINE_DOSFSTOOLS:=	select BUSYBOX_FSCK

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,DOSFSTOOLS,dosfstools,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,DOSFSTOOLS,dosfstools,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

HOST_CONFIGURE_ARGS+=	--enable-compat-symlinks

dosfstools-install:
	${INSTALL_DIR} ${IDIR_DOSFSTOOLS}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/usr/sbin/fsck.fat ${IDIR_DOSFSTOOLS}/usr/sbin
	${INSTALL_BIN} ${WRKINST}/usr/sbin/mkfs.fat ${IDIR_DOSFSTOOLS}/usr/sbin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
