# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		neon
PKG_VERSION:=		0.33.0
PKG_RELEASE:=		1
PKG_HASH:=		659a5cc9cea05e6e7864094f1e13a77abbbdbab452f04d751a8c16a9447cf4b8
PKG_DESCR:=		http and webdav library
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		libxml2 zlib libressl
PKG_BUILDDEP:=		libxml2 zlib libressl
PKG_NEEDS:=		threads
PKG_URL:=		https://notroj.github.io/neon/
PKG_SITES:=		https://notroj.github.io/neon/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,NEON,neon,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIGURE_ARGS+=	--with-ssl=openssl \
			--without-gssapi \
			--with-libxml2

neon-install:
	${INSTALL_DIR} ${IDIR_NEON}/usr/lib
	$(CP) ${WRKINST}/usr/lib/libneon.so* ${IDIR_NEON}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
