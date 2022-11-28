# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		file
PKG_VERSION:=		5.41
PKG_RELEASE:=		2
PKG_HASH:=		13e532c7b364f7d57e23dfeea3147103150cb90593a57af86c10e4f6e411603f
PKG_DESCR:=		file type guesser
PKG_SECTION:=		sys/utils
PKG_DEPENDS:=		libmagic magic
PKG_URL:=		http://www.darwinsys.com/file
PKG_SITES:=		ftp://ftp.astron.com/pub/file/
PKG_LIBNAME:=		libmagic
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_SUBPKGS:=		FILE LIBMAGIC MAGIC
PKGSD_LIBMAGIC:=	file type guesser library
PKGSC_LIBMAGIC:=	libs/misc
PKGSD_MAGIC:=		magic file
PKGSC_MAGIC:=		sys/misc

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,FILE,file,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,FILE,${PKG_NAME},${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,LIBMAGIC,libmagic,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_LIBMAGIC},${PKGSD_LIBMAGIC},${PKGSC_LIBMAGIC},${PKG_OPTS}))
$(eval $(call PKG_template,MAGIC,magic,${PKG_VERSION}-${PKG_RELEASE},${PKGSS_MAGIC},${PKGSD_MAGIC},${PKGSC_MAGIC}))

AUTOTOOL_STYLE:=	autoreconf

ifeq ($(ADK_TARGET_USE_STATIC_LIBS_ONLY),y)
MAKE_FLAGS+=		LDFLAGS="$(TARGET_LDFLAGS) -all-static"
endif

HOST_CONFIGURE_ARGS+=	--enable-static \
			--disable-shared \
			--disable-warnings

file-install:
	${INSTALL_DIR} ${IDIR_FILE}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/file ${IDIR_FILE}/usr/bin

magic-install:
	${INSTALL_DIR} ${IDIR_MAGIC}/usr/share/misc
	${INSTALL_DATA} ${WRKINST}/usr/share/misc/magic.mgc \
		${IDIR_MAGIC}/usr/share/misc

libmagic-install:
	${INSTALL_DIR} ${IDIR_LIBMAGIC}/usr/lib
	${CP} ${WRKINST}/usr/lib/libmagic.so* ${IDIR_LIBMAGIC}/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
