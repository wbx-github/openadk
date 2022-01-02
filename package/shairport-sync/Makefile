# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		shairport-sync
PKG_VERSION:=		3.3.8
PKG_RELEASE:=		1
PKG_GIT:=		tag
PKG_DESCR:=		airplay daemon	
PKG_SECTION:=		mm/audio	
PKG_DEPENDS:=		libressl libpopt libdaemon libconfig jack mosquitto libavahi
PKG_BUILDDEP:=		libressl popt libdaemon libconfig jack mosquitto avahi
PKG_URL:=		https://github.com/mikebrady/shairport-sync
PKG_SITES:=		https://github.com/mikebrady/shairport-sync.git

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,SHAIRPORT_SYNC,shairport-sync,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ARGS+=	--with-pkg-config \
  			--without-systemv \
  			--without-systemd \
			--with-libdaemon \
  			--with-avahi \
 			--disable-tinysvcmdns \
  			--with-alsa \
  			--with-jack \
  			--with-mqtt-client \
			-with-ssl=openssl

shairport-sync-install:
	$(INSTALL_DIR) $(IDIR_SHAIRPORT_SYNC)/usr/bin
	$(INSTALL_DIR) $(IDIR_SHAIRPORT_SYNC)/etc/shairport-sync
	$(INSTALL_BIN) $(WRKINST)/usr/bin/shairport-sync \
		$(IDIR_SHAIRPORT_SYNC)/usr/bin
	$(INSTALL_DATA) $(WRKINST)/etc/* \
		$(IDIR_SHAIRPORT_SYNC)/etc/shairport-sync/

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
