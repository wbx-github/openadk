# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		e2tools
PKG_VERSION:=		0.1.2
PKG_RELEASE:=		1
PKG_HASH:=		b19593bbfc85e9c14c0d2bc8525887901c8fe02588c76df60ab843bf0573c4a2
PKG_DESCR:=		read, write, and manipulate files in an ext2 filesystem
PKG_SECTION:=		sys/fs
PKG_DEPENDS:=		libe2fs libcom-err
PKG_BUILDDEP:=		e2fsprogs
PKG_SITES:=		https://github.com/e2tools/e2tools/releases/download/v$(PKG_VERSION)/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,E2TOOLS,e2tools,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

e2tools-install:
	$(INSTALL_DIR) $(IDIR_E2TOOLS)/usr/bin
	$(CP) $(WRKINST)/usr/bin/e2* \
		$(IDIR_E2TOOLS)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
