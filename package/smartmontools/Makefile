# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		smartmontools
PKG_VERSION:=		7.5
PKG_RELEASE:=		1
PKG_HASH:=		690b83ca331378da9ea0d9d61008c4b22dde391387b9bbad7f29387f2595f76e
PKG_DESCR:=		tools to provide advanced warning of disk degradation
PKG_SECTION:=		sys/hw
PKG_URL:=		www.smartmontools.org
PKG_SITES:=		https://github.com/smartmontools/smartmontools/releases/download/RELEASE_7_5/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,SMARTMONTOOLS,smartmontools,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

smartmontools-install:
	$(INSTALL_DIR) $(IDIR_SMARTMONTOOLS)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/smartctl \
		$(IDIR_SMARTMONTOOLS)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/smartd \
		$(IDIR_SMARTMONTOOLS)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/update-smart-drivedb \
		$(IDIR_SMARTMONTOOLS)/usr/sbin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
