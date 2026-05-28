# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		keyutils
PKG_VERSION:=		1.6.1
PKG_RELEASE:=		1
PKG_HASH:=		c8b15722ae51d95b9ad76cc6d49a4c2cc19b0c60f72f61fb9bf43eea7cbd64ce
PKG_DESCR:=		utilities for managing the key retention facility
PKG_SECTION:=		libs/misc
PKG_NEEDS:=		mmu
PKG_SITES:=		https://people.redhat.com/dhowells/keyutils/
PKG_OPTS:=		dev

DISTFILES:=             ${PKG_NAME}-${PKG_VERSION}.tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,KEYUTILS,keyutils,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIG_STYLE:=		manual

keyutils-install:
	$(INSTALL_DIR) $(IDIR_KEYUTILS)/usr/lib
	$(CP) $(WRKBUILD)/libkeyutils.so* \
		$(IDIR_KEYUTILS)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
