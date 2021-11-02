# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libargon2
PKG_VERSION:=		20190702
PKG_RELEASE:=		1
PKG_HASH:=		daf972a89577f8772602bf2eb38b6a3dd3d922bf5724d45e7f9589b5e830442c
PKG_DESCR:=		Password hashing software that won the Password Hashing Competition (PHC)
PKG_SECTION:=		libs/crypto
PKG_URL:=		https://github.com/P-H-C/phc-winner-argon2
PKG_SITES:=		https://github.com/P-H-C/phc-winner-argon2/archive/refs/tags/
DISTFILES:=             $(PKG_VERSION).tar.gz
WRKDIST=		$(WRKDIR)/phc-winner-argon2-$(PKG_VERSION)

PKG_SUBPKGS:=		LIBARGON2 ARGON2
PKGSD_ARGON2:=		libargon2 command-line utility
PKGSS_ARGON2:=		libargon2
PKGSC_ARGON2:=		app/crypto

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBARGON2,libargon2,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))
$(eval $(call PKG_template,ARGON2,argon2,$(PKG_VERSION)-$(PKG_RELEASE),$(PKGSS_ARGON2),$(PKGSD_ARGON2),$(PKGSC_ARGON2)))

CONFIG_STYLE:=		manual
MAKE_ENV+=		LIBRARY_REL=lib

libargon2-install:
	$(INSTALL_DIR) ${IDIR_LIBARGON2}/usr/lib
	$(CP) ${WRKINST}/usr/lib/libargon2.so* \
		${IDIR_LIBARGON2}/usr/lib

argon2-install:
	$(INSTALL_DIR) $(IDIR_ARGON2)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/argon2 \
		$(IDIR_ARGON2)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
