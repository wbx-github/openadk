# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		alsa-utils
PKG_VERSION:=		1.2.10
PKG_RELEASE:=		1
PKG_HASH:=		104b62ec7f02a7ce16ca779f4815616df1cc21933503783a9107b5944f83063a
PKG_DESCR:=		mixer/player/record utilities
PKG_SECTION:=		mm/audio
PKG_DEPENDS:=		alsa-lib
PKG_BUILDDEP:=		alsa-lib
PKG_NEEDS:=		threads
PKG_URL:=		http://www.alsa-project.org/
PKG_SITES:=		ftp://ftp.alsa-project.org/pub/utils/

PKG_FLAVOURS_ALSA_UTILS:=WITH_ALSAMIXER
PKGFS_WITH_ALSAMIXER:=	libncurses
PKGFD_WITH_ALSAMIXER:=	include alsamixer ncurses applet
PKGFB_WITH_ALSAMIXER:=	ncurses

DISTFILES:=             ${PKG_NAME}-${PKG_VERSION}.tar.bz2

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,ALSA_UTILS,alsa-utils,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_CPPFLAGS+=	-D_GNU_SOURCE -D_POSIX_SOURCE
CONFIGURE_ARGS+=	--disable-xmlto
ifeq (${ADK_PACKAGE_ALSA_UTILS_WITH_ALSAMIXER},y)
CONFIGURE_ARGS+=	--enable-alsamixer
TARGET_LDFLAGS+=	-ltinfo
else
CONFIGURE_ARGS+=	--disable-alsamixer
endif

alsa-utils-install:
	${INSTALL_DIR} ${IDIR_ALSA_UTILS}/usr/bin
	${CP} ${WRKINST}/usr/bin/{aplay,amixer,arecord,amidi,aconnect} ${IDIR_ALSA_UTILS}/usr/bin
ifeq ($(ADK_TARGET_SYSTEM_RASPBERRY_PI),y)
	$(INSTALL_DIR) $(IDIR_ALSA_UTILS)/etc/amixer.d
	$(INSTALL_BIN) ./files/raspberry-pi.sh \
		$(IDIR_ALSA_UTILS)/etc/amixer.d
endif
ifeq (${ADK_PACKAGE_ALSA_UTILS_WITH_ALSAMIXER},y)
	${INSTALL_BIN} ${WRKINST}/usr/bin/alsamixer \
		${IDIR_ALSA_UTILS}/usr/bin
endif

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
