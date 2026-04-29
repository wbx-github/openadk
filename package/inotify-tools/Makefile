# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		inotify-tools
PKG_VERSION:=		4.25.9.0
PKG_RELEASE:=		1
PKG_HASH:=		d33a4fd24c72c2d08893f129d724adf725b93dae96c359e4f4e9f32573cc853b
PKG_DESCR:=		command line programs providing a simple interface to inotify
PKG_SECTION:=		sys/fs
PKG_KDEPENDS:=		inotify-user
PKG_URL:=		https://github.com/inotify-tools/
PKG_SITES:=		https://github.com/inotify-tools/inotify-tools/archive/refs/tags/

DISTFILES:=		$(PKG_VERSION).tar.gz

PKG_SUBPKGS:=		INOTIFYWAIT INOTIFYWATCH LIBINOTIFYTOOLS
PKGSC_LIBINOTIFYTOOLS:=	libs/misc
PKGSD_INOTIFYWAIT:=	wait for changes to files using inotify
PKGSS_INOTIFYWAIT:=	libinotifytools
PKGSD_INOTIFYWATCH:=	gather filesystem access statistics using inotify
PKGSS_INOTIFYWATCH:=	libinotifytools
PKGSD_LIBINOTIFYTOOLS:=	inotify tools library

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,INOTIFYWAIT,inotifywait,$(PKG_VERSION)-$(PKG_RELEASE),libinotifytools,$(PKGSD_INOTIFYWAIT),$(PKG_SECTION)))
$(eval $(call PKG_template,INOTIFYWATCH,inotifywatch,$(PKG_VERSION)-$(PKG_RELEASE),libinotifytools,$(PKGSD_INOTIFYWATCH),$(PKG_SECTION)))
$(eval $(call PKG_template,LIBINOTIFYTOOLS,libinotifytools,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKGSD_LIBINOTIFYTOOLS),$(PKGSC_LIBINOTIFYTOOLS)))

AUTOTOOL_STYLE:=	autoreconf

inotifywait-install:
	$(INSTALL_DIR) $(IDIR_INOTIFYWAIT)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/inotifywait $(IDIR_INOTIFYWAIT)/usr/bin

inotifywatch-install:
	$(INSTALL_DIR) $(IDIR_INOTIFYWATCH)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/inotifywatch $(IDIR_INOTIFYWATCH)/usr/bin

libinotifytools-install:
	$(INSTALL_DIR) $(IDIR_LIBINOTIFYTOOLS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libinotifytools.so* $(IDIR_LIBINOTIFYTOOLS)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
