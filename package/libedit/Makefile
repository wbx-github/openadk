# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libedit
PKG_VERSION:=		20251016-3.1
PKG_RELEASE:=		1
PKG_HASH:=		21362b00653bbfc1c71f71a7578da66b5b5203559d43134d2dd7719e313ce041
PKG_DESCR:=		editline library
PKG_BUILDDEP:=		ncurses
PKG_SECTION:=		libs/misc
PKG_SITES:=		https://www.thrysoee.dk/editline/
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBEDIT,libedit,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

libedit-install:
	$(INSTALL_DIR) $(IDIR_LIBEDIT)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libedit*.so* \
		$(IDIR_LIBEDIT)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
