# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libwebp
PKG_VERSION:=		1.6.0
PKG_RELEASE:=		1
PKG_HASH:=		93a852c2b3efafee3723efd4636de855b46f9fe1efddd607e1f42f60fc8f2136
PKG_DESCR:=		new image format for the web
PKG_SECTION:=		libs/image
PKG_BUILDDEP:=		cmake-host
PKG_URL:=		https://developers.google.com/speed/webp/
PKG_SITES:=		https://github.com/webmproject/libwebp/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=		v${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

CONFIG_STYLE:=		cmake
CMAKE_FLAGS+=		-DBUILD_SHARED_LIBS=ON

$(eval $(call PKG_template,LIBWEBP,libwebp,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

libwebp-install:
	$(INSTALL_DIR) $(IDIR_LIBWEBP)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libwebp*so* \
		$(IDIR_LIBWEBP)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
