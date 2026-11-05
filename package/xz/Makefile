# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		xz
PKG_VERSION:=		5.8.4
PKG_RELEASE:=		1
PKG_HASH:=		0014c7886930454fe8bd4228665b51af55eeae560ea135c9c4cd33f55b2591d9
PKG_DESCR:=		xz compression application
PKG_SECTION:=		app/archive
PKG_URL:=		https://tukaani.org/xz/
PKG_SITES:=		https://github.com/tukaani-project/xz/releases/download/v$(PKG_VERSION)/
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,XZ,xz,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

xz-install:
	$(INSTALL_DIR) $(IDIR_XZ)/usr/lib
	$(CP) $(WRKINST)/usr/lib/liblzma.so.* \
		$(IDIR_XZ)/usr/lib
	$(INSTALL_DIR) $(IDIR_XZ)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/xz \
		$(IDIR_XZ)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
