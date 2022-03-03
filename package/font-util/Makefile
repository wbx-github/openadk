# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		font-util
PKG_VERSION:=		1.3.2
PKG_RELEASE:=		1
PKG_HASH:=		f115a3735604de1e852a4bf669be0269d8ce8f21f8e0e74ec5934b31dadc1e76
PKG_DESCR:=		font utility
PKG_SECTION:=		x11/fonts
PKG_URL:=		http://www.x.org/
PKG_SITES:=		http://www.x.org/releases/individual/font/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,FONT_UTIL,font-util,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

# XXX: Push the mapping files to a place where we can find them
# again when compiling the actual fonts. This is ugly as hell,
# especially as all font packages still need patching to avoid
# calling pkg-config (which we don't provide) in order to
# automatically find the mappings.
post-build:
	${INSTALL_DIR} ${STAGING_TARGET_DIR}/usr/share/fonts/X11/util
	${CP} ${WRKBUILD}/map-* \
		${STAGING_TARGET_DIR}/usr/share/fonts/X11/util

font-util-install:
	${INSTALL_DIR} ${IDIR_FONT_UTIL}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/ucs2any \
		${IDIR_FONT_UTIL}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/bdftruncate \
		${IDIR_FONT_UTIL}/usr/bin
	${INSTALL_DIR} ${IDIR_FONT_UTIL}/usr/share/fonts/X11/util
	${CP} ${WRKINST}/usr/share/fonts/X11/util/* \
		${IDIR_FONT_UTIL}/usr/share/fonts/X11/util

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
