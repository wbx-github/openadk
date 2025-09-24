# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		font-alias
PKG_VERSION:=		1.0.5
PKG_RELEASE:=		1
PKG_HASH:=		f8e0ca6537003f11fcaf36c598f7de9c0428f8ed587388a8a37ff18ccc597730
PKG_DESCR:=		font alias utility
PKG_SECTION:=		x11/fonts
PKG_URL:=		http://www.x.org/
PKG_SITES:=		http://www.x.org/releases/individual/font/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,FONT_ALIAS,font-alias,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,FONT_ALIAS,font-alias,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

font-alias-install:
	${INSTALL_DIR} ${IDIR_FONT_ALIAS}/usr/share/fonts/X11/misc
	${CP} ${WRKINST}/usr/share/fonts/X11/misc/fonts.alias \
		${IDIR_FONT_ALIAS}/usr/share/fonts/X11/misc
	${INSTALL_DIR} ${IDIR_FONT_ALIAS}/usr/share/fonts/X11/100dpi
	${CP} ${WRKINST}/usr/share/fonts/X11/100dpi/fonts.alias \
		${IDIR_FONT_ALIAS}/usr/share/fonts/X11/100dpi
	${INSTALL_DIR} ${IDIR_FONT_ALIAS}/usr/share/fonts/X11/75dpi
	${CP} ${WRKINST}/usr/share/fonts/X11/75dpi/fonts.alias \
		${IDIR_FONT_ALIAS}/usr/share/fonts/X11/75dpi

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
