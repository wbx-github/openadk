# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		apr-util
PKG_VERSION:=		1.6.1
PKG_RELEASE:=		1
PKG_HASH:=		d3e12f7b6ad12687572a3a39475545a072608f4ba03a6ce8a3778f607dd0035b
PKG_DESCR:=		apache portable runtime utility library
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		libexpat apr
PKG_BUILDDEP:=		expat apr
PKG_URL:=		http://apr.apache.org/
PKG_SITES:=		http://www.apache.org/dist/apr/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.bz2

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,APR_UTIL,apr-util,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIGURE_ARGS+=	--without-berkeley-db \
			--with-apr=${STAGING_TARGET_DIR}/usr \
			--with-expat=${STAGING_TARGET_DIR}/usr \
			--without-iconv
XAKE_FLAGS+=		apr_builddir=${STAGING_TARGET_DIR}/usr/share/build-1 \
			apr_builders=${STAGING_TARGET_DIR}/usr/share/build-1

apr-util-install:
	${INSTALL_DIR} ${IDIR_APR_UTIL}/usr/lib
	${CP} ${WRKINST}/usr/lib/libaprutil-1.so* ${IDIR_APR_UTIL}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
