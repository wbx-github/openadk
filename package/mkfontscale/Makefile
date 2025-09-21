# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		mkfontscale
PKG_VERSION:=		1.2.3
PKG_RELEASE:=		1
PKG_HASH:=		3a026b468874eb672a1d0a57dbd3ddeda4f0df09886caf97d30097b70c2df3f8
PKG_DESCR:=		font utility
PKG_SECTION:=		x11/fonts
PKG_DEPENDS:=		freetype libfontenc
PKG_BUILDDEP:=		freetype libfontenc
PKG_SITES:=		http://www.x.org/releases/individual/app/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,MKFONTSCALE,mkfontscale,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

mkfontscale-install:
	$(INSTALL_DIR) $(IDIR_MKFONTSCALE)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/mkfontscale \
		$(IDIR_MKFONTSCALE)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
