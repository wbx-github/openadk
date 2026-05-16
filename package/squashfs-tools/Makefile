# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		squashfs-tools
PKG_VERSION:=		4.7.5
PKG_RELEASE:=		1
PKG_HASH:=		547b7b7f4d2e44bf91b6fc554664850c69563701deab9fd9cd7e21f694c88ea6
PKG_DESCR:=		squashfs filesystem utilities
HOST_BUILDDEP:=		liblzo-host lz4-host
PKG_SECTION:=		sys/fs
PKG_SITES:=		https://github.com/plougher/squashfs-tools/archive/refs/tags/

DISTFILES:=		${PKG_VERSION}.tar.gz
WRKDIST=		${WRKDIR}/$(PKG_NAME)-${PKG_VERSION}

PKG_CFLINE_SQUASHFS_TOOLS:=	depends on ADK_HOST_ONLY

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,SQUASHFS-TOOLS,squashfs-tools,$(PKG_VERSION)-${PKG_RELEASE}))

HOST_STYLE:=		manual
HOST_MAKE_FLAGS+=	LZ4_SUPPORT=1 LZO_SUPPORT=1 XATTR_SUPPORT=0 XZ_SUPPORT=0 EXTRA_LDFLAGS=$(LDFLAGS_FOR_BUILD)

host-build:
	(cd ${WRKBUILD}/squashfs-tools && env ${HOST_MAKE_ENV} ${MAKE} -f ${MAKE_FILE} \
		${HOST_MAKE_FLAGS} ${HOST_ALL_TARGET})

squashfs-tools-hostinstall:
	${INSTALL_DIR} ${STAGING_HOST_DIR}/usr/bin
	${INSTALL_BIN} ${WRKBUILD}/squashfs-tools/mksquashfs \
		${STAGING_HOST_DIR}/usr/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
