# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		pcsc-lite
PKG_VERSION:=		2.4.1
PKG_RELEASE:=		1
PKG_HASH:=		afd3ba68c8000d2be048dc292df99a9812df9ad2efaf0a366eea22ac1faa19a7
PKG_DESCR:=		middleware for smartcards
PKG_SECTION:=		app/crypto
PKG_DEPENDS:=		libusb libusb-compat
PKG_BUILDDEP:=		libusb libusb-compat
PKG_NEEDS:=		threads
PKG_URL:=		https://pcsclite.apdu.fr/
PKG_SITES:=		https://pcsclite.apdu.fr/files/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,PCSC_LITE,pcsc-lite,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

MESON_FLAGS+=		-Dlibsystemd=false \
			-Dpolkit=false

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

pcsc-lite-install:
	$(INSTALL_DIR) $(IDIR_PCSC_LITE)/etc/reader.conf.d
	$(INSTALL_DIR) $(IDIR_PCSC_LITE)/usr/sbin
	$(INSTALL_DIR) $(IDIR_PCSC_LITE)/usr/lib
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/pcscd \
		$(IDIR_PCSC_LITE)/usr/sbin
	$(CP) $(WRKINST)/usr/lib/libpcsclite.so* \
		$(IDIR_PCSC_LITE)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
