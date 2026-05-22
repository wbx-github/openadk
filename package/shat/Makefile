# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		shat
PKG_VERSION:=		0.9.7
PKG_RELEASE:=		1
PKG_HASH:=		88eb26863e2637c739892af44b3476f494cbcad6ba00fb91721c85ac77adb0ee
PKG_DESCR:=		tool for nomadic routing
PKG_SECTION:=		net/misc
PKG_SITES:=		https://sourceforge.net/projects/shat/files/shat/shat-$(PKG_VERSION)/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_LIBC_DEPENDS:=	uclibc-ng glibc

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,SHAT,shat,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=          manual
BUILD_STYLE:=           manual
INSTALL_STYLE:=         manual

do-build:
	${MAKE} -C ${WRKBUILD}/src \
		CC="${TARGET_CC}" LD=${TARGET_CROSS}ld \
		CFLAGS="${TARGET_CFLAGS} -Wall -I${WRKBUILD}/include/linux/include -I${WRKBUILD}/include -DVERSION=\\\"${PKG_VERSION}\\\" -DDROP_NETBIOS"

do-install:
	${INSTALL_DIR} ${IDIR_SHAT}/usr/sbin
	${INSTALL_BIN} ${WRKBUILD}/src/shat{c,d} ${IDIR_SHAT}/usr/sbin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
