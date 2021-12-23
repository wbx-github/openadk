# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		mesa
PKG_VERSION:=		18.3.6
PKG_RELEASE:=		2
PKG_HASH:=		aaf17638dcf5a90b93b6389e152fdc9ef147768b09598f24d2c5cf482fcfc705
PKG_DESCR:=		3d graphics library
PKG_SECTION:=		libs/video
PKG_DEPENDS:=		libxdamage libxfixes libdrm libxxf86vm libexpat
PKG_DEPENDS+=		libxml2 libxml2-python
PKG_BUILDDEP:=		python2 libxml2 libXdamage libXfixes libXrandr
PKG_BUILDDEP+=		libXxf86vm libdrm dri2proto glproto expat libXext
PKG_BUILDDEP+=		eudev dri3proto presentproto xcb-proto libxcb
PKG_BUILDDEP+=		libxshmfence
PKG_NEEDS:=		c++
PKG_URL:=		http://www.mesa3d.org/
PKG_SITES:=		ftp://ftp.freedesktop.org/pub/mesa/
PKG_LIBNAME:=		mesa
PKG_OPTS:=		dev

PKG_ARCH_DEPENDS:=	x86 x86_64 mips mipsel mips64 mips64el arm

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,MESA,mesa,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

DRI_DRIVERS:=		swrast

CONFIGURE_ARGS+=	--disable-static \
			--disable-gallium-llvm \
			--without-gallium-drivers \
			--enable-dri \
			--enable-dri3 \
			--enable-glx=dri \
			--with-dri-driverdir=/usr/lib/dri \
			--with-dri-drivers=${DRI_DRIVERS}
CONFIGURE_ENV+=		MISSING="echo"
XAKE_FLAGS+=		HOST_CC=${CC_FOR_BUILD}

mesa-install:
	$(INSTALL_DIR) $(IDIR_MESA)/usr/lib/dri
	$(CP) $(WRKINST)/usr/lib/libEGL*.so* \
		$(IDIR_MESA)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libGL*.so* \
		$(IDIR_MESA)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libglapi.so* \
		$(IDIR_MESA)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libgbm.so* \
		$(IDIR_MESA)/usr/lib
	${CP} $(WRKINST)/usr/lib/dri/*.so \
		${IDIR_MESA}/usr/lib/dri/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
