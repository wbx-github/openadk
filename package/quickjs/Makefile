# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		quickjs
PKG_VERSION:=		2026-06-04
PKG_RELEASE:=		1
PKG_HASH:=		b376e839b322978313d929fd20663b11ba58b75df5a46c126dd19ea2fa70ad2a
PKG_DESCR:=		javascript engine
PKG_SECTION:=		dev/lang
PKG_URL:=		https://bellard.org/quickjs/
PKG_SITES:=		https://bellard.org/quickjs/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,QUICKJS,quickjs,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

XAKE_FLAGS+=		CROSS_PREFIX=$(TARGET_CROSS)
TARGET_LDFLAGS+=	-latomic
CONFIG_STYLE:=		manual

quickjs-install:
	$(INSTALL_DIR) $(IDIR_QUICKJS)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/qjs \
		$(IDIR_QUICKJS)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
