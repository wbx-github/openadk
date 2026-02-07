# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		chrony
PKG_VERSION:=		4.8
PKG_RELEASE:=		1
PKG_HASH:=		33ea8eb2a4daeaa506e8fcafd5d6d89027ed6f2f0609645c6f149b560d301706
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
