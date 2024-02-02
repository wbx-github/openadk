# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		tinyxml2
PKG_VERSION:=		10.0.0
PKG_RELEASE:=		1
PKG_HASH:=		3bdf15128ba16686e69bce256cc468e76c7b94ff2c7f391cc5ec09e40bff3839
PKG_DESCR:=		small xml library
PKG_SECTION:=		libs/misc
PKG_BUILDDEP+=		meson-host
PKG_SITES:=		https://github.com/leethomason/tinyxml2/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,TINYXML2,tinyxml2,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

tinyxml2-install:
	$(INSTALL_DIR) $(IDIR_TINYXML2)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libtinyxml2*.so* \
		$(IDIR_TINYXML2)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
