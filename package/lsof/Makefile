# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		lsof
PKG_VERSION:=		4.99.6
PKG_RELEASE:=		1
PKG_HASH:=		6081dedf841cd61f8a022ff7cbe04ed78918a47dea3c39528c8571474167aa0f
PKG_DESCR:=		list open files
PKG_SECTION:=		sys/utils
PKG_DEPENDS:=		libtirpc
PKG_BUILDDEP:=		libtirpc
PKG_SITES:=		https://github.com/lsof-org/lsof/releases/download/$(PKG_VERSION)/

DISTFILES:=             ${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LSOF,lsof,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

lsof-install:
	$(INSTALL_DIR) $(IDIR_LSOF)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/lsof \
		$(IDIR_LSOF)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
