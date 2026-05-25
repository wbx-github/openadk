# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		rng-tools
PKG_VERSION:=		5
PKG_RELEASE:=		1
PKG_HASH:=		60a102b6603bbcce2da341470cad42eeaa9564a16b4490e7867026ca11a3078e
PKG_DESCR:=		daemon to use hardware random number generators
PKG_SECTION:=		app/crypto
PKG_URL:=		http://gkernel.sourceforge.net/
PKG_SITES:=		https://sourceforge.net/projects/gkernel/files/rng-tools/$(PKG_VERSION)/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,RNG_TOOLS,rng-tools,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

rng-tools-install:
	$(INSTALL_DIR) $(IDIR_RNG_TOOLS)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/rngd $(IDIR_RNG_TOOLS)/usr/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
