# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		sox
PKG_VERSION:=		f3094754a7c2a7e55c35621d20fa9945736e72df
PKG_GIT:=		hash
PKG_RELEASE:=		1
PKG_HASH:=		b45f598643ffbd8e363ff24d61166ccec4836fea6d3888881b8df53e3bb55f6c
PKG_DESCR:=		swiss army knife of sound processing programs
PKG_SECTION:=		mm/audio
PKG_DEPENDS:=		zlib libncurses
PKG_BUILDDEP:=		zlib ncurses
PKG_NEEDS:=		threads
PKG_URL:=		http://sox.sourceforge.net/
PKG_SITES:=		https://git.code.sf.net/p/sox/code.git

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_FLAVOURS_SOX:=	WITH_LAME WITH_VORBIS WITH_FLAC WITH_MAD WITH_ALSA WITH_ID3TAG
PKGFD_WITH_LAME:=	mp3 lame support
PKGFB_WITH_LAME:=	lame
PKGFS_WITH_LAME:=	libmp3lame
PKGFD_WITH_MAD:=	mp3 mad support
PKGFB_WITH_MAD:=	libmad
PKGFS_WITH_MAD:=	libmad
PKGFD_WITH_VORBIS:=	ogg vorbis support
PKGFB_WITH_VORBIS:=	libvorbis libogg
PKGFS_WITH_VORBIS:=	libvorbis libogg libvorbisenc
PKGFD_WITH_FLAC:=	flac support
PKGFB_WITH_FLAC:=	flac
PKGFS_WITH_FLAC:=	libflac
PKGFD_WITH_ID3TAG:=	id3tag support
PKGFB_WITH_ID3TAG:=	libid3tag
PKGFS_WITH_ID3TAG:=	libid3tag
PKGFD_WITH_ALSA:=	alsa support
PKGFB_WITH_ALSA:=	alsa-lib
PKGFS_WITH_ALSA:=	alsa-lib

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,SOX,sox,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ARGS+=	--disable-openmp \
			--without-magic \
			--without-ladspa \
			--without-png \
			--without-amrwb \
			--without-amrnb \
			--without-pulseaudio \
			--without-wavpack \
			--without-twolame

ifeq ($(ADK_PACKAGE_SOX_WITH_ALSA),y)
CONFIGURE_ARGS+=	--with-alsa
else
CONFIGURE_ARGS+=	--without-alsa
endif
ifeq ($(ADK_PACKAGE_SOX_WITH_ID3TAG),y)
CONFIGURE_ARGS+=	--with-id3tag
else
CONFIGURE_ARGS+=	--without-id3tag
endif
ifeq ($(ADK_PACKAGE_SOX_WITH_FLAC),y)
CONFIGURE_ARGS+=	--with-flac
else
CONFIGURE_ARGS+=	--without-flac
endif
ifeq ($(ADK_PACKAGE_SOX_WITH_LAME),y)
CONFIGURE_ARGS+=	--with-lame
else
CONFIGURE_ARGS+=	--without-lame
endif
ifeq ($(ADK_PACKAGE_SOX_WITH_MAD),y)
CONFIGURE_ARGS+=	--with-mad
else
CONFIGURE_ARGS+=	--without-mad
endif
ifeq ($(ADK_PACKAGE_SOX_WITH_VORBIS),y)
CONFIGURE_ARGS+=	--with-oggvorbis
else
CONFIGURE_ARGS+=	--without-oggvorbis
endif
ifeq ($(ADK_TARGET_USE_SSP),y)
CONFIGURE_ARGS+=	--enable-stack-protector
else
CONFIGURE_ARGS+=	--disable-stack-protector
endif

sox-install:
	$(INSTALL_DIR) $(IDIR_SOX)/usr/lib
	${CP} ${WRKINST}/usr/lib/libsox.so* $(IDIR_SOX)/usr/lib
	$(INSTALL_DIR) $(IDIR_SOX)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/sox $(IDIR_SOX)/usr/bin
	cd ${IDIR_SOX}/usr/bin; for tgt in rec play; do \
		ln sox $$tgt; \
	done

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
