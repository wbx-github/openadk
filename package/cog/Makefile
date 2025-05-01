# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		cog
PKG_VERSION:=		0.18.4
PKG_RELEASE:=		1
PKG_HASH:=		31d7079db2eeed790899d2f1f824dd6a54bf30d072d196d737be572f105d99b1
PKG_DESCR:=		minimalistic browser
PKG_SECTION:=		app/browser
PKG_DEPENDS:=		wpewebkit wpebackend-fdo libinput
PKG_BUILDDEP:=		wpewebkit wpebackend-fdo libinput
PKG_URL:=		https://wpewebkit.org
PKG_SITES:=		https://wpewebkit.org/releases/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,COG,cog,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

MESON_FLAGS+=		-Ddocumentation=false \
			-Dmanpages=false \
			-Dprograms=true \
			-Dwpe_api=2.0 \
			-Dplatforms="wayland"

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

cog-install:
	$(INSTALL_DIR) $(IDIR_COG)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libcogcore.so* \
		$(IDIR_COG)/usr/lib
	$(INSTALL_DIR) $(IDIR_COG)/usr/lib/cog/modules
	$(CP) $(WRKINST)/usr/lib/cog/modules/* \
		$(IDIR_COG)/usr/lib/cog/modules
	$(INSTALL_DIR) $(IDIR_COG)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/cog \
		$(IDIR_COG)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
