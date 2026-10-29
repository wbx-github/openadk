# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		patch
PKG_VERSION:=		2.8.1
PKG_RELEASE:=		1
PKG_HASH:=		3240c7959c5347c8ed347e3c4201c0337bf4240d5cf09d68889e58eeaba30e17
PKG_DESCR:=		patch utility
PKG_SECTION:=		sys/utils
PKG_URL:=		http://www.gnu.org/software/patch/
PKG_SITES:=		${MASTER_SITE_GNU:=patch/}
PKG_BB:=		1

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,PATCH,patch,$(PKG_VERSION)-${PKG_RELEASE}))
$(eval $(call PKG_template,PATCH,patch,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

patch-install:
	$(INSTALL_DIR) $(IDIR_PATCH)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/patch $(IDIR_PATCH)/usr/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
