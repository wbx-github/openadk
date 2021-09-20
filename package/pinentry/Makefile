# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		pinentry
PKG_VERSION:=		1.2.0
PKG_RELEASE:=		1
PKG_HASH:=		e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
PKG_DESCR:=		pinentry application
PKG_SECTION:=		app/crypto
PKG_URL:=		https://www.gnupg.org
PKG_SITES:=		https://www.gnupg.org/ftp/gcrypt/pinentry/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,PINENTRY,pinentry,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

pinentry-install:
	$(INSTALL_DIR) $(IDIR_PINENTRY)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/pinentry \
		$(IDIR_PINENTRY)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
