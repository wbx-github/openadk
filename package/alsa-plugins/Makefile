# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		alsa-plugins
PKG_VERSION:=		1.0.28
PKG_RELEASE:=		2
PKG_HASH:=		426f8af1a07ee9d8c06449524d1f0bd59a06e0331a51aa3d59d343a7c6d03120
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
