# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		neatvnc
PKG_VERSION:=		1.0.0
PKG_RELEASE:=		1
PKG_HASH:=		993dedc30e72981650770c04438e9759537e4677010e2dab5e792c39afe74601
PKG_DESCR:=		vnc server library
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		aml
PKG_BUILDDEP:=		aml
PKG_SITES:=		https://github.com/any1/neatvnc/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,NEATVNC,neatvnc,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

neatvnc-install:
	$(INSTALL_DIR) $(IDIR_NEATVNC)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libneatvnc*.so* \
		$(IDIR_NEATVNC)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
