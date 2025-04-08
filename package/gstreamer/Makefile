# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		gstreamer
PKG_VERSION:=		1.26.0
PKG_RELEASE:=		1
PKG_HASH:=		1b2ee4028010c25b776effa7c396c7e3e1861b60b9417e416f4914abcdff279f
PKG_DESCR:=		opensource multimedia framework
PKG_SECTION:=		libs/video
PKG_BUILDDEP:=		glib
PKG_DEPENDS:=		glib
PKG_URL:=		http://gstreamer.freedesktop.org/
PKG_SITES:=		http://gstreamer.freedesktop.org/src/gstreamer/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,GSTREAMER,gstreamer,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

MESON_FLAGS+=		-Dcheck=disabled \
			-Ddoc=disabled \
			-Dexamples=disabled

gstreamer-install:
	$(INSTALL_DIR) $(IDIR_GSTREAMER)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libgst*.so* \
		$(IDIR_GSTREAMER)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
