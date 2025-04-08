# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		toybox
PKG_VERSION:=		0.8.12
PKG_RELEASE:=		1
PKG_HASH:=		ad88a921133ae2231d9f2df875ec0bd42af4429145caea7d7db9e02208a6fd2e
PKG_DESCR:=		linux tools collection
PKG_SECTION:=		base/apps
PKG_URL:=		http://landley.net/toybox/
PKG_SITES:=		http://landley.net/toybox/downloads/
PKG_BB:=		1

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,TOYBOX,toybox,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		manual
XAKE_FLAGS+=		CC="gcc" V=1 PREFIX="$(WRKINST)"

do-configure:
	-rm $(WRKBUILD)/toys/other/swap*.c
	-rm $(WRKBUILD)/toys/other/gpiod.c
	-rm $(WRKBUILD)/toys/other/lsattr.c
	-rm $(WRKBUILD)/toys/other/nsenter.c
	-rm $(WRKBUILD)/toys/posix/getconf.c
	-rm $(WRKBUILD)/toys/posix/iconv.c
	cp ./files/config $(WRKBUILD)/.config

toybox-install:
	$(CP) $(WRKINST)/* $(IDIR_TOYBOX)/
	$(INSTALL_DIR) $(IDIR_TOYBOX)/etc
	$(CP) ./files/inittab $(IDIR_TOYBOX)/etc

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
