# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		avahi
PKG_VERSION:=		0.8
PKG_RELEASE:=		1
PKG_HASH:=		060309d7a333d38d951bc27598c677af1796934dbd98e1024e7ad8de798fedda
PKG_DESCR:=		multicast dns daemon and dns-sd server
PKG_SECTION:=		net/dns
PKG_BUILDDEP:=		libdaemon expat gdbm glib libevent
PKG_NEEDS:=		c++ intl
PKG_URL:=		http://avahi.org/
PKG_SITES:=		https://github.com/lathiat/avahi/releases/download/v$(PKG_VERSION)/
PKG_LIBNAME:=		libavahi
PKG_OPTS:=		dev

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_SUBPKGS:=		AVAHI LIBAVAHI
PKGSS_AVAHI:=		libavahi libdaemon libexpat dbus
PKGSB_AVAHI:=		dbus
PKGSS_LIBAVAHI:=	dbus
PKGSB_LIBAVAHI:=	dbus
PKGSD_LIBAVAHI:=	dns-sd and mdns library
PKGSC_LIBAVAHI:=	libs/misc

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,AVAHI,avahi,$(PKG_VERSION)-$(PKG_RELEASE),$(PKGSS_AVAHI),$(PKG_DESCR),$(PKG_SECTION)))
$(eval $(call PKG_template,LIBAVAHI,libavahi,$(PKG_VERSION)-$(PKG_RELEASE),,$(PKGSD_LIBAVAHI),$(PKGSC_LIBAVAHI),$(PKG_OPTS)))

CONFIGURE_ARGS+=	--enable-glib \
			--enable-libdaemon \
			--enable-dbus \
			--disable-qt3 \
			--disable-qt4 \
			--disable-qt5 \
			--disable-gtk \
			--disable-gtk3 \
			--disable-python \
			--disable-pygtk \
			--disable-python-dbus \
			--disable-mono \
			--disable-monodoc \
			--disable-doxygen-doc \
			--disable-doxygen-dot \
			--disable-doxygen-man \
			--disable-doxygen-rtf \
			--disable-doxygen-xml \
			--disable-doxygen-chm \
			--disable-doxygen-chi \
			--disable-doxygen-html \
			--disable-doxygen-ps \
			--disable-doxygen-pdf \
			--disable-xmltoman \
			--with-distro=none \
			--with-avahi-user=avahi \
			--with-avahi-group=avahi

ifeq ($(ADK_TARGET_USE_SSP),y)
CONFIGURE_ARGS+=	--enable-stack-protector
else
CONFIGURE_ARGS+=	--disable-stack-protector
endif

avahi-install:
	$(INSTALL_DIR) $(IDIR_AVAHI)/etc/dbus-1/system.d
	$(INSTALL_DATA) $(WRKINST)/etc/dbus-1/system.d/avahi-dbus.conf \
		$(IDIR_AVAHI)/etc/dbus-1/system.d
	$(INSTALL_DIR) $(IDIR_AVAHI)/etc/avahi
	$(CP) $(WRKINST)/etc/avahi/avahi-dnsconfd.action \
		$(IDIR_AVAHI)/etc/avahi
	$(INSTALL_DATA) ./files/avahi-daemon.conf \
		$(IDIR_AVAHI)/etc/avahi
	$(INSTALL_DIR) $(IDIR_AVAHI)/etc/avahi/services
	$(INSTALL_DATA) ./files/service-http \
		$(IDIR_AVAHI)/etc/avahi/services/http.service
	$(INSTALL_DATA) ./files/service-ssh \
		$(IDIR_AVAHI)/etc/avahi/services/ssh.service
	$(INSTALL_DIR) $(IDIR_AVAHI)/usr/sbin
	$(INSTALL_DIR) $(IDIR_AVAHI)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/* \
		$(IDIR_AVAHI)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/* \
		$(IDIR_AVAHI)/usr/bin

libavahi-install:
	$(INSTALL_DIR) $(IDIR_LIBAVAHI)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libavahi-common.so* \
		$(IDIR_LIBAVAHI)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libavahi-client.so* \
		$(IDIR_LIBAVAHI)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libavahi-core.so* \
		$(IDIR_LIBAVAHI)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libavahi-glib.so* \
		$(IDIR_LIBAVAHI)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
