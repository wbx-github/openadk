# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		eudev
PKG_VERSION:=		3.2.14
PKG_RELEASE:=		1
PKG_HASH:=		8da4319102f24abbf7fff5ce9c416af848df163b29590e666d334cc1927f006f
PKG_DESCR:=		device manager
PKG_SECTION:=		sys/utils
PKG_BUILDDEP:=		gperf-host
PKG_DEPENDS:=		libkmod
PKG_KDEPENDS:=		inotify-user
PKG_URL:=		http://wiki.gentoo.org/wiki/Project:Eudev
PKG_SITES:=		https://github.com/eudev-project/eudev/releases/download/v$(PKG_VERSION)/
PKG_LIBNAME:=		libudev
PKG_OPTS:=		dev

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_SUBPKGS:=		UDEV LIBUDEV
PKGSD_UDEV:=		dynamic device management manager
PKGSC_LIBUDEV:=		libs/misc
PKGSD_LIBUDEV:=		dynamic device management library

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,UDEV,udev,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))
$(eval $(call PKG_template,LIBUDEV,libudev,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIGURE_ARGS+=	--disable-manpages \
			--disable-blkid \
			--enable-hwdb

udev-install:
	$(INSTALL_DIR) $(IDIR_UDEV)/usr/bin
	$(INSTALL_DIR) $(IDIR_UDEV)/etc/udev
	$(INSTALL_DIR) $(IDIR_UDEV)/usr/lib/udev
	$(INSTALL_DIR) $(IDIR_UDEV)/usr/sbin
	$(CP) $(WRKINST)/etc/udev/* $(IDIR_UDEV)/etc/udev
	$(CP) $(WRKINST)/usr/lib/udev/* $(IDIR_UDEV)/usr/lib/udev
	$(CP) $(WRKINST)/usr/bin/udevadm $(IDIR_UDEV)/usr/bin
	$(CP) $(WRKINST)/usr/sbin/udevd $(IDIR_UDEV)/usr/sbin
	$(CP) ./files/*.rules $(IDIR_UDEV)/etc/udev/rules.d

libudev-install:
	$(INSTALL_DIR) $(IDIR_LIBUDEV)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libudev.so* $(IDIR_LIBUDEV)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
