# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		xcb-proto
PKG_VERSION:=		1.16.0
PKG_RELEASE:=		1
PKG_HASH:=		a75a1848ad2a89a82d841a51be56ce988ff3c63a8d6bf4383ae3219d8d915119
PKG_DESCR:=		xml-xcb protocol descriptions
PKG_SECTION:=		dev/header
HOST_BUILDDEP:=		python3-host
PKG_SITES:=		https://xorg.freedesktop.org/archive/individual/proto/
PKG_OPTS:=		dev devonly

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,XCB_PROTO,xcb-proto,$(PKG_VERSION)-${PKG_RELEASE}))
$(eval $(call PKG_template,XCB_PROTO,xcb-proto,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

include $(ADK_TOPDIR)/mk/python3.mk

HOST_STYLE:=		auto
CONFIGURE_ENV+=		PYTHON=$(PYTHON)

hostpost-install:
	${INSTALL_DIR} ${STAGING_HOST_DIR}/usr/share/xcb
	${CP} ${WRKBUILD}/src/*.xml ${STAGING_HOST_DIR}/usr/share/xcb

post-build:
	${INSTALL_DIR} ${STAGING_TARGET_DIR}/usr/share/xcb
	${CP} ${WRKBUILD}/src/*.xml ${STAGING_TARGET_DIR}/usr/share/xcb

xcb-proto-install:
	$(INSTALL_DIR) ${STAGING_TARGET_DIR}/usr/lib/python${PYTHON_VERSION}/site-packages/xcbgen
	${CP} ${WRKINST}/usr/lib/python${PYTHON_VERSION}/site-packages/xcbgen/*.py \
		${STAGING_TARGET_DIR}/usr/lib/python${PYTHON_VERSION}/site-packages/xcbgen
	${INSTALL_DIR} ${IDIR_XCB_PROTO}/usr/lib/python${PYTHON_VERSION}/site-packages/xcbgen
	${CP} ${WRKINST}/usr/lib/python${PYTHON_VERSION}/site-packages/xcbgen/*.py \
		${IDIR_XCB_PROTO}/usr/lib/python${PYTHON_VERSION}/site-packages/xcbgen

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
