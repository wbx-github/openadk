# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		mtdev
PKG_VERSION:=		1.1.6
PKG_RELEASE:=		1
PKG_HASH:=		1325f389a2f25cd5f5a8ea4d29aad24aa7c3ec30401d679400dd79eb9c0a8dbb
PKG_DESCR:=		library which transforms all variants of kernel MT events
PKG_SECTION:=		libs/misc
PKG_SITES:=		https://bitmath.org/code/mtdev/
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,MTDEV,mtdev,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

mtdev-install:
	$(INSTALL_DIR) $(IDIR_MTDEV)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libmtdev*.so* \
		$(IDIR_MTDEV)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
