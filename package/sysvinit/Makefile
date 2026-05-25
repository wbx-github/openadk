# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		sysvinit
PKG_VERSION:=		3.15
PKG_RELEASE:=		1
PKG_HASH:=		4c1a28d6e97fa656ec70aa736185d72c9b31a6a4fa414f2fddacd61c7d9f47cf
PKG_DESCR:=		sysv init system
PKG_SECTION:=		base/init
PKG_SITES:=		https://github.com/slicer69/sysvinit/archive/refs/tags/

DISTFILES:=             $(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,SYSVINIT,sysvinit,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		manual

sysvinit-install:
	$(INSTALL_DIR) $(IDIR_SYSVINIT)/etc
	$(CP) ./files/inittab $(IDIR_SYSVINIT)/etc
	$(INSTALL_DIR) $(IDIR_SYSVINIT)/sbin
	$(INSTALL_BIN) $(WRKINST)/sbin/init \
		$(IDIR_SYSVINIT)/sbin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
