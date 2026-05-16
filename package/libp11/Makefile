# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		libp11
PKG_VERSION:=		0.4.18
PKG_RELEASE:=		1
PKG_HASH:=		9292de67ca73aba1deacf577c9086b595765f36ef47712cfeb49fa31f6e772fb
PKG_DESCR:=		library implementing a small layer on top of pkcs11 api
PKG_SECTION:=		libs/crypto
PKG_DEPENDS:=		libltdl libopenssl
PKG_BUILDDEP:=		libtool openssl
PKG_URL:=		https://github.com/OpenSC/libp11/wiki
PKG_SITES:=		https://github.com/OpenSC/libp11/releases/download/$(PKG_NAME)-$(PKG_VERSION)/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LIBP11,libp11,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

libp11-install:
	${INSTALL_DIR} ${IDIR_LIBP11}/usr/lib
	${CP} ${WRKINST}/usr/lib/libp11.so* ${IDIR_LIBP11}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
