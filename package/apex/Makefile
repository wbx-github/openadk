# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		apex
PKG_VERSION:=		main
PKG_GIT:=		branch
PKG_HASH:=		d6c17d16012bc71989c2d608436c1954b27588510d5af69da7f5d5c04ef417aa
PKG_RELEASE:=		1
PKG_DESCR:=		bootloader for ixp4xx devices
PKG_SECTION:=		base/boot
PKG_SITES:=		https://github.com/linusw/apex.git

PKG_SYSTEM_DEPENDS:=	linksys-nslu2

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,APEX,apex,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

TARGET_LDFLAGS:=

do-configure:
	(cd $(WRKBUILD) && PATH='$(HOST_PATH)' ARCH=arm $(MAKE) openwrt-nslu2-armeb_config )

do-build:
	(cd $(WRKBUILD) && env \
		PATH='$(HOST_PATH)' \
		CROSS_COMPILE='$(TARGET_CROSS)' \
		KBUILD_HAVE_NLS=no \
		V=1 \
		ARCH=arm \
		$(MAKE) all)

apex-install:
	$(CP) $(WRKBUILD)/src/arch-arm/rom/apex.bin $(FW_DIR)

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
