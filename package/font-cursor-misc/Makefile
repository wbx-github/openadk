# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		font-cursor-misc
PKG_VERSION:=		1.0.4
PKG_RELEASE:=		1
PKG_HASH:=		37ef2363b3cfa6f5e20b65feab736db77fad484127c267b78de95d55fa39f61d
PKG_DESCR:=		font cursor-misc
PKG_SECTION:=		x11/fonts
PKG_URL:=		http://www.x.org/
PKG_SITES:=		http://www.x.org/releases/individual/font/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/host.mk
include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call HOST_template,FONT_CURSOR_MISC,font-cursor-misc,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,FONT_CURSOR_MISC,font-cursor-misc,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

font-cursor-misc-install:
	${INSTALL_DIR} ${IDIR_FONT_CURSOR_MISC}/usr/share/fonts/X11/misc
	${CP} ${WRKINST}/usr/share/fonts/X11/misc/cursor.pcf.gz \
		${IDIR_FONT_CURSOR_MISC}/usr/share/fonts/X11/misc

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
