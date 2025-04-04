# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		simpleinit
PKG_VERSION:=		1.0
PKG_RELEASE:=		1
PKG_DESCR:=		very simple init
PKG_SECTION:=		base/init

NO_DISTFILES:=		1

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,SIMPLEINIT,simpleinit,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

TARGET_CPPFLAGS+=	-DCONFIG_USER_INIT_CONSOLE_SH
TARGET_CFLAGS+=		-Wno-incompatible-pointer-types

do-build:
	PATH='$(HOST_PATH)' \
	$(TARGET_CC) $(TARGET_CPPFLAGS) $(TARGET_CFLAGS) $(TARGET_LDFLAGS) \
		-o $(WRKBUILD)/simpleinit $(WRKBUILD)/simpleinit.c

do-install:
	$(INSTALL_DIR) $(IDIR_SIMPLEINIT)/etc
	$(CP) ./files/rc $(IDIR_SIMPLEINIT)/etc
	$(CP) ./files/inittab $(IDIR_SIMPLEINIT)/etc
	$(INSTALL_DIR) $(IDIR_SIMPLEINIT)/sbin
	$(INSTALL_BIN) $(WRKBUILD)/simpleinit $(IDIR_SIMPLEINIT)/sbin/init

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
