# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libexif
PKG_VERSION:=		0.6.24
PKG_RELEASE:=		1
PKG_HASH:=		d47564c433b733d83b6704c70477e0a4067811d184ec565258ac563d8223f6ae
PKG_DESCR:=		Library for parsing, editing, and saving EXIF data
PKG_SECTION:=		libs/image
PKG_URL:=		https://libexif.github.io/
PKG_SITES:=		https://github.com/libexif/libexif/releases/download/v${PKG_VERSION}/
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBEXIF,libexif,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

libexif-install:
	$(INSTALL_DIR) $(IDIR_LIBEXIF)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libexif*.so* \
		$(IDIR_LIBEXIF)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
