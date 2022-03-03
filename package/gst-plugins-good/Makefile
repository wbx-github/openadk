# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		gst-plugins-good
PKG_VERSION:=		1.19.3
PKG_RELEASE:=		1
PKG_HASH:=		79ea32a77fa47e6596530e38113bf97c113fd95658087d9a91ffb8af47d11d07
PKG_DESCR:=		gstreamer good plugins
PKG_SECTION:=		libs/video
PKG_DEPENDS:=		gstreamer
PKG_BUILDDEP:=		gstreamer libvorbis libtheora alsa-lib
PKG_URL:=		http://gstreamer.freedesktop.org/
PKG_SITES:=		http://gstreamer.freedesktop.org/src/gst-plugins-good/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,GST_PLUGINS_GOOD,gst-plugins-good,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

TARGET_CPPFLAGS+=	-D_GNU_SOURCE -D_POSIX_SOURCE

gst-plugins-good-install:
	$(INSTALL_DIR) $(IDIR_GST_PLUGINS_GOOD)/usr/lib/gstreamer-1.0/
	$(CP) $(WRKINST)/usr/lib/gstreamer-1.0/*.so \
		$(IDIR_GST_PLUGINS_GOOD)/usr/lib/gstreamer-1.0/

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
