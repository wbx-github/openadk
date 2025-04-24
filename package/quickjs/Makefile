# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		quickjs
PKG_VERSION:=		2024-01-13
PKG_RELEASE:=		1
PKG_HASH:=		3c4bf8f895bfa54beb486c8d1218112771ecfc5ac3be1036851ef41568212e03
PKG_DESCR:=		javascript engine
PKG_SECTION:=		dev/lang
PKG_URL:=		https://bellard.org/quickjs/
PKG_SITES:=		https://bellard.org/quickjs/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,QUICKJS,quickjs,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

XAKE_FLAGS+=		CROSS_PREFIX=$(TARGET_CROSS)
TARGET_CFLAGS:=
TARGET_LDFLAGS+=	-latomic
CONFIG_STYLE:=		manual

quickjs-install:
	$(INSTALL_DIR) $(IDIR_QUICKJS)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/qjs \
		$(IDIR_QUICKJS)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
