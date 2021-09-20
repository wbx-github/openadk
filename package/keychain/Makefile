# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		keychain
PKG_VERSION:=		2.8.5
PKG_RELEASE:=		1
PKG_HASH:=		dcce703e5001211c8ebc0528f45b523f84d2bceeb240600795b4d80cb8475a0b
PKG_DESCR:=		manage ssh and gpg keys in a secure manner
PKG_SECTION:=		app/crypto
PKG_URL:=		http://www.funtoo.org/en/security/keychain/intro/
PKG_SITES:=		https://github.com/funtoo/keychain/archive/refs/tags/

DISTFILES:=             ${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,KEYCHAIN,keychain,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIG_STYLE:=		manual
INSTALL_STYLE:=		manual
ALL_TARGET:=		keychain

do-install:
	$(INSTALL_DIR) $(IDIR_KEYCHAIN)/usr/bin
	$(INSTALL_BIN) $(WRKBUILD)/keychain \
		$(IDIR_KEYCHAIN)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
