# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libdrm
PKG_VERSION:=		2.4.114
PKG_RELEASE:=		1
PKG_HASH:=		3049cf843a47d12e5eeefbc3be3496d782fa09f42346bf0b7defe3d1e598d026
PKG_DESCR:=		direct rendering manager library
PKG_SECTION:=		libs/video
PKG_BUILDDEP:=		meson-host libpthread-stubs cairo libpciaccess
PKG_URL:=		http://dri.freedesktop.org/wiki/
PKG_SITES:=		http://dri.freedesktop.org/libdrm/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBDRM,libdrm,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

MESON_FLAGS+=		-Dvalgrind=disabled

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

libdrm-install:
	$(INSTALL_DIR) $(IDIR_LIBDRM)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libdrm*.so* \
		$(IDIR_LIBDRM)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
