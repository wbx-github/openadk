# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		ccache
PKG_VERSION:=		4.13.4
PKG_RELEASE:=		1
PKG_HASH:=		4a7ef278b39d031b9ec524c0778d24bdb3e761940ed368060b54594f15559537
PKG_DESCR:=		compiler cache utility
PKG_SECTION:=		dev/tools
HOST_BUILDDEP:=		cmake-host
PKG_SITES:=		https://github.com/ccache/ccache/releases/download/v$(PKG_VERSION)/

PKG_CFLINE_CCACHE:=	depends on ADK_HOST_ONLY

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,CCACHE,ccache,$(PKG_VERSION)-${PKG_RELEASE}))

HOST_STYLE:=		cmake

host-build:
	(cd ${WRKBUILD} && env ${HOST_MAKE_ENV} ${MAKE} -f ${MAKE_FILE} \
		${HOST_MAKE_FLAGS} ${HOST_ALL_TARGET})

hostpost-install:
	(cd ${WRKBUILD} && env ${HOST_MAKE_ENV} ${MAKE} -f ${MAKE_FILE} \
		${HOST_FAKE_FLAGS} ${HOST_INSTALL_TARGET})

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
