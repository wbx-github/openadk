# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

# always use tab spaces as separator, no spaces
PKG_NAME:=		smartmontools
PKG_VERSION:=		7.1
PKG_RELEASE:=		1
PKG_HASH:=		3f734d2c99deb1e4af62b25d944c6252de70ca64d766c4c7294545a2e659b846
PKG_DESCR:=		Tools to provide advanced warning of disk degradation
PKG_SECTION:=		sys/hw
PKG_URL:=		www.smartmontools.org
PKG_SITES:=		$(MASTER_SITE_SOURCEFORGE:=smartmontools/)

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
