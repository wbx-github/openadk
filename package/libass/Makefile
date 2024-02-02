# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libass
PKG_VERSION:=		0.17.1
PKG_RELEASE:=		1
PKG_HASH:=		f0da0bbfba476c16ae3e1cfd862256d30915911f7abaa1b16ce62ee653192784
PKG_DESCR:=		portable subtitle renderer
PKG_SECTION:=		libs/video
PKG_DEPENDS:=		fribidi fontconfig
PKG_BUILDDEP:=		fribidi fontconfig
PKG_SITES:=		https://github.com/libass/libass/releases/download/$(PKG_VERSION)/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBASS,libass,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

libass-install:
	$(INSTALL_DIR) $(IDIR_LIBASS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libass*.so* \
		$(IDIR_LIBASS)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
