# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libinput
PKG_VERSION:=		1.19.2
PKG_RELEASE:=		1
PKG_HASH:=		0fc39f0af3ee1a77c60c34bc45391a4d0879169f7c0f7bbbeb5eef590b98b883
PKG_DESCR:=		input library
PKG_DEPENDS:=		mtdev libevdev libudev
PKG_BUILDDEP:=		mtdev libevdev eudev
PKG_SECTION:=		libs/misc
PKG_SITES:=		https://www.freedesktop.org/software/libinput/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBINPUT,libinput,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

MESON_FLAGS+=		-Dlibwacom=false \
			-Dtests=false \
			-Ddebug-gui=false

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

libinput-install:
	$(INSTALL_DIR) $(IDIR_LIBINPUT)/usr/share/libinput
	$(CP) $(WRKINST)/usr/share/libinput/* \
		$(IDIR_LIBINPUT)/usr/share/libinput/
	$(INSTALL_DIR) $(IDIR_LIBINPUT)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libinput*.so* \
		$(IDIR_LIBINPUT)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
