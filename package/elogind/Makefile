# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		elogind
PKG_VERSION:=		255.25
PKG_RELEASE:=		1
PKG_HASH:=		103d5b5fac8dca30535573c5067c730ed8518a40ac0616442de29f74747778f1
PKG_DESCR:=		login and session manager
PKG_SECTION:=		x11/misc
PKG_DEPENDS:=		libcap
PKG_BUILDDEP:=		libcap python3-jinja2-host
PKG_SITES:=		https://github.com/elogind/elogind/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,ELOGIND,elogind,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

MESON_FLAGS:=		-Dtests=false

elogind-install:
	$(INSTALL_DIR) $(IDIR_ELOGIND)/etc
	$(CP) $(WRKINST)/etc/* \
		$(IDIR_ELOGIND)/etc
	$(INSTALL_DIR) $(IDIR_ELOGIND)/usr/bin
	$(CP) $(WRKINST)/usr/bin/* \
		$(IDIR_ELOGIND)/usr/bin
	$(INSTALL_DIR) $(IDIR_ELOGIND)/usr/libexec
	$(CP) $(WRKINST)/usr/libexec/* \
		$(IDIR_ELOGIND)/usr/libexec
	$(INSTALL_DIR) $(IDIR_ELOGIND)/usr/lib
	$(CP) $(WRKINST)/usr/lib/* \
		$(IDIR_ELOGIND)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
