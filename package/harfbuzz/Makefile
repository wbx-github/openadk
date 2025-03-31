# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		harfbuzz
PKG_VERSION:=		11.0.0
PKG_RELEASE:=		1
PKG_HASH:=		85178b78f0e405269bbc0c17a55545708d86dae63a85f04cd29f71dd422879a8
PKG_DESCR:=		opentype text shaping engine
PKG_SECTION:=		libs/fonts
PKG_SITES:=		https://github.com/harfbuzz/harfbuzz/archive/refs/tags/
PKG_DEPENDS:=		cairo icu4c
PKG_BUILDDEP:=		cairo icu4c
HOST_BUILDDEP:=		cairo-host icu4c-host
PKG_NEEDS:=		c++
PKG_OPTS:=		dev

DISTFILES:=             ${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,HARFBUZZ,harfbuzz,$(PKG_VERSION)-${PKG_RELEASE}))
$(eval $(call PKG_template,HARFBUZZ,harfbuzz,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

HOST_STYLE:=		meson
CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

MESON_FLAGS+=		-Dtests=disabled

host-postinstall:
	$(CP) $(WRKBUILD)/meson-private/harfbuzz.pc \
		$(STAGING_HOST_DIR)/usr/lib/pkgconfig/

harfbuzz-install:
	$(INSTALL_DIR) $(IDIR_HARFBUZZ)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libharfbuzz*.so* \
		$(IDIR_HARFBUZZ)/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
