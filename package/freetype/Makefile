# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		freetype
PKG_VERSION:=		2.11.1
PKG_RELEASE:=		1
PKG_HASH:=		f8db94d307e9c54961b39a1cc799a67d46681480696ed72ecf78d4473770f09b
PKG_DESCR:=		free, high-quality and portable font engine
PKG_SECTION:=		libs/fonts
PKG_DEPENDS:=		zlib
PKG_BUILDDEP:=		zlib
PKG_URL:=		http://www.freetype.org/
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=freetype/}
PKG_LIBNAME:=		libfreetype
PKG_OPTS:=		dev

DISTFILES:=             ${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,LIBFREETYPE,libfreetype,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,LIBFREETYPE,libfreetype,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

HOST_STYLE:=		auto
HOST_CONFIGURE_ARGS+=	--with-zlib \
			--without-png \
			--without-bzip2 \
			--enable-freetype-config
CONFIGURE_ARGS+=	--with-zlib \
			--without-png \
			--with-harfbuzz=no \
			--without-bzip2 \
			--enable-freetype-config

hostpost-install:
	$(SED) 's:^includedir=.*:includedir="$${prefix}/include":' \
                -e 's:^libdir=.*:libdir="$${exec_prefix}/lib":' \
                $(STAGING_HOST_DIR)/usr/bin/freetype-config


libfreetype-install:
	${INSTALL_DIR} ${IDIR_LIBFREETYPE}/usr/lib
	${CP} ${WRKINST}/usr/lib/libfreetype.so* ${IDIR_LIBFREETYPE}/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
