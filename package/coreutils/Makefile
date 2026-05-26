# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		coreutils
PKG_VERSION:=		9.11
PKG_RELEASE:=		1
PKG_HASH:=		394024eda0a5955217ceda9cd1201e65dc8fa3aa29c2951135a49521d57c3cc3
PKG_DESCR:=		file, shell and text utilities
PKG_SECTION:=		base/apps
PKG_NEEDS:=		threads
PKG_URL:=		https://www.gnu.org/software/coreutils/
PKG_SITES:=		https://ftp.gnu.org/gnu/coreutils/

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,COREUTILS,coreutils,$(PKG_VERSION)-${PKG_RELEASE}))
$(eval $(call PKG_template,COREUTILS,coreutils,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ARGS+=	--disable-rpath

coreutils-install:
	$(INSTALL_DIR) $(IDIR_COREUTILS)/usr/bin
	$(CP) $(WRKINST)/usr/bin/* \
		$(IDIR_COREUTILS)/usr/bin

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
