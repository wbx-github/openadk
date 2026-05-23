# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		v4l-utils
PKG_VERSION:=		1.32.0
PKG_RELEASE:=		1
PKG_HASH:=		6828828a17775526eb93fb258a9294d1d1073d633c344dd71ecd4e7a1ffb7dfc
PKG_DESCR:=		video4linux utilities
PKG_SECTION:=		mm/video
PKG_BUILDDEP:=		libjpeg-turbo
PKG_SITES:=		https://www.linuxtv.org/downloads/v4l-utils/
PKG_NEEDS:=		intl
PKG_LIBNAME:=		libv4l
PKG_OPTS:=		dev

PKG_SUBPKGS:=		V4L_UTILS LIBV4L
PKGSC_LIBV4L:=		libs/video
PKGSD_LIBV4L:=		Video4Linux2 libraries

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,V4L_UTILS,v4l-utils,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,LIBV4L,libv4l,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_LIBV4L},${PKGSC_LIBV4L},${PKG_OPTS}))

TARGET_CPPFLAGS+=	-DLINUX_I2C_DEV_H
WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

MESON_FLAGS+=		-Dgconv=disabled \
			-Dv4l-wrappers=false

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

v4l-utils-install:
	$(INSTALL_DIR) $(IDIR_V4L_UTILS)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/v4l2-ctl \
		$(IDIR_V4L_UTILS)/usr/bin

libv4l-install:
	$(INSTALL_DIR) $(IDIR_LIBV4L)/usr/lib/libv4l
	$(CP) $(WRKINST)/usr/lib/libv4l*so* \
		$(IDIR_LIBV4L)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
