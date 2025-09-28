# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		wpewebkit
PKG_VERSION:=		2.50.0
PKG_RELEASE:=		1
PKG_HASH:=		a9af62c5e18551b7386b7db864e8ba8156f219b8e6c639934bf6f3a567969922
PKG_DESCR:=		web platform for embedded
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		libwpe libsoup3 harfbuzz libjpeg-turbo libgcrypt
PKG_DEPENDS+=		libtasn1 libwebp gstreamer gst-plugins-base libxslt
PKG_DEPENDS+=		libpsl libmount libblkid libepoxy
PKG_BUILDDEP:=		cmake-host libwpe libsoup3 harfbuzz libjpeg-turbo
PKG_BUILDDEP+=		libgcrypt libtasn1 libwebp gstreamer gst-plugins-base
PKG_BUILDDEP+=		libxslt libpsl libepoxy unifdef-host libatomic
PKG_URL:=		https://wpewebkit.org
PKG_SITES:=		https://wpewebkit.org/releases/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,WPEWEBKIT,wpewebkit,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

XAKE_FLAGS+=		VERBOSE=1
CONFIG_STYLE:=		cmake
CMAKE_FLAGS+=		-DPORT=WPE \
			-DUSE_SYSTEM_SYSPROF_CAPTURE=NO \
			-DENABLE_API_TESTS=OFF \
			-DENABLE_DOCUMENTATION=OFF \
			-DENABLE_INTROSPECTION=OFF \
			-DENABLE_MINIBROWSER=OFF \
			-DENABLE_WEB_RTC=OFF \
			-DENABLE_SPEECH_SYNTHESIS=OFF \
			-DENABLE_JOURNALD_LOG=OFF \
			-DENABLE_BUBBLEWRAP_SANDBOX=OFF \
			-DUSE_GSTREAMER_TRANSCODER=OFF \
			-DUSE_LIBBACKTRACE=OFF \
			-DUSE_JPEGXL=OFF \
			-DUSE_LCMS=OFF \
			-DUSE_WOFF2=OFF \
			-DUSE_AVIF=OFF \
			-DUSE_ATK=OFF \
			-DUSE_SKIA=OFF

wpewebkit-install:
	$(INSTALL_DIR) $(IDIR_WPEWEBKIT)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libWPEWebKit*.so* \
		$(IDIR_WPEWEBKIT)/usr/lib
	$(INSTALL_DIR) $(IDIR_WPEWEBKIT)/usr/libexec/wpe-webkit-2.0
	$(INSTALL_BIN) $(WRKINST)/usr/libexec/wpe-webkit-2.0/* \
		$(IDIR_WPEWEBKIT)/usr/libexec/wpe-webkit-2.0

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
