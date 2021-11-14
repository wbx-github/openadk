# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libxcvt
PKG_VERSION:=		0.1.1
PKG_RELEASE:=		1
PKG_HASH:=		27ebce180d355f94c1992930bedb40a36f6d7312ee50bf7f0acbcd22f33e8c29
PKG_DESCR:=		xcvt library
PKG_SECTION:=		libs/misc
PKG_SITES:=		https://www.x.org/releases/individual/lib/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBXCVT,libxcvt,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

libxcvt-install:
	$(INSTALL_DIR) $(IDIR_LIBXCVT)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libxcvt*.so* \
		$(IDIR_LIBXCVT)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
