# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		vlc
PKG_VERSION:=		3.0.20
PKG_RELEASE:=		1
PKG_HASH:=		adc7285b4d2721cddf40eb5270cada2aaa10a334cb546fd55a06353447ba29b5
PKG_DESCR:=		popular media player
PKG_SECTION:=		mm/video
PKG_DEPENDS:=		libffmpeg xcb-util libgcrypt alsa-lib
PKG_BUILDDEP:=		ffmpeg xcb-util libgcrypt alsa-lib
PKG_NEEDS:=		threads
PKG_URL:=		http://www.videolan.org/vlc/
PKG_SITES:=		http://download.videolan.org/pub/videolan/vlc/$(PKG_VERSION)/

PKG_FLAVOURS_VLC:=	WITH_BLURAY WITH_MAD WITH_OGG WITH_OPUS WITH_SPEEX WITH_THEORA
PKG_FLAVOURS_VLC+=	WITH_VPX WITH_X264
PKGFD_WITH_BLURAY:=	enable bluray support
PKGFB_WITH_BLURAY:=	libbluray
PKGFS_WITH_BLURAY:=	libbluray
PKGFD_WITH_MAD:=	enable mp3 support
PKGFB_WITH_MAD:=	libmad
PKGFS_WITH_MAD:=	libmad
PKGFD_WITH_OGG:=	enable ogg support
PKGFB_WITH_OGG:=	libogg
PKGFS_WITH_OGG:=	libogg
PKGFD_WITH_OPUS:=	enable opus support
PKGFB_WITH_OPUS:=	opus
PKGFS_WITH_OPUS:=	libopus
PKGFD_WITH_SPEEX:=	enable speex support
PKGFB_WITH_SPEEX:=	speex
PKGFS_WITH_SPEEX:=	libspeex
PKGFD_WITH_THEORA:=	enable theora support
PKGFB_WITH_THEORA:=	libtheora
PKGFS_WITH_THEORA:=	libtheora
PKGFD_WITH_VPX:=	enable vpx support
PKGFB_WITH_VPX:=	libvpx
PKGFS_WITH_VPX:=	libvpx
PKGFD_WITH_X264:=	enable h264 support
PKGFB_WITH_X264:=	libx264
PKGFS_WITH_X264:=	libx264

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,VLC,vlc,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_CPPFLAGS+=	-D_DEFAULT_SOURCE
TARGET_CFLAGS+=		-fPIC

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ENV+=		ac_cv_func_sched_getaffinity=no
CONFIGURE_ARGS+=	--disable-lua \
			--disable-dbus \
			--disable-a52 \
			--disable-fribidi \
			--disable-skins2 \
			--disable-dvdnav \
			--disable-libxml2 \
			--disable-jack \
			--disable-xcb \
			--disable-taglib \
			--without-kde-solid \
			--enable-run-as-root \
			--enable-libgcrypt \
			--disable-optimizations \
			--disable-static \
			--disable-swscale \
			--disable-avformat \
			--disable-avcodec \
			--disable-mpg123

ifeq ($(ADK_TARGET_ARCH_ARM_WITH_NEON),)
CONFIGURE_ARGS+=	--disable-neon
endif

ifneq ($(ADK_PACKAGE_VLC_WITH_BLURAY),)
CONFIGURE_ARGS+=	--enable-bluray
else
CONFIGURE_ARGS+=	--disable-bluray
endif
ifneq ($(ADK_PACKAGE_VLC_WITH_MAD),)
CONFIGURE_ARGS+=	--enable-mad
else
CONFIGURE_ARGS+=	--disable-mad
endif
ifneq ($(ADK_PACKAGE_VLC_WITH_OGG),)
CONFIGURE_ARGS+=	--enable-ogg
else
CONFIGURE_ARGS+=	--disable-ogg
endif
ifneq ($(ADK_PACKAGE_VLC_WITH_OPUS),)
CONFIGURE_ARGS+=	--enable-opus
else
CONFIGURE_ARGS+=	--disable-opus
endif
ifneq ($(ADK_PACKAGE_VLC_WITH_SPEEX),)
CONFIGURE_ARGS+=	--enable-speex
else
CONFIGURE_ARGS+=	--disable-speex
endif
ifneq ($(ADK_PACKAGE_VLC_WITH_THEORA),)
CONFIGURE_ARGS+=	--enable-theora
else
CONFIGURE_ARGS+=	--disable-theora
endif
ifneq ($(ADK_PACKAGE_VLC_WITH_VPX),)
CONFIGURE_ARGS+=	--enable-vpx
else
CONFIGURE_ARGS+=	--disable-vpx
endif
ifneq ($(ADK_PACKAGE_VLC_WITH_X264),)
CONFIGURE_ARGS+=	--enable-x264
else
CONFIGURE_ARGS+=	--disable-x264
endif

vlc-install:
	$(INSTALL_DIR) $(IDIR_VLC)/usr/bin
	$(INSTALL_DIR) $(IDIR_VLC)/usr/lib/vlc/plugins
	$(CP) $(WRKINST)/usr/lib/libvlc*.so* \
		$(IDIR_VLC)/usr/lib
	$(INSTALL_BIN) $(WRKINST)/usr/bin/{c,}vlc \
		$(IDIR_VLC)/usr/bin
	$(CP) $(WRKINST)/usr/lib/vlc/plugins/* \
		$(IDIR_VLC)/usr/lib/vlc/plugins
	-rm $(IDIR_VLC)/usr/lib/vlc/plugins/*/*.la
	-rm $(IDIR_VLC)/usr/lib/vlc/plugins/*/*.a

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
