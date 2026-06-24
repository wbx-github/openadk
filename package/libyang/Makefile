# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libyang
PKG_VERSION:=		3.13.6
PKG_RELEASE:=		1
PKG_HASH:=		5cd5018f39c830f97d70616c003990287ce5e820ae2792763a49e2a1f63af8d6
PKG_DESCR:=		yang data modelling language parser and toolkit 
PKG_SECTION:=		libs/misc
PKG_BUILDDEP:=		pcre2
PKG_DEPENDS:=		pcre2
PKG_URL:=		https://github.com/CESNET/libyang
PKG_SITES:=		https://github.com/CESNET/libyang/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBYANG,libyang,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=		$(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		cmake

libyang-install:
	$(INSTALL_DIR) $(IDIR_LIBYANG)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libyang*.so* \
		$(IDIR_LIBYANG)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
