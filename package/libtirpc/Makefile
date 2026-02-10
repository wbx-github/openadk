# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		libtirpc
PKG_VERSION:=		1.3.7
PKG_RELEASE:=		1
PKG_HASH:=		b47d3ac19d3549e54a05d0019a6c400674da716123858cfdb6d3bdd70a66c702
PKG_DESCR:=		transport independent rpc library
PKG_SECTION:=		libs/net
PKG_URL:=		http://sourceforge.net/projects/libtirpc/
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=libtirpc/}
PKG_OPTS:=		dev

PKG_FLAVOURS_LIBTIRPC:=	WITH_IPV6 WITH_GSS
PKGFD_WITH_IPV6:=	enable ipv6 support
PKGFD_WITH_GSS:=	enable gss support
PKGFB_WITH_GSS:=	libgssglue krb5
PKGFS_WITH_GSS:=	libgssglue

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.bz2

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LIBTIRPC,libtirpc,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

TARGET_CFLAGS+=		-DGQ
MAKE_ENV+=		V=1
HOST_CPPFLAGS+=		-I/usr/include/tirpc

ifeq (${ADK_PACKAGE_LIBTIRPC_WITH_GSS},y)
CONFIGURE_ARGS+=	--enable-gssapi
else
CONFIGURE_ARGS+=	--disable-gssapi
endif

ifeq (${ADK_PACKAGE_LIBTIRPC_WITH_IPV6},y)
CONFIGURE_ARGS+=	--enable-ipv6
CFG:=			.ipv6
else
CONFIGURE_ARGS+=	--disable-ipv6
endif
CONFIGURE_ARGS+=	--enable-rpcdb

libtirpc-install:
	${INSTALL_DIR} ${IDIR_LIBTIRPC}/usr/lib ${IDIR_LIBTIRPC}/etc
	${CP} ${WRKINST}/usr/lib/libtirpc*.so* ${IDIR_LIBTIRPC}/usr/lib/
	${CP} ./files/netconfig$(CFG) ${IDIR_LIBTIRPC}/etc/netconfig

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
