# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		kodi
PKG_VERSION:=		19.5
PKG_RELEASE:=		1
PKG_HASH:=		56e0074f27f08496b2a21af5704a15378a2f0979ae3e9fa9a50a2630d0313d19
PKG_DESCR:=		software media player
PKG_SECTION:=		mm/video
PKG_DEPENDS:=		python3 libsquish libressl libxz libfmt rapidjson
PKG_DEPENDS+=		libass libmpeg2 libmad libmodplug libcurl
PKG_DEPENDS+=		libflac libbz2 libtiff libnettle librtmp liblzo
PKG_DEPENDS+=		yajl tinyxml libsqlite libpcrecpp libncurses libpng
PKG_DEPENDS+=		libpcre libcdio libfreetype libsamplerate libuuid
PKG_DEPENDS+=		taglib libjasper libmp3lame libgpg-error giflib
PKG_DEPENDS+=		glib libdcadec libffmpeg libxvidcore libiconv
PKG_DEPENDS+=		flatbuffers fstrcmp spdlog mesa libinput libxkbcommon
PKG_BUILDDEP:=		python3 libass ffmpeg rtmpdump libiconv
PKG_BUILDDEP+=		libmpeg2 libmad libjpeg-turbo fmt rapidjson
PKG_BUILDDEP+=		curl flac bzip2 libtiff yajl cmake-host
PKG_BUILDDEP+=		tinyxml sqlite pcre libcdio freetype libpng
PKG_BUILDDEP+=		libsamplerate taglib libjasper giflib
PKG_BUILDDEP+=		glib libmodplug libgpg-error xvidcore
PKG_BUILDDEP+=		swig-host liblzo-host libpng-host libjpeg-turbo-host
PKG_BUILDDEP+=		zip-host unzip-host giflib-host libsquish libdcadec
PKG_BUILDDEP+=		libcrossguid libressl xz bzip2 liblzo
PKG_BUILDDEP+=		flatbuffers fstrcmp spdlog mesa libinput libxkbcommon
PKG_NEEDS:=		threads c++ data iconv
PKG_URL:=		http://kodi.tv/
PKG_SITES:=		https://github.com/xbmc/xbmc/archive/

DISTFILES:=		$(PKG_VERSION)-Matrix.tar.gz
WRKDIST=		${WRKDIR}/xbmc-$(PKG_VERSION)-Matrix
WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

PKG_SYSTEM_DEPENDS:=	raspberry-pi raspberry-pi2 raspberry-pi3 raspberry-pi4 rockpi4-plus

PKG_FLAVOURS_KODI:=	WITH_ALSA WITH_CEC WITH_PULSEAUDIO WITH_SMB
PKG_FLAVOURS_KODI+=	WITH_MICROHTTPD WITH_SSH WITH_AVAHI
PKGFD_WITH_ALSA:=	enable alsa support
PKGFS_WITH_ALSA:=	alsa-lib
PKGFB_WITH_ALSA:=	alsa-lib
PKGFD_WITH_AVAHI:=	enable avahi support
PKGFS_WITH_AVAHI:=	libavahi
PKGFB_WITH_AVAHI:=	avahi
PKGFD_WITH_CEC:=	enable cec support
PKGFS_WITH_CEC:=	libcec
PKGFB_WITH_CEC:=	libcec
PKGFD_WITH_MICROHTTPD:=	enable microhttpd support
PKGFS_WITH_MICROHTTPD:=	libmicrohttpd
PKGFB_WITH_MICROHTTPD:=	libmicrohttpd
PKGFD_WITH_PULSEAUDIO:=	enable pulseaudio support
PKGFS_WITH_PULSEAUDIO:=	pulseaudio
PKGFB_WITH_PULSEAUDIO:=	pulseaudio
PKGFD_WITH_SMB:=	enable smb support
PKGFS_WITH_SMB:=	samba
PKGFB_WITH_SMB:=	samba
PKGFD_WITH_SSH:=	enable ssh support
PKGFS_WITH_SSH:=	libssh
PKGFB_WITH_SSH:=	libssh

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,KODI,kodi,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

HOST_CXXFLAGS:=		-DTARGET_POSIX -DTARGET_LINUX -D_LINUX -I$(WRKSRC)/xbmc/linux
CONFIG_STYLE:=		cmake
CMAKE_FLAGS+= 		-DENABLE_CCACHE=OFF \
			-DCMAKE_BUILD_TYPE=Release \
			-DVERBOSE=ON \
			-DENABLE_DVDCSS=ON \
			-DENABLE_INTERNAL_CROSSGUID=OFF \
			-DENABLE_INTERNAL_FFMPEG=OFF \
			-DWITH_FFMPEG=$(STAGING_TARGET_DIR)/usr \
			-DKODI_DEPENDSBUILD=OFF \
			-DENABLE_OPENSSL=ON \
			-DENABLE_MYSQLCLIENT=OFF \
			-DENABLE_NONFREE=ON \
			-DENABLE_CAP=OFF \
			-DENABLE_XSLT=OFF \
			-DENABLE_BLUETOOTH=OFF \
			-DENABLE_BLURAY=OFF \
			-DENABLE_AIRTUNES=OFF \
			-DENABLE_LCMS2=OFF \
			-DENABLE_LIRC=OFF \
			-DENABLE_UPNP=OFF \
			-DENABLE_OPTICAL=OFF \
			-DENABLE_DBUS=OFF \
			-DENABLE_EVENTCLIENTS=OFF \
			-DENABLE_UDEV=ON \
			-DENABLE_PLIST=OFF \
			-DNATIVEPREFIX=$(STAGING_HOST_DIR)/usr \
			-DDEPENDS_PATH=$(STAGING_HOST_DIR) \
			-DWITH_TEXTUREPACKER=$(STAGING_HOST_DIR)/usr/bin/TexturePacker \
			-DCMAKE_EXE_LINKER_FLAGS=-latomic \
			-DLIBDVDCSS_URL=$(DL_DIR)/libdvdcss-1.4.2-Leia-Beta-5.tar.gz \
			-DLIBDVDNAV_URL=$(DL_DIR)/libdvdnav-6.0.0-Leia-Alpha-3.tar.gz \
			-DLIBDVDREAD_URL=$(DL_DIR)/libdvdread-6.0.0-Leia-Alpha-3.tar.gz
			
ifeq ($(ADK_TARGET_ARCH_AARCH64),y)
CMAKE_FLAGS+=		-DCORE_PLATFORM_NAME=gbm \
			-DAPP_RENDER_SYSTEM=gles \
			-DWITH_ARCH=aarch64 \
			-DWITH_CPU=aarch64 \
			-DENABLE_NEON=ON \
			-DENABLE_OPENGL=OFF \
			-DENABLE_X11=OFF \
			-DENABLE_OPENGLES=ON
endif

ifeq ($(ADK_TARGET_BOARD_BCM28XX),y)
CMAKE_FLAGS+=		-DCORE_PLATFORM_NAME=gbm \
			-DAPP_RENDER_SYSTEM=gles \
			-DWITH_ARCH=arm \
			-DWITH_CPU=arm \
			-DENABLE_NEON=ON \
			-DENABLE_OPENGL=OFF \
			-DENABLE_X11=OFF \
			-DENABLE_OPENGLES=ON
endif

ifeq ($(ADK_PACKAGE_KODI_WITH_ALSA),y)
CMAKE_FLAGS+=		-DENABLE_ALSA=ON
else
CMAKE_FLAGS+=		-DENABLE_ALSA=OFF
endif
ifeq ($(ADK_PACKAGE_KODI_WITH_AVAHI),y)
CMAKE_FLAGS+=		-DENABLE_AVAHI=ON
else
CMAKE_FLAGS+=		-DENABLE_AVAHI=OFF
endif
ifeq ($(ADK_PACKAGE_KODI_WITH_CEC),y)
CMAKE_FLAGS+=		-DENABLE_CEC=ON
else
CMAKE_FLAGS+=		-DENABLE_CEC=OFF
endif
ifeq ($(ADK_PACKAGE_KODI_WITH_MICROHTTPD),y)
CMAKE_FLAGS+=		-DENABLE_MICROHTTPD=ON
else
CMAKE_FLAGS+=		-DENABLE_MICROHTTPD=OFF
endif
ifeq ($(ADK_PACKAGE_KODI_WITH_PULSEAUDIO),y)
CMAKE_FLAGS+=		-DENABLE_PULSEAUDIO=ON
else
CMAKE_FLAGS+=		-DENABLE_PULSEAUDIO=OFF
endif
ifeq ($(ADK_PACKAGE_KODI_WITH_SMB),y)
CMAKE_FLAGS+=		-DENABLE_SMBCLIENT=ON
else
CMAKE_FLAGS+=		-DENABLE_SMBCLIENT=OFF
endif
ifeq ($(ADK_PACKAGE_KODI_WITH_SSH),y)
CMAKE_FLAGS+=		-DENABLE_SSH=ON
else
CMAKE_FLAGS+=		-DENABLE_SSH=OFF
endif

XAKE_FLAGS+=		VERBOSE=1
TARGET_LDFLAGS+=	-latomic

pre-configure:
	(cd $(WRKSRC)/tools/depends/native/JsonSchemaBuilder && PATH='$(HOST_PATH)' cmake .)
	PATH='$(HOST_PATH)' make -C $(WRKSRC)/tools/depends/native/JsonSchemaBuilder
	cp $(WRKSRC)/tools/depends/native/JsonSchemaBuilder/JsonSchemaBuilder \
		$(STAGING_HOST_DIR)/usr/bin/JsonSchemaBuilder::JsonSchemaBuilder
	(cd $(WRKSRC)/tools/depends/native/TexturePacker && PATH='$(HOST_PATH)' cmake \
		-DCORE_SOURCE_DIR=$(WRKSRC) \
		-DCMAKE_MODULE_PATH=$(WRKSRC)/cmake/modules \
		-DCMAKE_CXX_FLAGS="$(HOST_CXXFLAGS)" .)
	PATH='$(HOST_PATH)' make -C $(WRKSRC)/tools/depends/native/TexturePacker
	cp $(WRKSRC)/tools/depends/native/TexturePacker/TexturePacker \
		$(STAGING_HOST_DIR)/usr/bin
	(cd $(DL_DIR) && wget -O libdvdcss-1.4.2-Leia-Beta-5.tar.gz https://github.com/xbmc/libdvdcss/archive/refs/tags/1.4.2-Leia-Beta-5.tar.gz)
	(cd $(DL_DIR) && wget -O libdvdnav-6.0.0-Leia-Alpha-3.tar.gz https://github.com/xbmc/libdvdnav/archive/refs/tags/6.0.0-Leia-Alpha-3.tar.gz)
	(cd $(DL_DIR) && wget -O libdvdread-6.0.0-Leia-Alpha-3.tar.gz https://github.com/xbmc/libdvdread/archive/refs/tags/6.0.0-Leia-Alpha-3.tar.gz)

kodi-install:
	$(INSTALL_DIR) $(STAGING_TARGET_DIR)/usr/share/kodi
	$(CP) $(WRKINST)/usr/share/kodi/* \
		$(STAGING_TARGET_DIR)/usr/share/kodi
	# we need a symlink to /data 
	cd $(IDIR_KODI)/ && ln -sf ../data/kodi .kodi
	$(INSTALL_DIR) $(IDIR_KODI)/usr/lib/kodi/addons
	$(CP) $(WRKINST)/usr/lib/kodi/* \
		$(IDIR_KODI)/usr/lib/kodi
	$(INSTALL_DIR) $(IDIR_KODI)/usr/share/kodi
	$(CP) $(WRKINST)/usr/share/kodi/* \
		$(IDIR_KODI)/usr/share/kodi
	$(INSTALL_DIR) $(IDIR_KODI)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/kodi-standalone \
		$(IDIR_KODI)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/kodi \
		$(IDIR_KODI)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
