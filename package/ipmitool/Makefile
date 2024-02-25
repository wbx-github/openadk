# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		ipmitool
PKG_VERSION:=		1.8.19
PKG_RELEASE:=		1
PKG_HASH:=		48b010e7bcdf93e4e4b6e43c53c7f60aa6873d574cbd45a8d86fa7aaeebaff9c
PKG_DESCR:=		utility for controlling ipmi enabled devices
PKG_SECTION:=		net/misc
PKG_SITES:=		https://github.com/ipmitool/ipmitool/archive/refs/tags/

DISTFILES:=		IPMITOOL_1_8_19.tar.gz
WRKDIST=           	${WRKDIR}/$(PKG_NAME)-IPMITOOL_1_8_19

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,IPMITOOL,ipmitool,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

AUTOTOOL_STYLE:=	bootstrap

ipmitool-install:
	$(INSTALL_DIR) $(IDIR_IPMITOOL)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/ipmitool \
		$(IDIR_IPMITOOL)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
