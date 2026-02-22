# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		iso-codes
PKG_VERSION:=		4.20.1
PKG_RELEASE:=		1
PKG_HASH:=		2d7d9f6084ab9ce6c534ce71a3dd5144b6e474f3c97616459a88f73f44a64bff
PKG_DESCR:=		iso codes database
PKG_SECTION:=		libs/misc
PKG_SITES:=		https://salsa.debian.org/iso-codes-team/iso-codes/-/archive/v4.20.1/

DISTFILES:=             $(PKG_NAME)-v$(PKG_VERSION).tar.gz
WRKDIST=		$(WRKDIR)/$(PKG_NAME)-v$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,ISO_CODES,iso-codes,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

iso-codes-install:
	$(INSTALL_DIR) $(IDIR_ISO_CODES)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
