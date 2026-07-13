# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		cmake
PKG_VERSION:=		4.4.0
PKG_RELEASE:=		1
PKG_HASH:=		65757f442fdd242e27f1728fc26dc0cba4164f7a0791a5c788631c00080369bc
PKG_DESCR:=		build utility
PKG_SECTION:=		dev/tools
HOST_BUILDDEP:=		curl-host
PKG_URL:=		http://www.cmake.org/
PKG_SITES:=		https://github.com/Kitware/CMake/releases/download/v$(PKG_VERSION)/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_CFLINE_CMAKE:=	depends on ADK_HOST_ONLY

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,CMAKE,cmake,$(PKG_VERSION)-${PKG_RELEASE}))

HOST_STYLE:=		manual

host-configure:
	(cd $(WRKBUILD); ./configure --prefix=${STAGING_HOST_DIR}/usr --system-curl --parallel=${ADK_MAKE_JOBS} )

host-build:
	(cd ${WRKBUILD} && env ${HOST_MAKE_ENV} ${MAKE} -j${ADK_MAKE_JOBS} -f ${MAKE_FILE} \
		${HOST_MAKE_FLAGS} ${HOST_ALL_TARGET} VERBOSE=1) $(MAKE_TRACE)

cmake-hostinstall:
	cd ${WRKBUILD} && env ${HOST_MAKE_ENV} ${MAKE} -j${ADK_MAKE_JOBS} -f ${MAKE_FILE} \
		${HOST_FAKE_FLAGS} ${HOST_INSTALL_TARGET} $(MAKE_TRACE)

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
