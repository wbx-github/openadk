# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		mosquitto
PKG_VERSION:=		2.0.18
PKG_RELEASE:=		1
PKG_HASH:=		d665fe7d0032881b1371a47f34169ee4edab67903b2cd2b4c083822823f4448a
PKG_DESCR:=		mqtt broker
PKG_SECTION:=		net/misc
PKG_DEPENDS:=		c-ares libressl
PKG_BUILDDEP:=		cmake-host c-ares libressl
PKG_NEEDS:=		threads
PKG_URL:=		http://mosquitto.org
PKG_SITES:=		http://mosquitto.org/files/source/

DISTFILES:=             ${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,MOSQUITTO,mosquitto,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=          cmake
CMAKE_FLAGS+=		-DINC_MEMTRACK=OFF -DWITH_TLS_PSK=OFF

mosquitto-install:
	$(INSTALL_DIR) $(IDIR_MOSQUITTO)/usr/bin
	$(INSTALL_DIR) $(IDIR_MOSQUITTO)/usr/sbin
	$(INSTALL_DIR) $(IDIR_MOSQUITTO)/usr/lib
	$(INSTALL_DIR) $(IDIR_MOSQUITTO)/etc/mosquitto
	$(INSTALL_BIN) $(WRKINST)/usr/bin/mosquitto* \
		$(IDIR_MOSQUITTO)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/mosquitto* \
		$(IDIR_MOSQUITTO)/usr/sbin
	$(INSTALL_DATA) $(WRKINST)/usr/etc/mosquitto/* \
		$(IDIR_MOSQUITTO)/etc/mosquitto
	$(CP) $(WRKINST)/usr/lib/*.so* \
		$(IDIR_MOSQUITTO)/usr/lib



include ${ADK_TOPDIR}/mk/pkg-bottom.mk
