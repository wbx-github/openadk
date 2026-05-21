# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		ser2net
PKG_VERSION:=		4.6.7
PKG_RELEASE:=		1
PKG_HASH:=		6b921bc7efb1b9a8a78268d63332701902cc1c8dbac51842d46ede6ffb5fa2a4
PKG_DESCR:=		allowing network connections to serial ports
PKG_SECTION:=		net/misc
PKG_DEPENDS:=		yaml gensio
PKG_BUILDDEP:=		yaml gensio
PKG_SITES:=		https://sourceforge.net/projects/ser2net/files/ser2net/

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,SER2NET,ser2net,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

ser2net-install:
	$(INSTALL_DIR) $(IDIR_SER2NET)/etc/ser2net $(IDIR_SER2NET)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/ser2net $(IDIR_SER2NET)/usr/sbin
	$(INSTALL_DATA) $(WRKBUILD)/ser2net.yaml $(IDIR_SER2NET)/etc/ser2net

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
