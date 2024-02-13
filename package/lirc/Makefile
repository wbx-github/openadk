# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		lirc
PKG_VERSION:=		0.10.2
PKG_RELEASE:=		1
PKG_HASH:=		3d44ec8274881cf262f160805641f0827ffcc20ade0d85e7e6f3b90e0d3d222a
PKG_DESCR:=		decode and send infra-red signals
PKG_SECTION:=		sys/hw
PKG_BUILDDEP:=		libxml2-host libxslt-host
PKG_URL:=		http://www.lirc.org/
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=lirc/}

DISTFILES:=             ${PKG_NAME}-${PKG_VERSION}.tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIRC,lirc,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ARGS+=	--with-driver=none

lirc-install:
	$(INSTALL_DIR) $(IDIR_LIRC)/etc/lirc
	$(CP) $(WRKINST)/etc/lirc/* $(IDIR_LIRC)/etc/lirc
	$(INSTALL_DIR) $(IDIR_LIRC)/usr/lib
	$(CP) $(WRKINST)/usr/lib/liblirc*.so* \
		$(IDIR_LIRC)/usr/lib
	$(INSTALL_DIR) $(IDIR_LIRC)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/lircd \
		$(IDIR_LIRC)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/lircmd \
		$(IDIR_LIRC)/usr/sbin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
