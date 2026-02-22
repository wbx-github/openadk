# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		duktape
PKG_VERSION:=		2.7.0
PKG_RELEASE:=		1
PKG_HASH:=		90f8d2fa8b5567c6899830ddef2c03f3c27960b11aca222fa17aa7ac613c2890
PKG_DESCR:=		javascript library
PKG_SECTION:=		libs/misc
PKG_URL:=		https://duktape.org/
PKG_SITES:=		https://duktape.org/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,DUKTAPE,duktape,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIG_STYLE:=		manual
MAKE_FILE:=		Makefile.sharedlibrary
FAKE_FLAGS+=		INSTALL_PREFIX=/usr

duktape-install:
	$(INSTALL_DIR) $(IDIR_DUKTAPE)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libduktape*.so* \
		$(IDIR_DUKTAPE)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
