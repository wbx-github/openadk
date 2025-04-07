# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		readline
PKG_VERSION:=		8.2
PKG_RELEASE:=		1
PKG_HASH:=		3feb7171f16a84ee82ca18a36d7b9be109a52c04f492a053331d7d1095007c35
PKG_DESCR:=		command line editing library
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		libncurses
PKG_BUILDDEP:=		ncurses
PKG_SITES:=		${MASTER_SITE_GNU:=readline/}
PKG_LIBNAME:=		libreadline
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,READLINE,readline,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,LIBREADLINE,libreadline,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIGURE_ARGS+= 	--with-curses
TARGET_LDFLAGS+=	-ltinfo

libreadline-install:
	${INSTALL_DIR} ${IDIR_LIBREADLINE}/usr/lib
	${CP} ${WRKINST}/usr/lib/libhistory.so* ${IDIR_LIBREADLINE}/usr/lib
	${CP} ${WRKINST}/usr/lib/libreadline.so* ${IDIR_LIBREADLINE}/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
