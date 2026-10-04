# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		gzip
PKG_VERSION:=		1.15
PKG_RELEASE:=		1
PKG_HASH:=		9aa0cc780dec156b8282844833b342ab7cb08c25d2cd9a1869cdd0df31deff48
PKG_DESCR:=		compression utility
PKG_SECTION:=		app/archive
PKG_URL:=		http://www.gnu.org/software/gzip/
PKG_SITES:=		${MASTER_SITE_GNU:=gzip/}
PKG_BB:=		1

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,GZIP,gzip,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

gzip-install:
	$(INSTALL_DIR) $(IDIR_GZIP)/usr/bin
	$(CP) $(WRKINST)/usr/bin/* $(IDIR_GZIP)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
