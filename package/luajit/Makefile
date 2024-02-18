# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		luajit
PKG_VERSION:=		0d313b243194a0b8d2399d8b549ca5a0ff234db5
PKG_GIT:=		hash
PKG_RELEASE:=		1
PKG_DESCR:=		just in time compiler for lua
PKG_SECTION:=		dev/lang
PKG_URL:=		http://luajit.org/download/
PKG_SITES:=		https://luajit.org/git/luajit.git

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LUAJIT,luajit,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		manual
MAKE_TARGET:=		amalg
XAKE_FLAGS+=		STATIC_CC="$(TARGET_CC)" \
			DYNAMIC_CC="$(TARGET_CC)" \
			CROSS='$(TARGET_CROSS)' \
			PREFIX=/usr \
			CFLAGS='' \
			LDFLAGS='' \
			TARGET_CFLAGS='$(TARGET_CFLAGS) -fPIC' \
			TARGET_LDFLAGS='$(TARGET_LDFLAGS)' \
			HOST_CC='$(HOST_CC)' \
			HOST_CFLAGS='$(HOST_CFLAGS)' \
			HOST_LDFLAGS='$(HOST_LDFLAGS)' \
			Q=''

luajit-install:
	$(INSTALL_DIR) $(IDIR_LUAJIT)/usr/bin
	$(CP) $(WRKINST)/usr/bin/luajit* \
		$(IDIR_LUAJIT)/usr/bin
	$(INSTALL_DIR) $(IDIR_LUAJIT)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libluajit-*.so* \
		$(IDIR_LUAJIT)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
