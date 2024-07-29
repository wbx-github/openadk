# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libedit
PKG_VERSION:=		20230828-3.1
PKG_RELEASE:=		1
PKG_HASH:=		4ee8182b6e569290e7d1f44f0f78dac8716b35f656b76528f699c69c98814dad
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
