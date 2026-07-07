# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		ltrace
PKG_VERSION:=		0.8.1
PKG_RELEASE:=		1
PKG_HASH:=		11c85a1353fcf2b5438b19d0ccc2d376c96656ce6f11cf9537e3a92b84392c58
PKG_DESCR:=		intercepts and records dynamic library calls 
PKG_SECTION:=		app/debug
PKG_DEPENDS:=		elfutils
PKG_BUILDDEP:=		elfutils
PKG_NEEDS:=		c++
PKG_URL:=		http://ltrace.org/
PKG_SITES:=		https://gitlab.com/cespedes/ltrace/-/archive/0.8.1/

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LTRACE,ltrace,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ARGS+=	--disable-werror

ltrace-install:
	$(INSTALL_DIR) $(IDIR_LTRACE)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/ltrace \
		$(IDIR_LTRACE)/usr/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
