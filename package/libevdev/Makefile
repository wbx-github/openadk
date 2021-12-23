# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libevdev
PKG_VERSION:=		1.12.0
PKG_RELEASE:=		1
PKG_HASH:=		2f729e3480695791f9482e8388bd723402b89f0eaf118057bbdea3cecee9b237
PKG_DESCR:=		wrapper library for evdev devices
PKG_SECTION:=		libs/misc
PKG_URL:=		add project url
PKG_SITES:=		https://www.freedesktop.org/software/libevdev/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBEVDEV,libevdev,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

libevdev-install:
	$(INSTALL_DIR) $(IDIR_LIBEVDEV)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libevdev*.so* \
		$(IDIR_LIBEVDEV)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
