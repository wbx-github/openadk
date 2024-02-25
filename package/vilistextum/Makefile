# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		vilistextum
PKG_VERSION:=		2.6.9
PKG_RELEASE:=		1
PKG_HASH:=		3a16b4d70bfb144e044a8d584f091b0f9204d86a716997540190100c20aaf88d
PKG_DESCR:=		html to ascii converter
PKG_SECTION:=		net/mail
PKG_SITES:=		http://bhaak.net/vilistextum/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,VILISTEXTUM,vilistextum,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_CFLAGS+=		-fcommon

vilistextum-install:
	${INSTALL_DIR} ${IDIR_VILISTEXTUM}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/vilistextum \
		 ${IDIR_VILISTEXTUM}/usr/bin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
