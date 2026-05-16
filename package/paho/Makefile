# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		paho
PKG_VERSION:=		v1.3.16
PKG_RELEASE:=		1
PKG_GIT:=		tag
PKG_DESCR:=		Eclipse Paho MQTT client library	
PKG_SECTION:=		libs/misc
PKG_BUILDDEP:=		cmake-host
PKG_URL:=		https://www.eclipse.org/paho/clients/c/a
PKG_SITES:=		https://github.com/eclipse/paho.mqtt.c.git
PKG_OPTS:=		dev

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,PAHO,paho,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIG_STYLE:=		cmake	

paho-install:
	$(INSTALL_DIR) $(IDIR_PAHO)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/MQTTVersion \
		$(IDIR_PAHO)/usr/bin
	$(INSTALL_DIR) $(IDIR_PAHO)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libpaho*.so* \
		$(IDIR_PAHO)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
