# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		apcupsd
PKG_VERSION:=		3.14.14
PKG_RELEASE:=		1
PKG_HASH:=		db7748559b6b4c3784f9856561ef6ac6199ef7bd019b3edcd7e0a647bf8f9867
PKG_DESCR:=		APC UPS daemon with integrated tcp/ip remote shutdown
PKG_SECTION:=		sys/misc
PKG_DEPENDS:=		libusb
PKG_BUILDDEP:=		libusb
PKG_URL:=		http://www.apcupsd.org
PKG_SITES:=		$(MASTER_SITE_SOURCEFORGE:=apcupsd/)
DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_CFLINE_APCUPSD:=	select BUSYBOX_WALL@
PKG_CFLINE_APCUPSD+=	select ADK_LINUX_KERNEL_USB_HID@

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,APCUPSD,apcupsd,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIGURE_ARGS+=	--prefix="${WRKINST}" --sbindir="/usr/sbin" --enable-usb
CONFIGURE_ENV+=		ac_cv_path_WALL=/usr/bin/wall
XAKE_FLAGS:=		VERBOSE=1 STRIP="" LD="$(TARGET_CXX)"

# XXX: custom init script?
apcupsd-install:
	$(INSTALL_DIR) $(IDIR_APCUPSD)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/apc{access,test,upsd} \
		$(IDIR_APCUPSD)/usr/sbin
	$(INSTALL_DIR) $(IDIR_APCUPSD)/etc
	$(INSTALL_DATA) $(WRKINST)/etc/apcupsd.conf $(IDIR_APCUPSD)/etc
	# default to USB-based UPS, avoid writing to /etc to keep cfgfs clean
	$(SED) 's/^UPSCABLE smart/UPSCABLE usb/' \
		-e 's/^UPSTYPE apcsmart/UPSTYPE usb/' \
		-e 's,^DEVICE /dev/ttyS0,DEVICE,' \
		-e 's,^PWRFAILDIR /etc,PWRFAILDIR /tmp,' \
		$(IDIR_APCUPSD)/etc/apcupsd.conf
	$(INSTALL_BIN) ./files/apccontrol $(IDIR_APCUPSD)/etc/

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
