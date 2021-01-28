# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libmspack
PKG_VERSION:=		0.10.1alpha
PKG_RELEASE:=		1
PKG_HASH:=		bac862dee6e0fc10d92c70212441d9f8ad9b0222edc9a708c3ead4adb1b24a8e
PKG_DESCR:=		cab extractor
PKG_SECTION:=		libs/misc
PKG_SITES:=		https://www.cabextract.org.uk/libmspack/
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBMSPACK,libmspack,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

libmspack-install:
	$(INSTALL_DIR) $(IDIR_LIBMSPACK)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libmspack*.so* \
		$(IDIR_LIBMSPACK)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
