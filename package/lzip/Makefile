# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		lzip
PKG_VERSION:=		1.26
PKG_RELEASE:=		1
PKG_HASH:=		641cf30961525cbe3b340cc883436c8854e9f5032f459f444de4782b621e6572
PKG_DESCR:=		compression utility
PKG_SECTION:=		app/archive
PKG_NEEDS:=		c++
PKG_URL:=		http://www.nongnu.org/lzip/lzip.html
PKG_SITES:=		http://download.savannah.gnu.org/releases/lzip/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,LZIP,lzip,$(PKG_VERSION)-${PKG_RELEASE}))
$(eval $(call PKG_template,LZIP,lzip,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

HOST_LDFLAGS+=		-static-libstdc++

lzip-install:
	$(INSTALL_DIR) $(IDIR_LZIP)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/lzip $(IDIR_LZIP)/usr/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
