# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libxml2
PKG_VERSION:=		2.10.3
PKG_RELEASE:=		1
PKG_HASH:=		5d2cc3d78bec3dbe212a9d7fa629ada25a7da928af432c93060ff5c17ee28a9c
PKG_DESCR:=		xml parser and toolkit
PKG_SECTION:=		libs/data
PKG_DEPENDS:=		zlib
PKG_BUILDDEP:=		libxml2-host python3 zlib
HOST_BUILDDEP:=		python3-host
PKG_URL:=		http://www.xmlsoft.org/
PKG_SITES:=		https://download.gnome.org/sources/libxml2/2.10/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,LIBXML2,libxml2,$(PKG_VERSION)-$(PKG_RELEASE)))
$(eval $(call PKG_template,LIBXML2,libxml2,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

HOST_STYLE:=		auto
HOST_CONFIGURE_ARGS+=	--without-python \
			--with-threads \
			--without-iconv \
			--without-lzma \
			--without-zlib

CONFIGURE_ARGS+=	--without-c14n \
			--without-debug \
			--with-catalog \
			--with-html \
			--without-ftp \
			--without-http \
			--without-iconv \
			--without-lzma \
			--without-iso8859x \
			--without-legacy \
			--with-output \
			--without-pattern \
			--without-push \
			--with-reader \
			--without-readline \
			--without-regexps \
			--with-sax1 \
			--with-schemas \
			--with-threads \
			--with-tree \
			--with-valid \
			--with-writer \
			--with-xinclude \
			--with-xpath \
			--with-xptr \
			--without-python \
			--with-zlib='$(STAGING_TARGET_DIR)/usr'

libxml2-install:
	$(INSTALL_DIR) $(IDIR_LIBXML2)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libxml2.so* $(IDIR_LIBXML2)/usr/lib

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
