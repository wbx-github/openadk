# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		mesa
PKG_VERSION:=		25.0.2
PKG_RELEASE:=		1
PKG_HASH:=		adf904d083b308df95898600ffed435f4b5c600d95fb6ec6d4c45638627fdc97
PKG_DESCR:=		3d graphics library
PKG_SECTION:=		libs/video
PKG_DEPENDS:=		libxdamage libxfixes libdrm libxxf86vm libexpat
PKG_DEPENDS+=		libxml2
PKG_BUILDDEP:=		python3 libxml2 libXdamage libXfixes libXrandr
PKG_BUILDDEP+=		libXxf86vm libdrm dri2proto glproto expat libXext
PKG_BUILDDEP+=		eudev dri3proto presentproto xcb-proto libxcb
PKG_BUILDDEP+=		libxshmfence python-mako-host python3-yaml-host
PKG_NEEDS:=		c++
PKG_URL:=		http://www.mesa3d.org/
PKG_SITES:=		https://archive.mesa3d.org/
PKG_LIBNAME:=		mesa
PKG_OPTS:=		dev

PKG_CHOICES_MESA:=	WITH_X11 WITH_WAYLAND
PKGCD_WITH_X11:=	with X11 support
PKGCD_WITH_WAYLAND:=	with wayland support
PKGCB_WITH_WAYLAND:=	wayland wayland-protocols

PKG_ARCH_DEPENDS:=	x86 x86_64 mips mipsel mips64 mips64el arm aarch64

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,MESA,mesa,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj
CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

MESON_FLAGS+=		-Dllvm=disabled \
			-Dgallium-drivers=panfrost,vc4,v3d,virgl \
			-Dvulkan-drivers= \
			-Dgbm=enabled \
			-Dglx=dri

ifeq ($(ADK_PACKAGE_MESA_WITH_WAYLAND),y)
MESON_FLAGS+=		-Dplatforms="wayland"
endif

ifeq ($(ADK_PACKAGE_MESA_WITH_X11),y)
MESON_FLAGS+=		-Dplatforms="x11"
endif

mesa-install:
	$(INSTALL_DIR) $(IDIR_MESA)/usr/lib/dri
	$(INSTALL_DIR) $(IDIR_MESA)/usr/lib/gbm
	$(CP) $(WRKINST)/usr/lib/libEGL*.so* \
		$(IDIR_MESA)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libGL*.so* \
		$(IDIR_MESA)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libgbm.so* \
		$(IDIR_MESA)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libgallium*.so* \
		$(IDIR_MESA)/usr/lib
	${CP} $(WRKINST)/usr/lib/dri/*.so \
		${IDIR_MESA}/usr/lib/dri/
	${CP} $(WRKINST)/usr/lib/gbm/*.so \
		${IDIR_MESA}/usr/lib/gbm/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
