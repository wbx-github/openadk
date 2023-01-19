# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libseat
PKG_VERSION:=		0.7.0
PKG_RELEASE:=		1
PKG_HASH:=		ea6ccbaf86949dba4eda64761b11aa8d05b61fc60f569b0fc05f2c4d06baeb87
PKG_DESCR:=		seat library
PKG_SECTION:=		libs/misc
PKG_URL:=		https://git.sr.ht/~kennylevinsen/seatd
PKG_SITES:=		https://git.sr.ht/~kennylevinsen/seatd
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBSEAT,libseat,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

libseat-install:
	$(INSTALL_DIR) $(IDIR_LIBSEAT)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libseat*.so* \
		$(IDIR_LIBSEAT)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
