# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		connman
PKG_VERSION:=		2.0
PKG_RELEASE:=		1
PKG_HASH:=		d25c2ddc0b5ad13e986ec35ad765ae8d2f4b7acb47c958a05616c943cd082527
PKG_DESCR:=		connection manager
PKG_SECTION:=		net/misc
PKG_DEPENDS:=		libncurses libreadline glib dbus iptables libmount
PKG_BUILDDEP:=		ncurses readline glib dbus iptables util-linux
PKG_SITES:=		https://www.kernel.org/pub/linux/network/connman/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,CONNMAN,connman,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

TARGET_LDFLAGS+=	-lncursesw
CONFIGURE_ARGS+=	--with-firewall=iptables \
			--with-dbusconfdir=/etc \
			--disable-wispr

connman-install:
	$(INSTALL_DIR) $(IDIR_CONNMAN)/etc/dbus-1/system.d
	$(CP) $(WRKINST)/etc/dbus-1/system.d/connman.conf \
		$(IDIR_CONNMAN)/etc/dbus-1/system.d
	$(INSTALL_DIR) $(IDIR_CONNMAN)/usr/sbin
	$(CP) $(WRKINST)/usr/sbin/connmand* \
		$(IDIR_CONNMAN)/usr/sbin
	$(INSTALL_DIR) $(IDIR_CONNMAN)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/connmanctl \
		$(IDIR_CONNMAN)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
