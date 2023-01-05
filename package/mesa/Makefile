# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		mesa
PKG_VERSION:=		22.3.2
PKG_RELEASE:=		1
PKG_HASH:=		c15df758a8795f53e57f2a228eb4593c22b16dffd9b38f83901f76cd9533140b
PKG_DESCR:=		3d graphics library
PKG_SECTION:=		libs/video
PKG_DEPENDS:=		libxdamage libxfixes libdrm libxxf86vm libexpat
PKG_DEPENDS+=		libxml2
PKG_BUILDDEP:=		python3 libxml2 libXdamage libXfixes libXrandr
PKG_BUILDDEP+=		libXxf86vm libdrm dri2proto glproto expat libXext
PKG_BUILDDEP+=		eudev dri3proto presentproto xcb-proto libxcb
PKG_BUILDDEP+=		libxshmfence python-mako-host
PKG_NEEDS:=		c++
PKG_URL:=		http://www.mesa3d.org/
PKG_SITES:=		ftp://ftp.freedesktop.org/pub/mesa/
PKG_LIBNAME:=		mesa
PKG_OPTS:=		dev

PKG_ARCH_DEPENDS:=	x86 x86_64 mips mipsel mips64 mips64el arm aarch64

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,MESA,mesa,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj
CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

MESON_FLAGS+=		-Dllvm=disabled \
			-Dgallium-drivers=swrast,panfrost,vc4,v3d \
			-Dvulkan-drivers= \
			-Dgbm=enabled \
			-Dplatforms=x11

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
