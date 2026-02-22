# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		pamtester
PKG_VERSION:=		0.1.2
PKG_RELEASE:=		1
PKG_HASH:=		83633d0e8a4f35810456d9d52261c8ae0beb9148276847cae8963505240fb2d5
PKG_DESCR:=		pam testing tool
PKG_SECTION:=		sys/misc
PKG_DEPENDS:=		pam
PKG_BUILDDEP:=		pam
PKG_SITES:=		http://prdownloads.sourceforge.net/pamtester/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,PAMTESTER,pamtester,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

pamtester-install:
	$(INSTALL_DIR) $(IDIR_PAMTESTER)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/pamtester \
		$(IDIR_PAMTESTER)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
