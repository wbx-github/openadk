# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		tinyproxy
PKG_VERSION:=		1.11.0
PKG_RELEASE:=		1
PKG_HASH:=		c1ec81cfc4c551d2c24e0227a5aeeaad8723bd9a39b61cd729e516b82eaa3f32
PKG_DESCR:=		lightweight http and https proxy
PKG_SECTION:=		net/proxy
PKG_URL:=		https://tinyproxy.github.io
PKG_SITES:=		https://github.com/tinyproxy/tinyproxy/releases/download/$(PKG_VERSION)/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,TINYPROXY,tinyproxy,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIGURE_ARGS+=	--disable-manpage_support
CONFIGURE_ENV+=         ac_cv_func_malloc_0_nonnull=yes \
			ac_cv_func_realloc_0_nonnull=yes

tinyproxy-install:
	$(INSTALL_DIR) $(IDIR_TINYPROXY)/usr/bin
	$(INSTALL_DIR) $(IDIR_TINYPROXY)/etc/tinyproxy
	$(INSTALL_DIR) $(IDIR_TINYPROXY)/usr/share/tinyproxy
	$(INSTALL_DATA) ./files/tinyproxy.conf \
		$(IDIR_TINYPROXY)/etc/tinyproxy/
	$(INSTALL_BIN) $(WRKINST)/usr/bin/tinyproxy \
		$(IDIR_TINYPROXY)/usr/bin/
	$(INSTALL_DATA) $(WRKINST)/usr/share/tinyproxy/{default,stats,debug}.html \
		$(IDIR_TINYPROXY)/usr/share/tinyproxy/

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
