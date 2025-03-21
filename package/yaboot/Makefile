# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		yaboot
PKG_VERSION:=		1.3.17
PKG_RELEASE:=		1
PKG_HASH:=		2fb738d8fd48b94ab2534a4fdf63738ad02c1a30f4b2add91f837baff8fa2aa1
PKG_DESCR:=		ppc32 bootloader
PKG_SECTION:=		base/boot
PKG_BUILDDEP:=		e2fsprogs
PKG_URL:=		http://yaboot.ozlabs.org/
PKG_SITES:=		http://yaboot.ozlabs.org/releases/

PKG_ARCH_DEPENDS:=	ppc

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,YABOOT,yaboot,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		manual
INSTALL_STYLE:=		manual

yaboot-install:
	$(INSTALL_DIR) $(IDIR_YABOOT)/etc
	$(CP) $(WRKBUILD)/etc/yaboot.conf \
		$(IDIR_YABOOT)/etc
	$(INSTALL_DIR) $(IDIR_YABOOT)/sbin
	$(INSTALL_BIN) $(WRKBUILD)/second/yaboot \
		$(IDIR_YABOOT)/sbin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
