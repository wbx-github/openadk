# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		coreutils
PKG_VERSION:=		9.5
PKG_RELEASE:=		1
PKG_HASH:=		cd328edeac92f6a665de9f323c93b712af1858bc2e0d88f3f7100469470a1b8a
PKG_DESCR:=		file, shell and text utilities
PKG_SECTION:=		base/apps
PKG_NEEDS:=		threads
PKG_URL:=		http://www.gnu.org/software/coreutils/
PKG_SITES:=		http://ftp.gnu.org/gnu/coreutils/

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
