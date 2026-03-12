# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libarchive
PKG_VERSION:=		3.8.6
PKG_RELEASE:=		1
PKG_HASH:=		213269b05aac957c98f6e944774bb438d0bd168a2ec60b9e4f8d92035925821c
PKG_DESCR:=		multiformat archive and compression library
PKG_SECTION:=		libs/comp
PKG_URL:=		http://www.libarchive.org/
PKG_SITES:=		http://www.libarchive.org/downloads/
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

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
