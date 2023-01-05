# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		libxslt
PKG_VERSION:=		1.1.37
PKG_RELEASE:=		1
PKG_HASH:=		3a4b27dc8027ccd6146725950336f1ec520928f320f144eb5fa7990ae6123ab4
PKG_DESCR:=		xslt library
PKG_SECTION:=		libs/data
PKG_DEPENDS:=		libxml2
PKG_BUILDDEP:=		libxslt-host libxml2
HOST_BUILDDEP:=		libxml2-host
PKG_NEEDS:=		c++
PKG_URL:=		http://xmlsoft.org/XSLT
PKG_SITES:=		https://download.gnome.org/sources/libxslt/1.1/
PKG_OPTS:=		dev

PKG_SUBPKGS:=		LIBXSLT XSLTPROC
PKGSD_XSLTPROC:=	xslt processor utility
PKGSC_XSLTPROC:=	sys/misc

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,LIBXSLT,libxslt,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,LIBXSLT,libxslt,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))
$(eval $(call PKG_template,XSLTPROC,xsltproc,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_XSLTPROC},${PKGSC_XSLTPROC}))

AUTOTOOL_STYLE:=	autoreconf
HOST_LDFLAGS+=		-lxml2
HOST_CONFIGURE_ARGS+=	--without-python \
			--without-crypto \
			--with-libxml-prefix="${STAGING_HOST_DIR}/usr" \
			--with-libxml-include-prefix="${STAGING_HOST_DIR}/usr/include/libxml2" \
			--with-libxml-libs-prefix="${STAGING_HOST_DIR}/usr/lib"
TARGET_LDFLAGS+=	-lxml2
CONFIGURE_ARGS+=	--with-libxml-prefix="${STAGING_TARGET_DIR}/usr" \
			--with-libxml-include-prefix="${STAGING_TARGET_DIR}/usr/include/libxml2" \
			--with-libxml-libs-prefix="${STAGING_TARGET_DIR}/usr/lib" \
			--without-python \
			--without-crypto \
			--without-debug \
			--without-mem-debug \
			--without-debugger

xsltproc-install:
	${INSTALL_DIR} ${IDIR_XSLTPROC}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/xsltproc ${IDIR_XSLTPROC}/usr/bin

libxslt-install:
	${INSTALL_DIR} ${IDIR_LIBXSLT}/usr/lib
	${CP} ${WRKINST}/usr/lib/libxslt.so* ${IDIR_LIBXSLT}/usr/lib
	${CP} ${WRKINST}/usr/lib/libexslt.so* ${IDIR_LIBXSLT}/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
