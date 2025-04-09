# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		squashfs-tools
PKG_VERSION:=		4.6.1
PKG_RELEASE:=		1
PKG_HASH:=		e847913868349b6336dc73e30ae888010d03485a158188747ff010c13f051440
PKG_DESCR:=		squashfs filesystem utilities
PKG_SECTION:=		sys/fs
PKG_SITES:=		https://github.com/plougher/squashfs-tools/archive/refs/tags/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz
WRKDIST=		${WRKDIR}/$(PKG_NAME)-$(PKG_NAME)-${PKG_VERSION}

PKG_CFLINE_SQUASHFS:=	depends on ADK_HOST_ONLY

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,SQUASHFS-TOOLS,squashfs-tools,$(PKG_VERSION)-${PKG_RELEASE}))

HOST_STYLE:=		manual
HOST_MAKE_FLAGS+=	LZMA_SUPPORT=0 XATTR_SUPPORT=0 XZ_SUPPORT=0 EXTRA_LDFLAGS=$(LDFLAGS_FOR_BUILD)

host-build:
	(cd ${WRKBUILD}/squashfs-tools && env ${HOST_MAKE_ENV} ${MAKE} -f ${MAKE_FILE} \
		${HOST_MAKE_FLAGS} ${HOST_ALL_TARGET})

squashfs-tools-hostinstall:
	${INSTALL_DIR} ${STAGING_HOST_DIR}/usr/bin
	${INSTALL_BIN} ${WRKBUILD}/squashfs-tools/mksquashfs \
		${STAGING_HOST_DIR}/usr/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
