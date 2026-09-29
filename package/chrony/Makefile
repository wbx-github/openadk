# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		chrony
PKG_VERSION:=		4.9
PKG_RELEASE:=		1
PKG_HASH:=		4924c6f530105bcd5b9e9e33c48a2ae1bfd889222c8480bc41601110efc864d0
PKG_DESCR:=		time server
PKG_SECTION:=		net/ntp
PKG_URL:=		https://chrony-project.org/
PKG_SITES:=		https://chrony-project.org/releases/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,CHRONY,chrony,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

chrony-install:
	$(INSTALL_DIR) $(IDIR_CHRONY)/etc
	$(CP) $(WRKSRC)/examples/chrony.conf.example1 \
		$(IDIR_CHRONY)/etc/chrony.conf
	$(INSTALL_DIR) $(IDIR_CHRONY)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/chronyd \
		$(IDIR_CHRONY)/usr/sbin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
