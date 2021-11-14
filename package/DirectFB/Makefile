# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		DirectFB
PKG_VERSION:=		1.7.7
PKG_EXTRAVER:=		1.7-7
PKG_RELEASE:=		1
PKG_HASH:=		b785c638dc31b8fe3a7c81be1475c89b2255ab3d67b777c747d3fbc52f8027a3
PKG_DESCR:=		thin graphic library for framebuffer devices
PKG_SECTION:=		libs/image
PKG_DEPENDS:=		libpng libjpeg-turbo libfreetype
PKG_BUILDDEP:=		libpng libjpeg-turbo freetype
PKG_URL:=		http://www.directfb.org/
PKG_SITES:=		https://distfiles.openadk.org/
PKG_LIBNAME:=		directfb
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,DIRECTFB,directfb,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIGURE_ARGS+=	--with-inputdrivers=linuxinput,keyboard,ps2mouse \
			--with-gfxdrivers=none \
			--without-tools \
			--enable-fbdev \
			--disable-sdl \
			--disable-osx \
			--disable-x11 \
			--disable-gif \
			--enable-png \
			--disable-debug \
			--disable-trace \
			--enable-text \
			--enable-jpeg

# This is to overcome libtool fuckup - when building without,
# libtool calls (the correct) ld directly without parameters,
# which then chooses the wrong default emulation (which is
# probably the real problem here).
ifeq (${ADK_TARGET_SYSTEM_LEMOTE_YEELONG},y)
XAKE_FLAGS+=		LDFLAGS=$(ADK_TARGET_ABI_CFLAGS)
endif

directfb-install:
	${INSTALL_DIR} ${IDIR_DIRECTFB}/etc
	${INSTALL_DATA} ./files/directfbrc ${IDIR_DIRECTFB}/etc
	$(INSTALL_DIR) $(IDIR_DIRECTFB)/usr/lib/directfb-${PKG_EXTRAVER}/{inputdrivers,systems,wm}
	${CP} $(WRKINST)/usr/lib/lib{direct,fusion}*.so* \
		$(IDIR_DIRECTFB)/usr/lib
	${CP} ${WRKINST}/usr/lib/directfb-${PKG_EXTRAVER}/inputdrivers/*.so \
		${IDIR_DIRECTFB}/usr/lib/directfb-${PKG_EXTRAVER}/inputdrivers
	${CP} ${WRKINST}/usr/lib/directfb-${PKG_EXTRAVER}/systems/*.so \
		${IDIR_DIRECTFB}/usr/lib/directfb-${PKG_EXTRAVER}/systems
	${CP} ${WRKINST}/usr/lib/directfb-${PKG_EXTRAVER}/wm/*.so \
		${IDIR_DIRECTFB}/usr/lib/directfb-${PKG_EXTRAVER}/wm
	$(INSTALL_DIR) $(IDIR_DIRECTFB)/usr/lib/directfb-${PKG_EXTRAVER}/interfaces/IDirectFB{Font,ImageProvider,VideoProvider}
	${CP} ${WRKINST}/usr/lib/directfb-${PKG_EXTRAVER}/interfaces/IDirectFBFont/*.so \
		${IDIR_DIRECTFB}/usr/lib/directfb-${PKG_EXTRAVER}/interfaces/IDirectFBFont
	${CP} ${WRKINST}/usr/lib/directfb-${PKG_EXTRAVER}/interfaces/IDirectFBImageProvider/*.so \
		${IDIR_DIRECTFB}/usr/lib/directfb-${PKG_EXTRAVER}/interfaces/IDirectFBImageProvider
	${CP} ${WRKINST}/usr/lib/directfb-${PKG_EXTRAVER}/interfaces/IDirectFBVideoProvider/*.so \
		${IDIR_DIRECTFB}/usr/lib/directfb-${PKG_EXTRAVER}/interfaces/IDirectFBVideoProvider

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
