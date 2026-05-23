# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		empty
PKG_VERSION:=		0.6.23d
PKG_RELEASE:=		1
PKG_HASH:=		9ad495d52b942e3fd858643536d8d12e282568214300954d4518d8c22b893585
PKG_DESCR:=		similar to expect for interactive console apps
PKG_SECTION:=		sys/misc
PKG_URL:=		http://empty.sourceforge.net
PKG_SITES:=		https://sourceforge.net/projects/empty/files/empty/empty-$(PKG_VERSION)/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tgz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,EMPTY,empty,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		manual
INSTALL_STYLE:=		manual

do-install:
	$(INSTALL_DIR) $(WRKINST)/usr/bin
	$(INSTALL_BIN) $(WRKBUILD)/empty $(WRKINST)/usr/bin/empty

empty-install:
	$(INSTALL_DIR) $(IDIR_EMPTY)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/empty \
		$(IDIR_EMPTY)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
