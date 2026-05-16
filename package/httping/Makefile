# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		httping
PKG_VERSION:=		4.4.0
PKG_RELEASE:=		1
PKG_HASH:=		87fa2da5ac83c4a0edf4086161815a632df38e1cc230e1e8a24a8114c09da8fd
PKG_DESCR:=		like ping but for http-requests
PKG_SECTION:=		net/http
PKG_DEPENDS:=		libopenssl ca-certificates
PKG_BUILDDEP:=		cmake-host openssl
PKG_NEEDS:=		intl
PKG_SITES:=		https://github.com/folkertvanheusden/HTTPing/archive/refs/tags/

PKG_CFLINE_HTTPING:=	depends on ADK_BROKEN

DISTFILES:=		v${PKG_VERSION}.tar.gz
WRKDIST=		${WRKDIR}/HTTPing-${PKG_VERSION}

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,HTTPING,httping,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CMAKE_FLAGS+=		-DUSE_SSL=ON \
			-DUSE_GETTEXT=OFF

CONFIG_STYLE:=		cmake
INSTALL_STYLE:=		manual

httping-install:
	${INSTALL_DIR} ${IDIR_HTTPING}/usr/bin
	${INSTALL_BIN} ${WRKBUILD}/httping ${IDIR_HTTPING}/usr/bin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
