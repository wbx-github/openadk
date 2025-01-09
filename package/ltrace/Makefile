# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		ltrace
PKG_VERSION:=		0.7.3
PKG_RELEASE:=		1
PKG_HASH:=		0e6f8c077471b544c06def7192d983861ad2f8688dd5504beae62f0c5f5b9503
PKG_DESCR:=		intercepts and records dynamic library calls 
PKG_SECTION:=		app/debug
PKG_DEPENDS:=		elfutils
PKG_BUILDDEP:=		elfutils
PKG_NEEDS:=		c++
PKG_URL:=		http://ltrace.org/
PKG_SITES:=		http://www.ltrace.org/

DISTFILES:=		$(PKG_NAME)_$(PKG_VERSION).orig.tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LTRACE,ltrace,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ARGS+=	--disable-werror

ltrace-install:
	$(INSTALL_DIR) $(IDIR_LTRACE)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/ltrace \
		$(IDIR_LTRACE)/usr/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
