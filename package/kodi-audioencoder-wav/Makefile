# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		kodi-audioencoder-wav
PKG_VERSION:=		v1.1.0
PKG_GIT:=		tag
PKG_RELEASE:=		1
PKG_DESCR:=		kodi wav audioencoder
PKG_SECTION:=		mm/video
PKG_DEPENDS:=		kodi
PKG_BUILDDEP:=		kodi
PKG_SITES:=		https://github.com/xbmc/audioencoder.wav.git

PKG_CFLINE_KODI_AUDIOENCODER_WAV:=	depends on ADK_BROKEN

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,KODI_AUDIOENCODER_WAV,kodi-audioencoder-wav,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		cmake

kodi-audioencoder-wav-install:
	$(INSTALL_DIR) $(IDIR_KODI_AUDIOENCODER_WAV)/usr/lib/kodi/addons
	$(CP) $(WRKINST)/usr/lib/kodi/addons/* \
		$(IDIR_KODI_AUDIOENCODER_WAV)/usr/lib/kodi/addons

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
