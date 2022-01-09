# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		mpc
PKG_VERSION:=		0.34
PKG_RELEASE:=		1
PKG_HASH:=		691e3f3654bc10d022bb0310234d0bc2d8c075a698f09924d9ebed8f506fda20
PKG_DESCR:=		music player client
PKG_SECTION:=		mm/audio
PKG_DEPENDS:=		libmpdclient
PKG_BUILDDEP:=		libmpdclient
PKG_URL:=		http://www.musicpd.org/
PKG_SITES:=		http://www.musicpd.org/download/mpc/0/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,MPC,mpc,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

mpc-install:
	$(INSTALL_DIR) $(IDIR_MPC)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/mpc \
		$(IDIR_MPC)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
