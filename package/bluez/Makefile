# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		bluez
PKG_VERSION:=		5.66
PKG_RELEASE:=		1
PKG_HASH:=		39fea64b590c9492984a0c27a89fc203e1cdc74866086efb8f4698677ab2b574
PKG_DESCR:=		bluetooth applications
PKG_SECTION:=		net/wifi
PKG_DEPENDS:=		glib dbus libreadline libudev
PKG_BUILDDEP:=		glib dbus readline eudev
PKG_KDEPENDS:=		bt bt-l2cap bt-sco bt-rfcomm bt-hidp bt-bnep
PKG_URL:=		http://www.bluez.org/
PKG_SITES:=		http://www.kernel.org/pub/linux/bluetooth/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,BLUEZ,bluez,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

TARGET_LDFLAGS+=	-lncurses

ifeq ($(ADK_TARGET_USE_STATIC_LIBS_ONLY),y)
XAKE_FLAGS+=		CCLD="$(TARGET_CC) -all-static -pthread"
endif

ifeq ($(ADK_TARGET_USE_PIE),y)
CONFIGURE_ARGS+=	--enable-pie
else
CONFIGURE_ENV+=		ac_cv_prog_cc_pie=no
CONFIGURE_ARGS+=	--disable-pie
endif

CONFIGURE_ARGS+=	--enable-tools \
			--enable-udev \
			--with-udevdir=/usr/bin \
			--disable-test \
			--disable-manpages \
			--disable-systemd \
			--disable-obex \
			--disable-cups

bluez-install:
	$(INSTALL_DIR) $(IDIR_BLUEZ)/etc/bluetooth
	$(INSTALL_DIR) $(IDIR_BLUEZ)/etc/dbus-1/system.d
	$(INSTALL_DIR) $(IDIR_BLUEZ)/usr/bin
	$(INSTALL_DIR) $(IDIR_BLUEZ)/usr/libexec/bluetooth
	$(INSTALL_BIN) $(WRKINST)/usr/libexec/bluetooth/bluetoothd \
		$(IDIR_BLUEZ)/usr/libexec/bluetooth
	$(CP) $(WRKINST)/usr/bin/* $(IDIR_BLUEZ)/usr/bin
	$(INSTALL_DATA) $(WRKBUILD)/src/main.conf \
		$(IDIR_BLUEZ)/etc/bluetooth
	$(INSTALL_DATA) ./files/bluetooth.conf \
		$(IDIR_BLUEZ)/etc/dbus-1/system.d

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
