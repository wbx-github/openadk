# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		screen
PKG_VERSION:=		5.0.1
PKG_RELEASE:=		1
PKG_HASH:=		2dae36f4db379ffcd14b691596ba6ec18ac3a9e22bc47ac239789ab58409869d
PKG_DESCR:=		window manager for the terminal session
PKG_SECTION:=		sys/utils
PKG_DEPENDS:=		libncurses
PKG_BUILDDEP:=		ncurses
PKG_NEEDS:=		mmu
PKG_URL:=		http://www.gnu.org/software/screen/
PKG_SITES:=		${MASTER_SITE_GNU:=screen/}

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,SCREEN,screen,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ARGS+=	--disable-pam

screen-install:
	${INSTALL_DIR} ${IDIR_SCREEN}/usr/bin
	${INSTALL_BIN} ${WRKINST}/usr/bin/screen ${IDIR_SCREEN}/usr/bin/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
