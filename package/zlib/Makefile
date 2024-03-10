# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		zlib
PKG_VERSION:=		1.3.1
PKG_RELEASE:=		1
PKG_HASH:=		38ef96b8dfe510d42707d9c781877914792541133e1870841463bfa73f883e32
PKG_DESCR:=		implementation of the deflate compression method
PKG_SECTION:=		libs/comp
PKG_URL:=		http://www.zlib.net/
PKG_SITES:=		http://zlib.net/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,ZLIB,zlib,$(PKG_VERSION)-$(PKG_RELEASE)))
$(eval $(call PKG_template,ZLIB,zlib,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

ifeq ($(ADK_TARGET_USE_STATIC_AND_SHARED_LIBS),y)
TARGET_CFLAGS:=	$(filter-out -static,$(TARGET_CFLAGS))
TARGET_LDFLAGS:=$(filter-out -static,$(TARGET_LDFLAGS))
endif

HOST_STYLE:=		auto
HOST_CONFIG_STYLE:=	manual
HOST_CONFIGURE_ENV+=	uname=Linux

CONFIG_STYLE:=		manual
CONFIGURE_ENV+=		uname=Linux

ifeq ($(ADK_TARGET_BINFMT_FLAT)$(ADK_TARGET_USE_STATIC_LIBS_ONLY),)
CONFIGURE_OPTS:=	--shared
else
CONFIGURE_OPTS:=	--static
endif

host-configure:
	(cd $(WRKBUILD); \
		uname="Linux" \
		$(HOST_CONFIGURE_OPTS) \
		CFLAGS="$(HOST_CFLAGS) -fPIC" \
		CPPFLAGS="-I$(STAGING_HOST_DIR)/usr/include" \
		LDFLAGS="-L$(STAGING_HOST_DIR)/usr/lib" \
		./configure \
		--prefix=/usr \
		--shared \
	);

do-configure:
	(cd $(WRKBUILD); \
		uname="Linux" \
		$(TARGET_CONFIGURE_OPTS) \
		CFLAGS="$(TARGET_CFLAGS) -fPIC" \
		CPPFLAGS="-I$(STAGING_TARGET_DIR)/usr/include" \
		LDFLAGS="-L$(STAGING_TARGET_DIR)/usr/lib" \
		./configure \
		--prefix=/usr \
		$(CONFIGURE_OPTS) \
	);

zlib-install:
	$(INSTALL_DIR) $(IDIR_ZLIB)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libz.so* $(IDIR_ZLIB)/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
