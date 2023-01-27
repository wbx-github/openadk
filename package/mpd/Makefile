# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		mpd
PKG_VERSION:=		0.23.12
PKG_RELEASE:=		1
PKG_HASH:=		b7fca62284ecc25a681ea6a07abc49200af5353be42cb5a31e3173be9d8702e7
PKG_DESCR:=		music player daemon
PKG_SECTION:=		mm/audio
PKG_DEPENDS:=		libmpdclient boost libncurses libexpat libsqlite libfmt libxcb
PKG_DEPENDS+=		libxau libxdmcp
PKG_BUILDDEP:=		libmpdclient boost ncurses expat sqlite fmt libxcb
PKG_BUILDDEP+=		libXau libXdmcp
PKG_FDEPENDS:=		libmpdclient
PKG_NEEDS:=		threads c++ data
PKG_URL:=		http://www.musicpd.org/
PKG_SITES:=		http://www.musicpd.org/download/mpd/0.23/

PKG_FLAVOURS_MPD:=	WITH_ALSA WITH_AO WITH_MP3 WITH_MP4
PKG_FLAVOURS_MPD+=	WITH_OGG WITH_FLAC WITH_WAV WITH_MMS WITH_FFMPEG
PKG_FLAVOURS_MPD+=	WITH_SHOUT WITH_CURL WITH_SAMPLERATE WITH_HTTPD
PKG_FLAVOURS_MPD+=	WITH_SNDFILE WITH_OPUS WITH_PULSE WITH_AVAHI WITH_JACK

PKGFD_WITH_ALSA:=	enable ALSA output
PKGFS_WITH_ALSA:=	alsa-lib
PKGFB_WITH_ALSA:=	alsa-lib
ifeq ($(ADK_PACKAGE_MPD_WITH_ALSA),y)
PKG_FDEPENDS+=		alsa-lib
endif
PKGFD_WITH_AO:=		enable Libao/ESD output
PKGFS_WITH_AO:=		libao
PKGFB_WITH_AO:=		libao
ifeq ($(ADK_PACKAGE_MPD_WITH_AO),y)
PKG_FDEPENDS+=		libao
endif
PKGFD_WITH_JACK:=	enable JACK support
PKGFS_WITH_JACK:=	jack
PKGFB_WITH_JACK:=	jack
ifeq ($(ADK_PACKAGE_MPD_WITH_JACK),y)
PKG_FDEPENDS+=		jack
endif
PKGFD_WITH_MP3:=	enable MP3 support
PKGFS_WITH_MP3:=	libid3tag libmad
PKGFB_WITH_MP3:=	libid3tag libmad
ifeq ($(ADK_PACKAGE_MPD_WITH_MP3),y)
PKG_FDEPENDS+=		libid3tag libmad
endif
PKGFD_WITH_MP4:=	enable MP4 support
PKGFS_WITH_MP4:=	libfaad2
PKGFB_WITH_MP4:=	faad2
ifeq ($(ADK_PACKAGE_MPD_WITH_MP4),y)
PKG_FDEPENDS+=		libfaad2
endif
PKGFD_WITH_OGG:=	enable OGG support
PKGFS_WITH_OGG:=	libvorbis libogg
PKGFB_WITH_OGG:=	libvorbis libogg
ifeq ($(ADK_PACKAGE_MPD_WITH_OGG),y)
PKG_FDEPENDS+=		libvorbis libogg
endif
PKGFD_WITH_FLAC:=	enable FLAC support
PKGFS_WITH_FLAC:=	libflac
PKGFB_WITH_FLAC:=	flac
ifeq ($(ADK_PACKAGE_MPD_WITH_FLAC),y)
PKG_FDEPENDS+=		libflac
endif
PKGFD_WITH_WAV:=	enable WAVE support
PKGFS_WITH_WAV:=	libaudiofile
PKGFB_WITH_WAV:=	libaudiofile
ifeq ($(ADK_PACKAGE_MPD_WITH_WAV),y)
PKG_FDEPENDS+=		libaudiofile
endif
PKGFD_WITH_MMS:=	enable MMS support
PKGFS_WITH_MMS:=	libmms
PKGFB_WITH_MMS:=	libmms
ifeq ($(ADK_PACKAGE_MPD_WITH_MMS),y)
PKG_FDEPENDS+=		libmms
endif
PKGFD_WITH_FFMPEG:=	enable FFMPEG support
PKGFS_WITH_FFMPEG:=	libffmpeg
PKGFB_WITH_FFMPEG:=	ffmpeg
ifeq ($(ADK_PACKAGE_MPD_WITH_FFMPEG),y)
PKG_FDEPENDS+=		libffmpeg
endif
PKGFD_WITH_SHOUT:=	enable Shoutcast output support
PKGFS_WITH_SHOUT:=	libshout libmp3lame libvorbisenc
PKGFB_WITH_SHOUT:=	lame libvorbis libshout
ifeq ($(ADK_PACKAGE_MPD_WITH_SHOUT),y)
PKG_FDEPENDS+=		libshout libmp3lame libvorbisenc
endif
PKGFD_WITH_CURL:=	enable CURL support
PKGFS_WITH_CURL:=	libcurl
PKGFB_WITH_CURL:=	curl
ifeq ($(ADK_PACKAGE_MPD_WITH_CURL),y)
PKG_FDEPENDS+=		curl
endif

PKGFD_WITH_SAMPLERATE:=	enable samplerate support
PKGFS_WITH_SAMPLERATE:=	libsamplerate
PKGFB_WITH_SAMPLERATE:=	libsamplerate
ifeq ($(ADK_PACKAGE_MPD_WITH_SAMPLERATE),y)
PKG_FDEPENDS+=		libsamplerate
endif

PKGFD_WITH_OPUS:=	enable OPUS support
PKGFS_WITH_OPUS:=	libopus
PKGFB_WITH_OPUS:=	opus
ifeq ($(ADK_PACKAGE_MPD_WITH_OPUS),y)
PKG_FDEPENDS+=		libopus
endif

PKGFD_WITH_SNDFILE:=	enable sndfile support
PKGFS_WITH_SNDFILE:=	libsndfile
PKGFB_WITH_SNDFILE:=	libsndfile
ifeq ($(ADK_PACKAGE_MPD_WITH_SNDFILE),y)
PKG_FDEPENDS+=		libsndfile
endif

PKGFD_WITH_PULSE:=	enable pulse support
PKGFS_WITH_PULSE:=	pulseaudio
PKGFB_WITH_PULSE:=	pulseaudio
ifeq ($(ADK_PACKAGE_MPD_WITH_PULSE),y)
PKG_FDEPENDS+=		pulseaudio
endif

PKGFD_WITH_AVAHI:=	enable avahi/zeroconf support
PKGFS_WITH_AVAHI:=	libavahi libdbus
PKGFB_WITH_AVAHI:=	avahi
ifeq ($(ADK_PACKAGE_MPD_WITH_AVAHI),y)
PKG_FDEPENDS+=		libavahi
endif

PKGFD_WITH_HTTPD:=	enable http output

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,MPD,mpd,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_FDEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

TARGET_CPPFLAGS+=	-D_GNU_SOURCE -D_POSIX_SOURCE
TARGET_CFLAGS+=		-std=gnu99

MESON_FLAGS+=	-Dfifo=false \
		-Doss=disabled

ifneq ($(ADK_PACKAGE_MPD_WITH_JACK),)
MESON_FLAGS+=	-Djack=enabled
else
MESON_FLAGS+=	-Djack=disabled
endif

ifneq ($(ADK_PACKAGE_MPD_WITH_SNDFILE),)
MESON_FLAGS+=	-Dsndfile=enabled
else
MESON_FLAGS+=	-Dsndfile=disabled
endif

ifneq ($(ADK_PACKAGE_MPD_WITH_HTTPD),)
MESON_FLAGS+=	-Dhttpd=true
else
MESON_FLAGS+=	-Dhttpd=false
endif

ifneq ($(ADK_PACKAGE_MPD_WITH_AVAHI),)
MESON_FLAGS+=	-Dzeroconf=avahi
else
MESON_FLAGS+=	-Dzeroconf=disabled
endif

ifneq ($(ADK_PACKAGE_MPD_WITH_PULSE),)
MESON_FLAGS+=	-Dpulse=enabled
else
MESON_FLAGS+=	-Dpulse=disabled
endif

ifneq ($(ADK_PACKAGE_MPD_WITH_ALSA),)
MESON_FLAGS+=	-Dalsa=enabled
else
MESON_FLAGS+=	-Dalsa=disabled
endif

ifneq ($(ADK_PACKAGE_MPD_WITH_AO),)
MESON_FLAGS+=	-Dao=enabled
else
MESON_FLAGS+=	-Dao=disabled
endif

ifneq ($(ADK_PACKAGE_MPD_WITH_MP3),)
MESON_FLAGS+=	-Dmad=enabled
else
MESON_FLAGS+=	-Dmad=disabled
endif

ifneq ($(ADK_PACKAGE_MPD_WITH_MP4),)
MESON_FLAGS+=	-Dfaad=enabled
else
MESON_FLAGS+=	-Dfaad=disabled
endif

ifneq ($(ADK_PACKAGE_MPD_WITH_OGG),)
MESON_FLAGS+=	-Dvorbis=enabled
else
MESON_FLAGS+=	-Dvorbis=disabled
endif

ifneq ($(ADK_PACKAGE_MPD_WITH_TREMOR),)
MESON_FLAGS+=	-Dtremor=enabled 
endif

ifneq ($(ADK_PACKAGE_MPD_WITH_FLAC),)
MESON_FLAGS+=	-Dflac=enabled
else
MESON_FLAGS+=	-Dflac=disabled
endif

ifneq ($(ADK_PACKAGE_MPD_WITH_WAV),)
MESON_FLAGS+=	-Daudiofile=enabled
else
MESON_FLAGS+=	-Daudiofile=disabled
endif

ifneq ($(ADK_PACKAGE_MPD_WITH_SHOUT),)
MESON_FLAGS+=	-Dshout=enabled
else
MESON_FLAGS+=	-Dshout=disabled
endif

ifneq ($(ADK_PACKAGE_MPD_WITH_CURL),)
MESON_FLAGS+=	-Dcurl=enabled
else
MESON_FLAGS+=	-Dcurl=disabled
endif

ifneq ($(ADK_PACKAGE_MPD_WITH_MMS),)
MESON_FLAGS+=	-Dmms=enabled
else
MESON_FLAGS+=	-Dmms=disabled
endif

ifneq ($(ADK_PACKAGE_MPD_WITH_FFMPEG),)
MESON_FLAGS+=	-Dffmpeg=enabled
else
MESON_FLAGS+=	-Dffmpeg=disabled
endif

ifneq ($(ADK_PACKAGE_MPD_WITH_SAMPLERATE),)
MESON_FLAGS+=	-Dlibsamplerate=enabled
else
MESON_FLAGS+=	-Dlibsamplerate=disabled
endif

ifneq ($(ADK_PACKAGE_MPD_WITH_OPUS),)
MESON_FLAGS+=	-Dopus=enabled
else
MESON_FLAGS+=	-Dopus=disabled
endif

mpd-install:
	$(INSTALL_DIR) $(IDIR_MPD)/etc
	$(INSTALL_DIR) $(IDIR_MPD)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/mpd \
		$(IDIR_MPD)/usr/bin
	$(INSTALL_DATA) ./files/mpd.conf \
		$(IDIR_MPD)/etc

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
