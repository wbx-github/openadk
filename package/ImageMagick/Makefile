# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		ImageMagick
PKG_VERSION:=		7.1.2
PKG_EXTRAVER:=		22
PKG_RELEASE:=		1
PKG_HASH:=		78de50d00e3e7b6cce5e5751460d43feda626a778904438ab83a6b51449f9452
PKG_DESCR:=		image processing and converting utility
PKG_SECTION:=		mm/image
PKG_BUILDDEP:=		libpng libjpeg-turbo libtiff fontconfig
PKG_BUILDDEP+=		pango libtool e2fsprogs
PKG_NEEDS:=		c++
PKG_URL:=		http://www.imagemagick.org/
PKG_SITES:=		https://github.com/ImageMagick/ImageMagick/archive/refs/tags/
PKG_LIBNAME:=		libimagemagick
PKG_OPTS:=		dev

PKG_ARCH_DEPENDS:=	!m68k

PKG_SUBPKGS:=		CONVERT DISPLAY LIBIMAGEMAGICK
PKGSD_LIBIMAGEMAGICK:=	imagemagick library
PKGSC_LIBIMAGEMAGICK:=	libs/image
PKGSS_LIBIMAGEMAGICK:=	libjpeg-turbo libtiff libpng
PKGSD_CONVERT:=		image processing and converting utility
PKGSC_CONVERT:=		mm/image
PKGSS_CONVERT:=		libimagemagick
PKGSD_DISPLAY:=		image display application
PKGSC_DISPLAY:=		mm/image
PKGSS_DISPLAY:=		libimagemagick libX11 libXau libXdmcp libICE libSM fontconfig libXt zlib libpng libltdl
PKGSB_DISPLAY:=		libX11

DISTFILES:=             ${PKG_VERSION}-${PKG_EXTRAVER}.tar.gz
WRKDIST=		${WRKDIR}/${PKG_NAME}-${PKG_VERSION}-$(PKG_EXTRAVER)

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBIMAGEMAGICK,libimagemagick,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKGSD_LIBIMAGEMAGICK},${PKGSC_LIBIMAGEMAGICK},${PKG_OPTS}))
$(eval $(call PKG_template,CONVERT,convert,$(PKG_VERSION)-${PKG_RELEASE},${PKGSS_CONVERT},${PKGSD_CONVERT},${PKGSC_CONVERT}))
$(eval $(call PKG_template,DISPLAY,display,$(PKG_VERSION)-${PKG_RELEASE},${PKGSS_DISPLAY},${PKGSD_DISPLAY},${PKGSC_DISPLAY}))

CONFIGURE_ENV+=		ac_cv_sys_file_offset_bits=yes
CONFIGURE_ARGS+=	--with-magick-plus-plus=no \
			--without-gslib \
			--without-dps \
			--without-perl \
			--without-djvu \
			--without-lcms \
			--without-lcms2 \
			--without-wmf \
			--without-xml \
			--without-lzma \
			--with-jpeg \
			--with-png \
			--with-tiff \
			--enable-fast-install

libimagemagick-install:
	$(INSTALL_DIR) $(IDIR_LIBIMAGEMAGICK)/usr/lib/${PKG_NAME}-${PKG_VERSION}
	$(CP) $(WRKINST)/usr/lib/${PKG_NAME}-${PKG_VERSION}/* \
		$(IDIR_LIBIMAGEMAGICK)/usr/lib/${PKG_NAME}-${PKG_VERSION}/
	$(CP) $(WRKINST)/usr/lib/libMagickCore*.so* \
		$(IDIR_LIBIMAGEMAGICK)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libMagickWand*.so* \
		$(IDIR_LIBIMAGEMAGICK)/usr/lib

convert-install:
	$(INSTALL_DIR) $(IDIR_CONVERT)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/convert $(IDIR_CONVERT)/usr/bin

display-install:
	$(INSTALL_DIR) $(IDIR_DISPLAY)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/display $(IDIR_DISPLAY)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
