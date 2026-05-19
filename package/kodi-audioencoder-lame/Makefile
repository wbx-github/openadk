# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		kodi-audioencoder-lame
PKG_VERSION:=		v1.2.0
PKG_GIT:=		tag
PKG_RELEASE:=		1
PKG_DESCR:=		kodi lame audioencoder
PKG_SECTION:=		mm/video
PKG_DEPENDS:=		kodi lame
PKG_BUILDDEP:=		kodi lame
PKG_SITES:=		https://github.com/xbmc/audioencoder.lame.git

PKG_CFLINE_KODI_AUDIOENCODER_LAME:=	depends on ADK_BROKEN

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,KODI_AUDIOENCODER_LAME,kodi-audioencoder-lame,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		cmake

kodi-audioencoder-lame-install:
	$(INSTALL_DIR) $(IDIR_KODI_AUDIOENCODER_LAME)/usr/lib/kodi/addons
	$(CP) $(WRKINST)/usr/lib/kodi/addons/* \
		$(IDIR_KODI_AUDIOENCODER_LAME)/usr/lib/kodi/addons

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
