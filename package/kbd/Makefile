# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		kbd
PKG_VERSION:=		2.10.0
PKG_RELEASE:=		1
PKG_HASH:=		6e5ca4f8d76ee9e3a8db700b667f13e12aac9933828a64e1aaad93d26be9b479
PKG_DESCR:=		keyboard and font utilities
PKG_SECTION:=		sys/hw
PKG_DEPENDS:=		libcheck
PKG_BUILDDEP:=		flex-host bison-host check
PKG_URL:=		http://kbd-project.org/
PKG_SITES:=		https://mirrors.edge.kernel.org/pub/linux/utils/kbd/

PKG_CFLINE_KBD:=	default y if ADK_TARGET_WITH_INPUT

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,KBD,kbd,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ARGS+=	--disable-vlock
CONFIGURE_ENV+=         ac_cv_func_malloc_0_nonnull=yes \
			ac_cv_func_realloc_0_nonnull=yes

kbd-install:
	$(INSTALL_DIR) $(IDIR_KBD)/usr/share
	$(CP) $(WRKINST)/usr/share/keymaps \
		$(IDIR_KBD)/usr/share
	$(CP) $(WRKINST)/usr/share/consolefonts \
		$(IDIR_KBD)/usr/share
	$(CP) $(WRKINST)/usr/share/consoletrans \
		$(IDIR_KBD)/usr/share
	$(CP) $(WRKINST)/usr/share/unimaps \
		$(IDIR_KBD)/usr/share
	$(INSTALL_DIR) $(IDIR_KBD)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/kbd_mode \
		$(IDIR_KBD)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/setfont \
		$(IDIR_KBD)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/showkey \
		$(IDIR_KBD)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/loadunimap \
		$(IDIR_KBD)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/loadkeys \
		$(IDIR_KBD)/usr/bin
ifeq ($(ADK_TARGET_SYSTEM_HP_JORNADA),y)
	$(INSTALL_DIR) $(IDIR_KBD)/etc
	$(CP) ./files/hpjornada.map $(IDIR_KBD)/etc
endif
ifeq ($(ADK_TARGET_SYSTEM_SHARP_ZAURUS),y)
	$(INSTALL_DIR) $(IDIR_KBD)/etc
	$(CP) ./files/zaurus.map $(IDIR_KBD)/etc
endif

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
