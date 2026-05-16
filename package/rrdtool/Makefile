# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		rrdtool
PKG_VERSION:=		1.9.0
PKG_RELEASE:=		1
PKG_HASH:=		5e65385e51f4a7c4b42aa09566396c20e7e1a0a30c272d569ed029a81656e56b
PKG_DESCR:=		round robin database management library
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		libart libfreetype libpng zlib
PKG_DEPENDS+=		glib cairo pango
PKG_BUILDDEP:=		libxml2 cgilib freetype libart libpng
PKG_BUILDDEP+=		glib cairo pango
PKG_URL:=		https://oss.oetiker.ch/rrdtool/
PKG_SITES:=		https://github.com/oetiker/rrdtool-1.x/releases/download/v$(PKG_VERSION)/
PKG_LIBNAME:=		librrd
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_CFLINE_RRDTOOL:=	select ADK_PACKAGE_CAIRO_WITH_PNG@

PKG_SUBPKGS:=		LIBRRD RRDCGI RRDTOOL
PKGSC_RRDCGI:=		sys/misc
PKGSD_RRDCGI:=		RRD CGI
PKGSC_RRDTOOL:=		sys/misc
PKGSD_RRDTOOL:=		RRD tool

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LIBRRD,librrd,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))
$(eval $(call PKG_template,RRDCGI,rrdcgi,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKGSC_RRDCGI}))
$(eval $(call PKG_template,RRDTOOL,rrdtool,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKGSC_RRDTOOL}))

CONFIGURE_ENV+=		rd_cv_ieee_works=yes
CONFIGURE_ARGS+=	--enable-rrdcgi \
			--disable-mmap \
			--disable-perl \
			--disable-ruby \
			--disable-tcl \
			--disable-python \
			--disable-libwrap \
			--disable-docs \
			--disable-examples
TARGET_CPPFLAGS+=	-I${STAGING_TARGET_DIR}/usr/include/freetype2
TARGET_LDFLAGS+=	-lglib-2.0 -lm

rrdtool-install:
	${INSTALL_DIR} ${IDIR_RRDTOOL}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/rrdtool ${WRKINST}/usr/bin/rrdupdate \
	               ${IDIR_RRDTOOL}/usr/bin/

rrdcgi-install:
	${INSTALL_DIR} ${IDIR_RRDCGI}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/rrdcgi ${IDIR_RRDCGI}/usr/bin/

librrd-install:
	${INSTALL_DIR} ${IDIR_LIBRRD}/usr/lib
	${CP} ${WRKINST}/usr/lib/librrd*.so* ${IDIR_LIBRRD}/usr/lib/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
