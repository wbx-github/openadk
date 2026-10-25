# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libarchive
PKG_VERSION:=		3.8.10
PKG_RELEASE:=		1
PKG_HASH:=		56cad765459d5ee25a3b761f90c47d99379d28297fbfb72d908880d6b875fb96
PKG_DESCR:=		multiformat archive and compression library
PKG_SECTION:=		libs/comp
PKG_URL:=		https://www.libarchive.org/
PKG_SITES:=		https://www.libarchive.org/downloads/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,LIBARCHIVE,libarchive,$(PKG_VERSION)-$(PKG_RELEASE)))
$(eval $(call PKG_template,LIBARCHIVE,libarchive,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

XAKE_FLAGS+=		V=1
CONFIGURE_ARGS+=	--disable-xattr \
			--disable-acl \
			--without-xml2 \
			--without-lzma \
			--without-lzmadec \
			--without-lz4 \
			--without-lzo2 \
			--without-nettle \
			--without-openssl \
			--without-expat \
			--without-bz2lib \
			--without-zlib

libarchive-install:
	$(INSTALL_DIR) $(IDIR_LIBARCHIVE)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libarchive*.so* \
		$(IDIR_LIBARCHIVE)/usr/lib

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
