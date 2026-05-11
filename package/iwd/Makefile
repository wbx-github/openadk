# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		iwd
PKG_VERSION:=		3.12
PKG_RELEASE:=		1
PKG_HASH:=		81a12fd4a03dd8e3d60c72b19767507c913f4b0fa4e5fc4ef5ed3f5ffae178dd
PKG_DESCR:=		daemon for wpa/wpa2/wpa3 client access
PKG_SECTION:=		net/wifi
PKG_KDEPENDS:=		crypto-aes crypto-des crypto-md5 crypto-sha1
PKG_KDEPENDS+=		crypto-sha256 crypto-hmac crypto-user-api-hash
PKG_KDEPENDS+=		crypto-user-api-skcipher crypto-user-api-aead
PKG_KDEPENDS+=		crypto-cmac
PKG_DEPENDS:=		readline dbus ncurses
PKG_BUILDDEP:=		readline dbus ncurses
PKG_SITES:=		https://mirrors.edge.kernel.org/pub/linux/network/wireless/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,IWD,iwd,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

TARGET_LDFLAGS+=	-lncursesw
CONFIGURE_ARGS+=	--disable-manual-pages \
		  	--disable-monitor \
		  	--disable-systemd-service \
		  	--with-dbus-datadir=/usr/share

iwd-install:
	$(INSTALL_DIR) $(IDIR_IWD)/etc/iwd
	$(INSTALL_DIR) $(IDIR_IWD)/usr/bin
	$(INSTALL_DIR) $(IDIR_IWD)/usr/sbin
	$(INSTALL_DIR) $(IDIR_IWD)/usr/share/dbus-1/system.d
	$(CP) $(WRKINST)/usr/bin/iwctl $(IDIR_IWD)/usr/bin/
	$(CP) $(WRKINST)/usr/libexec/iwd $(IDIR_IWD)/usr/sbin/
	$(CP) $(WRKINST)/usr/share/dbus-1/system.d/iwd-dbus.conf \
		$(IDIR_IWD)/usr/share/dbus-1/system.d
	$(CP) ./files/main.conf $(IDIR_IWD)/etc/iwd

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
