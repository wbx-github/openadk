# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		rsync
PKG_VERSION:=		3.4.1
PKG_RELEASE:=		1
PKG_HASH:=		2924bcb3a1ed8b551fc101f740b9f0fe0a202b115027647cf69850d65fd88c52
PKG_DESCR:=		utility that provides fast incremental file transfer
PKG_SECTION:=		net/misc
PKG_DEPENDS:=		libpopt libopenssl
PKG_BUILDDEP:=		popt openssl
HOST_BUILDDEP:=		openssl-host
PKG_URL:=		http://rsync.samba.org/
PKG_SITES:=		http://rsync.samba.org/ftp/rsync/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,RSYNC,rsync,$(PKG_VERSION)-$(PKG_RELEASE)))
$(eval $(call PKG_template,RSYNC,rsync,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

HOST_CONFIGURE_ARGS:=	--disable-xxhash \
			--disable-zstd \
			--disable-lz4
CONFIGURE_ARGS:=	--disable-xxhash \
			--disable-zstd \
			--disable-lz4

rsync-install:
	${INSTALL_DIR} ${IDIR_RSYNC}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/rsync ${IDIR_RSYNC}/usr/bin

include $(ADK_TOPDIR)/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
