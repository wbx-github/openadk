# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		json
PKG_VERSION:=		3.12.0
PKG_RELEASE:=		1
PKG_HASH:=		4b92eb0c06d10683f7447ce9406cb97cd4b453be18d7279320f7b2f025c10187
PKG_DESCR:=		C++ json library
PKG_SECTION:=		libs/misc
PKG_URL:=		https://github.com/nlohmann/json/
PKG_SITES:=		https://github.com/nlohmann/json/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,JSON,json,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

json-install:

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
