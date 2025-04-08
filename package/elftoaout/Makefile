# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		elftoaout
PKG_VERSION:=		2.3
PKG_RELEASE:=		1
PKG_DESCR:=		elf to a.out converter
PKG_SECTION:=		sys/misc

PKG_CFLINE_ELFTOAOUT:=	depends on ADK_HOST_ONLY

NO_DISTFILES:=		1

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,ELFTOAOUT,elftoaout,$(PKG_VERSION)-$(PKG_RELEASE)))

HOST_STYLE:=		manual

host-build:
	$(HOST_CC) $(HOST_CFLAGS) -o $(WRKBUILD)/elftoaout $(WRKBUILD)/elftoaout.c

elftoaout-hostinstall:
	$(INSTALL_DIR) $(STAGING_HOST_DIR)/usr/bin
	$(INSTALL_BIN) $(WRKBUILD)/elftoaout $(STAGING_HOST_DIR)/usr/bin

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
