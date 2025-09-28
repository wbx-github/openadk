# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libwpe
PKG_VERSION:=		1.16.3
PKG_RELEASE:=		1
PKG_HASH:=		c880fa8d607b2aa6eadde7d6d6302b1396ebc38368fe2332fa20e193c7ee1420
PKG_DESCR:=		general purpose library for wpe
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		libxkbcommon
PKG_BUILDDEP:=		libxkbcommon
PKG_URL:=		https://wpewebkit.org
PKG_SITES:=		https://wpewebkit.org/releases/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBWPE,libwpe,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIG_STYLE:=		cmake
CMAKE_FLAGS+=		-DCMAKE_POLICY_VERSION_MINIMUM=3.5

libwpe-install:
	$(INSTALL_DIR) $(IDIR_LIBWPE)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libwpe*.so* \
		$(IDIR_LIBWPE)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
