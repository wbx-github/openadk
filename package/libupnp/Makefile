# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		libupnp
PKG_VERSION:=		1.18.5
PKG_RELEASE:=		1
PKG_HASH:=		fe17522c605752f9f522d8cceab2a4601d75c2b701288a3bdbd9926e1bd9a9a1
PKG_DESCR:=		universal plug and play sdk library
PKG_SECTION:=		libs/net
PKG_NEEDS:=		threads
PKG_URL:=		http://pupnp.sourceforge.net/
PKG_SITES:=		https://sourceforge.net/projects/pupnp/files/release-$(PKG_VERSION)/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.bz2

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LIBUPNP,libupnp,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIGURE_ARGS+=	--disable-samples

libupnp-install:
	${INSTALL_DIR} ${IDIR_LIBUPNP}/usr/lib
	${CP} ${WRKINST}/usr/lib/lib*.so* ${IDIR_LIBUPNP}/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
