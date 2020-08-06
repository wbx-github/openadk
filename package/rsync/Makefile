# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		rsync
PKG_VERSION:=		3.2.2
PKG_RELEASE:=		1
PKG_HASH:=		644bd3841779507665211fd7db8359c8a10670c57e305b4aab61b4e40037afa8
PKG_DESCR:=		utility that provides fast incremental file transfer
PKG_SECTION:=		net/misc
PKG_DEPENDS:=		libpopt
PKG_BUILDDEP:=		popt libressl
HOST_BUILDDEP:=		libressl-host
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
