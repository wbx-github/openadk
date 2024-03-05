# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		motion
PKG_VERSION:=		4.6.0
PKG_RELEASE:=		1
PKG_HASH:=		9268df31a5ebeaf8daca4747cdcd01c86e223625b6f971e9bcec98edf35ec06f
PKG_DESCR:=		webcam motion sensing and logging
PKG_SECTION:=		mm/video
PKG_DEPENDS:=		libjpeg-turbo libmicrohttpd
PKG_BUILDDEP:=		libjpeg-turbo libmicrohttpd
PKG_NEEDS:=		threads
PKG_SITES:=		https://github.com/Motion-Project/motion/archive/refs/tags/

DISTFILES:=		release-$(PKG_VERSION).tar.gz
WRKDIST=		${WRKDIR}/${PKG_NAME}-release-${PKG_VERSION}

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,MOTION,motion,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ARGS+=	--without-ffmpeg \
			--without-jpeg-mmx \
			--without-optimizecpu \
			--without-mysql \
			--without-sqlite \
			--without-pgsql \
			--with-v4l

motion-install:
	${INSTALL_DIR} ${IDIR_MOTION}/etc ${IDIR_MOTION}/usr/bin
	$(INSTALL_DATA) ./files/motion.conf ${IDIR_MOTION}/etc
	${INSTALL_BIN} ${WRKINST}/usr/bin/motion ${IDIR_MOTION}/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
