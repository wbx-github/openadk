# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		open-iscsi
PKG_VERSION:=		2.1.9
PKG_RELEASE:=		1
PKG_HASH:=		60e2a1e3058a8af7f702e86a5a0511b05b8754d29d3d2df4e0e301399b5cf70a
PKG_DESCR:=		iscsi utilities
PKG_DEPENDS:=		libkmod libressl
PKG_BUILDDEP:=		cmake-host kmod libressl
PKG_SECTION:=		sys/fs
PKG_SITES:=		https://github.com/open-iscsi/open-iscsi/archive/refs/tags/

DISTFILES:=		$(PKG_VERSION).tar.gz
#WRKDIST=		${WRKDIR}/${PKG_NAME}-${PKG_VERSION}-${PKG_EXTRAVER}

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,OPEN_ISCSI,open-iscsi,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

MESON_FLAGS+=		-Dno_systemd=true \
			-Disns=disabled

open-iscsi-install:
	$(INSTALL_DIR) $(IDIR_OPEN_ISCSI)/usr/sbin $(IDIR_OPEN_ISCSI)/etc/iscsi
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/* $(IDIR_OPEN_ISCSI)/usr/sbin
	$(CP) $(WRKINST)/etc/iscsi/* $(IDIR_OPEN_ISCSI)/etc/iscsi

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
