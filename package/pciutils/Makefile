# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		pciutils
PKG_VERSION:=		3.5.1
PKG_RELEASE:=		3
PKG_HASH:=		2bf3a4605a562fb6b8b7673bff85a474a5cf383ed7e4bd8886b4f0939013d42f
PKG_DESCR:=		pci utilities
PKG_SECTION:=		sys/hw
PKG_DEPENDS:=		zlib
PKG_BUILDDEP:=		zlib
PKG_URL:=		http://www.kernel.org/pub/software/utils/pciutils/
PKG_SITES:=		http://www.kernel.org/pub/software/utils/pciutils/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,PCIUTILS,pciutils,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=          manual

MAKE_FLAGS+=		CC="$(TARGET_CC)" \
			CFLAGS="$(TARGET_CFLAGS) -fPIC" \
			CROSS_COMPILE="$(TARGET_CROSS)" \
			IDSDIR="/usr/share" \
			HOST=$(GNU_TARGET_NAME)
ALL_TARGET:=

pciutils-install:
	$(INSTALL_DIR) $(IDIR_PCIUTILS)/usr/sbin
	$(INSTALL_DIR) $(IDIR_PCIUTILS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libpci*.so* $(IDIR_PCIUTILS)/usr/lib
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/lspci $(IDIR_PCIUTILS)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/setpci $(IDIR_PCIUTILS)/usr/sbin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
