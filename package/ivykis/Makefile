# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		ivykis
PKG_VERSION:=		0.43.2
PKG_RELEASE:=		1
PKG_HASH:=		5a81cb5ff94e2b9c289682204aecc675bd726d6db822c592ed9f0e3e493d488e
PKG_DESCR:=		asynchronous i/o readiness notification
PKG_SECTION:=		libs/misc
PKG_URL:=		https://github.com/buytenh/ivykis
PKG_SITES:=		https://github.com/buytenh/ivykis/archive/refs/tags/

DISTFILES:=		v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,IVYKIS,ivykis,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

ivykis-install:
	$(INSTALL_DIR) $(IDIR_IVYKIS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libivykis.so* \
		$(IDIR_IVYKIS)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
