# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		libffi
PKG_VERSION:=		3.4.2
PKG_RELEASE:=		1
PKG_HASH:=		540fb721619a6aba3bdeef7d940d8e9e0e6d2c193595bc243241b77ff9e93620
PKG_DESCR:=		foreign function interface library
PKG_SECTION:=		libs/misc
HOST_BUILDDEP:=		libtool-host
PKG_URL:=		http://sourceware.org/libffi/
PKG_SITES:=		https://github.com/libffi/libffi/releases/download/v${PKG_VERSION}/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,LIBFFI,libffi,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,LIBFFI,libffi,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

AUTOTOOL_STYLE:=	autoreconf
HOST_STYLE:=		auto
HOST_CONFIGURE_ARGS+=	--disable-builddir --with-pic --disable-symvers
CONFIGURE_ARGS+=	--disable-builddir --with-pic --disable-symvers

ifeq ($(ADK_PACKAGE_OPENJDK7),y)
CONFIGURE_ARGS+=	--enable-static
endif

libffi-install:
	${INSTALL_DIR} ${IDIR_LIBFFI}/usr/lib
	${CP} ${WRKINST}/usr/lib*/libffi.so* ${IDIR_LIBFFI}/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
