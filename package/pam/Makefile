# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		pam
PKG_VERSION:=		1.7.0
PKG_RELEASE:=		1
PKG_HASH:=		1dad9cb50b4a19accd7d7b9716777caf5a0f33d26f018f27d63e9e095998f12b
PKG_DESCR:=		pluggable authentication modules
PKG_DEPENDS_GLIBC:=	libxcrypt
PKG_BUILDDEP:=		flex meson-host
PKG_BUILDDEP_GLIBC:=	libxcrypt
PKG_SECTION:=		sys/misc
PKG_URL:=		http://www.linux-pam.org/
PKG_SITES:=		https://github.com/linux-pam/linux-pam/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=		v$(PKG_VERSION).tar.gz
WRKDIST=                ${WRKDIR}/linux-pam-${PKG_VERSION}

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,PAM,pam,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

MESON_FLAGS+=		-Ddocs=disabled
CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

pam-install:
	$(INSTALL_DIR) $(STAGING_TARGET_DIR)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libpam*.so* \
			$(STAGING_TARGET_DIR)/usr/lib
	$(INSTALL_DIR) $(IDIR_PAM)/etc/security
	$(CP) $(WRKINST)/etc/security/* $(IDIR_PAM)/etc/security
	$(INSTALL_DIR) $(IDIR_PAM)/usr/lib/security
	$(CP) $(WRKINST)/usr/lib/libpam*.so* $(IDIR_PAM)/usr/lib
	$(CP) $(WRKINST)/usr/lib/security/*.so* $(IDIR_PAM)/usr/lib/security
	$(CP) ./files/pam.conf $(IDIR_PAM)/etc

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
