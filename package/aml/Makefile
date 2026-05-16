# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		aml
PKG_VERSION:=		1.0.0
PKG_RELEASE:=		1
PKG_HASH:=		b2b8f743213af39f40e8bc611147d69e2ea9e010b9b19cb65246582338f28d96
PKG_DESCR:=		andris's main loop
PKG_SECTION:=		libs/misc
PKG_SITES:=		https://github.com/any1/aml/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,AML,aml,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

aml-install:
	$(INSTALL_DIR) $(IDIR_AML)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libaml*.so* \
		$(IDIR_AML)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
