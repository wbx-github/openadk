# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libinput
PKG_VERSION:=		1.28.1
PKG_RELEASE:=		1
PKG_HASH:=		a13f8c9a7d93df3c85c66afd135f0296701d8d32f911991b7aa4273fdd6a42a3
PKG_DESCR:=		input library
PKG_DEPENDS:=		mtdev libevdev libudev
PKG_BUILDDEP:=		mtdev libevdev eudev
PKG_SECTION:=		libs/misc
PKG_SITES:=		https://gitlab.freedesktop.org/libinput/libinput/-/archive/$(PKG_VERSION)/
PKG_OPTS:=		dev

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

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
