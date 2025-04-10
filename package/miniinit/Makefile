# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		miniinit
PKG_VERSION:=		1.0
PKG_RELEASE:=		1
PKG_DESCR:=		minimal init
PKG_SECTION:=		base/init

NO_DISTFILES:=		1

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,MINIINIT,miniinit,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		manual
BUILD_STYLE:=		manual
INSTALL_STYLE:=		manual

do-build:
	PATH='$(HOST_PATH)' \
	$(TARGET_CC) $(TARGET_CPPFLAGS) $(TARGET_CFLAGS) $(TARGET_LDFLAGS) \
		-o $(WRKBUILD)/miniinit $(WRKBUILD)/miniinit.c

do-install:
	$(INSTALL_DIR) $(IDIR_MINIINIT)/sbin
	$(INSTALL_BIN) $(WRKBUILD)/miniinit $(IDIR_MINIINIT)/sbin/init

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
