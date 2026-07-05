# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		atop
PKG_VERSION:=		2.12.1
PKG_RELEASE:=		1
PKG_HASH:=		0f49f3aa5e3449f8c1cf10ac08036e2b67887640fe7980b8bc6ca9fd84d46fdf
PKG_DESCR:=		performance monitor for linux that is capable of reporting the activity of all processes
PKG_SECTION:=		sys/utils
PKG_DEPENDS:=		libncurses glib
PKG_BUILDDEP:=		ncurses glib
PKG_URL:=		https://github.com/Atoptool/atop
PKG_SITES:=		https://github.com/Atoptool/atop/archive/refs/tags/

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,ATOP,atop,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		manual

atop-install:
	$(INSTALL_DIR) $(IDIR_ATOP)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/atop \
		$(IDIR_ATOP)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
