# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libxcb
PKG_VERSION:=		1.16
PKG_RELEASE:=		1
PKG_HASH:=		bc0f75f84b28e6496a19a1d094d7e47def861a50cb7cce5b23b62eecdc2a4479
PKG_DESCR:=		interface to the x window system protocol
PKG_SECTION:=		x11/libs
PKG_BUILDDEP:=		python3 libpthread-stubs libxslt libXau xcb-proto
HOST_BUILDDEP:=		libXau-host libpthread-stubs-host xcb-proto-host
PKG_SITES:=		http://xcb.freedesktop.org/dist/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,LIBXCB,libxcb,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,LIBXCB,libxcb,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

include $(ADK_TOPDIR)/mk/python3.mk

HOST_STYLE:=		auto
CONFIGURE_ENV+=		PYTHONPATH=$(PYTHON) PYTHON=python3

libxcb-install:
	${INSTALL_DIR} ${IDIR_LIBXCB}/usr/lib
	${CP} ${WRKINST}/usr/lib/libxcb*.so* ${IDIR_LIBXCB}/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
