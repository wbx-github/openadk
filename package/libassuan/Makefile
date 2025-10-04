# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libassuan
PKG_VERSION:=		3.0.2
PKG_RELEASE:=		1
PKG_HASH:=		d2931cdad266e633510f9970e1a2f346055e351bb19f9b78912475b8074c36f6
PKG_DESCR:=		implementation of assuan protocol
PKG_SECTION:=		libs/crypto
PKG_DEPENDS:=		libgpg-error
PKG_BUILDDEP:=		libgpg-error
PKG_URL:=		https://gnupg.org/related_software/libassuan/index.html
PKG_SITES:=		https://gnupg.org/ftp/gcrypt/libassuan/
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBASSUAN,libassuan,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

libassuan-install:
	$(INSTALL_DIR) $(IDIR_LIBASSUAN)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libassuan*.so* \
		$(IDIR_LIBASSUAN)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
