# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		webkitgtk
PKG_VERSION:=		2.34.6
PKG_RELEASE:=		1
PKG_HASH:=		6bc8fd034aad0432a2459ce4fc7ee25ad65a4924c618bf8d93b52b0c1a84c1f6
PKG_DESCR:=		web browser engine
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		glib icu4c zlib libwebp libgtk3 libsoup
PKG_DEPENDS+=		libsecret libxt harfbuzz cairo libgcrypt
PKG_DEPENDS+=		gstreamer libnotify libwebp gst-plugins-base
PKG_BUILDDEP:=		glib icu4c zlib libwebp libgtk3 cmake-host
PKG_BUILDDEP+=		libsoup libsecret libXt harfbuzz libnotify
PKG_BUILDDEP+=		gstreamer cairo enchant libwebp gst-plugins-base
PKG_BUILDDEP+=		gnutls libgcrypt ruby-host
PKG_URL:=		http://www.webkitgtk.org/
PKG_SITES:=		http://webkitgtk.org/releases/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,WEBKITGTK,webkitgtk,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj
XAKE_FLAGS+=		VERBOSE=1
TARGET_CXXFLAGS+=	-D__STDC_LIMIT_MACROS -D__STDC_FORMAT_MACROS

CONFIG_STYLE:=		cmake
CMAKE_FLAGS+= 		-DPORT=GTK \
			-DENABLE_GLES2=OFF \
			-DENABLE_OPENGL=ON \
			-DENABLE_X11_TARGET=ON \
			-DENABLE_API_TESTS=OFF \
			-DENABLE_GTKDOC=OFF \
			-DENABLE_GEOLOCATION=OFF \
			-DENABLE_MINIBROWSER=ON \
			-DUSE_SYSTEM_MALLOC=ON \
			-DUSE_LIBNOTIFY=OFF \
			-DENABLE_JIT=OFF \
			-DUSE_LIBHYPHEN=OFF \
			-DUSE_SOUP2=ON \
			-DUSE_WPE_RENDERER=OFF \
			-DENABLE_GAMEPAD=OFF \
			-DUSE_OPENJPEG=OFF \
			-DUSE_WOFF2=OFF \
			-DUSE_SYSTEMD=OFF \
			-DUSE_LCMS=OFF \
			-DENABLE_BUBBLEWRAP_SANDBOX=OFF \
			-DENABLE_INTROSPECTION=OFF

webkitgtk-install:
	$(INSTALL_DIR) $(IDIR_WEBKITGTK)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libjavascriptcoregtk*.so* \
		$(IDIR_WEBKITGTK)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libwebkit2gtk*.so* \
		$(IDIR_WEBKITGTK)/usr/lib
	$(CP) $(WRKINST)/usr/lib/webkit2gtk-4.0 \
		$(IDIR_WEBKITGTK)/usr/lib
	$(INSTALL_DIR) $(IDIR_WEBKITGTK)/usr/libexec
	$(CP) $(WRKINST)/usr/libexec/* \
		$(IDIR_WEBKITGTK)/usr/libexec

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
