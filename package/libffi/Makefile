# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		libffi
PKG_VERSION:=		3.7.1
PKG_RELEASE:=		1
PKG_HASH:=		d5e9a6638ddbd2513ddb54518eb67e4bbe6fa707bcc01c10f6212f0a088d819d
PKG_DESCR:=		foreign function interface library
PKG_SECTION:=		libs/misc
HOST_BUILDDEP:=		libtool-host
PKG_URL:=		http://sourceware.org/libffi/
PKG_SITES:=		https://github.com/libffi/libffi/releases/download/v${PKG_VERSION}/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,LIBFFI,libffi,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,LIBFFI,libffi,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

HOST_CONFIGURE_ARGS+=	--disable-builddir --with-pic --disable-symvers
CONFIGURE_ARGS+=	--disable-builddir --with-pic --disable-symvers

libffi-install:
	${INSTALL_DIR} ${IDIR_LIBFFI}/usr/lib
	${CP} ${WRKINST}/usr/lib*/libffi.so* ${IDIR_LIBFFI}/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
