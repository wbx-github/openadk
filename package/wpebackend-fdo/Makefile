# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		wpebackend-fdo
PKG_VERSION:=		1.16.0
PKG_RELEASE:=		1
PKG_HASH:=		beddf321232d5bd08106c179dbc600f8ce88eb3620b4a59a6329063b78f64635
PKG_DESCR:=		freedesktop.org wpe backend
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		libwpe
PKG_BUILDDEP:=		wayland libwpe
PKG_URL:=		https://wpewebkit.org
PKG_SITES:=		https://wpewebkit.org/releases/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,WPEBACKEND_FDO,wpebackend-fdo,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

wpebackend-fdo-install:
	$(INSTALL_DIR) $(IDIR_WPEBACKEND_FDO)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libWPEBackend-fdo*.so* \
		$(IDIR_WPEBACKEND_FDO)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
