# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libseat
PKG_VERSION:=		0.8.0
PKG_RELEASE:=		1
PKG_HASH:=		a562a44ee33ccb20954a1c1ec9a90ecb2db7a07ad6b18d0ac904328efbcf65a0
PKG_DESCR:=		seat library
PKG_SECTION:=		libs/misc
PKG_URL:=		https://git.sr.ht/~kennylevinsen/seatd/
PKG_SITES:=		https://git.sr.ht/~kennylevinsen/seatd/archive/
PKG_LIBNAME:=		libseat
PKG_OPTS:=		dev

PKG_SUBPKGS:=		LIBSEAT SEATD
PKGSD_LIBSEAT:=		seat library
PKGSC_LIBSEAT:=		libs/misc
PKGSD_SEATD:=		seat daemon
PKGSC_SEATD:=		sys/misc
PKGSS_SEATD:=		libseat

DISTFILES:=		$(PKG_VERSION).tar.gz
WRKDIST=		${WRKDIR}/seatd-${PKG_VERSION}

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBSEAT,libseat,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))
$(eval $(call PKG_template,SEATD,seatd,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

libseat-install:
	$(INSTALL_DIR) $(IDIR_LIBSEAT)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libseat*.so* \
		$(IDIR_LIBSEAT)/usr/lib

seatd-install:
	$(INSTALL_DIR) $(IDIR_SEATD)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/seatd \
		$(IDIR_SEATD)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
