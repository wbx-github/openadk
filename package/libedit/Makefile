# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libedit
PKG_VERSION:=		20260512-3.1
PKG_RELEASE:=		1
PKG_HASH:=		432d5e7ea8b0116dd39f2eca7bc11d0eed77faa6b77ea526ace89907c23ea4a0
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
