# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		libmms
PKG_VERSION:=		0.6.4
PKG_RELEASE:=		1
PKG_HASH:=		3c05e05aebcbfcc044d9e8c2d4646cd8359be39a3f0ba8ce4e72a9094bee704f
PKG_DESCR:=		common library for parsing mms:// type network streams
PKG_SECTION:=		libs/audio
PKG_BUILDDEP:=		glib
PKG_DEPENDS:=		glib
PKG_URL:=		http://libmms.sourceforge.net/
PKG_SITES:=		https://sourceforge.net/projects/libmms/files/libmms/$(PKG_VERSION)/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LIBMMS,libmms,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

libmms-install:
	${INSTALL_DIR} ${IDIR_LIBMMS}/usr/lib
	${CP} ${WRKINST}/usr/lib/libmms.so* ${IDIR_LIBMMS}/usr/lib/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
