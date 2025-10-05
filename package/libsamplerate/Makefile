# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libsamplerate
PKG_VERSION:=		0.2.2
PKG_RELEASE:=		1
PKG_HASH:=		3258da280511d24b49d6b08615bbe824d0cacc9842b0e4caf11c52cf2b043893
PKG_DESCR:=		sample rate converter for audio
PKG_SECTION:=		libs/audio
PKG_SITES:=		https://github.com/libsndfile/libsamplerate/releases/download/$(PKG_VERSION)/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBSAMPLERATE,libsamplerate,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIGURE_ARGS+=	--disable-sndfile

libsamplerate-install:
	$(INSTALL_DIR) $(IDIR_LIBSAMPLERATE)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libsamplerate*.so* \
		$(IDIR_LIBSAMPLERATE)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
