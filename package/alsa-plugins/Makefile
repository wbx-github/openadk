# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		alsa-plugins
PKG_VERSION:=		1.2.12
PKG_RELEASE:=		1
PKG_HASH:=		7bd8a83d304e8e2d86a25895d8dcb0ef0245a8df32e271959cdbdc6af39b66f2
PKG_DESCR:=		sound library plugins
PKG_SECTION:=		libs/audio
PKG_BUILDDEP:=		libsamplerate alsa-lib
PKG_DEPENDS:=		libsamplerate alsa-lib
PKG_URL:=		http://www.alsa-project.org/
PKG_SITES:=		ftp://ftp.alsa-project.org/pub/plugins/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.bz2

PKG_FLAVOURS_ALSA_PLUGINS:=	WITH_JACK2
PKGFD_WITH_JACK2:=	enable jack2 support
PKGFS_WITH_JACK2:=	jack2
PKGFB_WITH_JACK2:=	jack2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,ALSA_PLUGINS,alsa-plugins,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

ifneq (${ADK_PACKAGE_ALSA_PLUGINS_WITH_JACK2},)
CONFIGURE_ARGS+=	--enable-jack
else
CONFIGURE_ARGS+=	--disable-jack
endif

alsa-plugins-install:
	$(INSTALL_DIR) $(IDIR_ALSA_PLUGINS)/usr/lib/alsa-lib
	$(CP) $(WRKINST)/usr/lib/alsa-lib/*.so \
		$(IDIR_ALSA_PLUGINS)/usr/lib/alsa-lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
