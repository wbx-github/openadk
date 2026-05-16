# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		gpm
PKG_VERSION:=		1.20.7
PKG_RELEASE:=		2
PKG_HASH:=		c7e4661c24e05ae13547176b649bac8e3a0db2575f7dd57559f9e0b509f90f49
PKG_DESCR:=		console mouse support
PKG_SECTION:=		sys/hw
PKG_URL:=		https://www.nico.schottelius.org/software/gpm/
PKG_SITES:=		http://www.nico.schottelius.org/software/gpm/archives/
PKG_NOPARALLEL:=	1
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,GPM,gpm,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

AUTOTOOL_STYLE:=	autogen
TARGET_CPPFLAGS+=	-I${WRKSRC}/src/headers
TARGET_LDFLAGS+=	-lncursesw

gpm-install:
	${INSTALL_DIR} ${IDIR_GPM}/usr/sbin ${IDIR_GPM}/usr/lib
	${INSTALL_BIN} ${WRKINST}/usr/sbin/gpm ${IDIR_GPM}/usr/sbin/
	${CP} ${WRKINST}/usr/lib/libgpm.so.* ${IDIR_GPM}/usr/lib/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
