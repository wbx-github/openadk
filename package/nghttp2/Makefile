# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		nghttp2
PKG_VERSION:=		1.65.0
PKG_RELEASE:=		1
PKG_HASH:=		f1b9df5f02e9942b31247e3d415483553bc4ac501c87aa39340b6d19c92a9331
PKG_DESCR:=		http2 library
PKG_SECTION:=		libs/misc
PKG_SITES:=		https://github.com/nghttp2/nghttp2/releases/download/v1.65.0/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,NGHTTP2,nghttp2,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

nghttp2-install:
	$(INSTALL_DIR) $(IDIR_NGHTTP2)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libnghttp2*.so* \
		$(IDIR_NGHTTP2)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
