# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		ccid
PKG_VERSION:=		1.5.5
PKG_RELEASE:=		1
PKG_HASH:=		194708f75fe369d45dd7c15e8b3e8a7db8b49cfc5557574ca2a2e76ef12ca0ca
PKG_DESCR:=		generic usb ccid and iccd driver
PKG_SECTION:=		app/crypto
PKG_BUILDDEP:=		pcsc-lite
PKG_URL:=		https://ccid.apdu.fr/
PKG_SITES:=		https://ccid.apdu.fr/files/

DISTFILES:=             ${PKG_NAME}-${PKG_VERSION}.tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,CCID,ccid,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

CONFIGURE_ARGS+=	--disable-twinserial \
			--enable-libusb

ccid-install:
	$(INSTALL_DIR) $(IDIR_CCID)/etc/reader.conf.d
	$(INSTALL_DIR) $(IDIR_CCID)/usr/lib/pcsc/drivers
	$(INSTALL_DATA) ./files/gemalto.conf \
		$(IDIR_CCID)/etc/reader.conf.d
	-$(CP) $(WRKINST)/usr/lib/pcsc/drivers/* \
		$(IDIR_CCID)/usr/lib/pcsc/drivers

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
