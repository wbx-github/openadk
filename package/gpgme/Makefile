# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		gpgme
PKG_VERSION:=		1.23.2
PKG_RELEASE:=		1
PKG_HASH:=		9499e8b1f33cccb6815527a1bc16049d35a6198a6c5fae0185f2bd561bce5224
PKG_DESCR:=		easy access to gnupg for applications
PKG_SECTION:=		libs/crypto
PKG_DEPENDS:=		libgpg-error libassuan
PKG_BUILDDEP:=		libgpg-error libassuan
PKG_NEEDS:=		c++
PKG_URL:=		https://gnupg.org/related_software/gpgme/index.html
PKG_SITES:=		https://gnupg.org/ftp/gcrypt/gpgme/
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,GPGME,gpgme,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

TARGET_CPPFLAGS+=	-D_FILE_OFFSET_BITS=64 -DLARGEFILE_SOURCE=1

gpgme-install:
	$(INSTALL_DIR) $(IDIR_GPGME)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libgpgme*.so* \
		$(IDIR_GPGME)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
