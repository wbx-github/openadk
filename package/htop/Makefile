# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		htop
PKG_VERSION:=		3.2.1
PKG_RELEASE:=		1
PKG_HASH:=		5a17121cf1c69d2f2e557c0b29d45a2c353ab983f644742e1c2e4ece15aa6cbb
PKG_DESCR:=		graphical process manager
PKG_SECTION:=		sys/utils
PKG_DEPENDS:=		libncurses
PKG_BUILDDEP:=		ncurses
PKG_URL:=		http://hisham.hm/htop
PKG_SITES:=		https://github.com/htop-dev/htop/releases/download/$(PKG_VERSION)/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,HTOP,htop,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

TARGET_LDFLAGS+=	-ltinfo
CONFIGURE_ENV+= 	ac_cv_file__proc_stat=yes \
		  	ac_cv_file__proc_meminfo=yes
CONFIGURE_ARGS+=	--disable-unicode

htop-install:
	$(INSTALL_DIR) $(IDIR_HTOP)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/htop $(IDIR_HTOP)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
