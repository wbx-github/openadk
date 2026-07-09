# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		mosquitto
PKG_VERSION:=		2.1.2
PKG_RELEASE:=		1
PKG_HASH:=		fd905380691ac65ea5a93779e8214941829e3d6e038d5edff9eac5fd74cbed02
PKG_DESCR:=		mqtt broker
PKG_SECTION:=		net/misc
PKG_DEPENDS:=		c-ares libopenssl cjson
PKG_BUILDDEP:=		cmake-host c-ares openssl cjson
PKG_NEEDS:=		threads
PKG_URL:=		http://mosquitto.org
PKG_SITES:=		http://mosquitto.org/files/source/

DISTFILES:=             ${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,MOSQUITTO,mosquitto,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=          cmake
MAKE_FLAGS+=		VERBOSE=1
CMAKE_FLAGS+=		-DINC_MEMTRACK=OFF \
			-DWITH_TLS_PSK=OFF \
			-DWITH_DOCS=OFF \
			-DWITH_TESTS=OFF \
			-DWITH_APPS=OFF \
			-DWITH_CTRL_SHELL=OFF

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
