# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		neon
PKG_VERSION:=		0.32.1
PKG_RELEASE:=		1
PKG_HASH:=		05c54bc115030c89e463a4fb28d3a3f8215879528ba5ca70d676d3d21bf3af52
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
