# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		radvd
PKG_VERSION:=		2.21
PKG_RELEASE:=		1
PKG_HASH:=		91df2ed7faca0716bbd726a17d6467ed92fcb2b6e45b57d9e619f9686ab99e1b
PKG_DESCR:=		routing advertisement daemon for ipv6
PKG_SECTION:=		net/ipv6
PKG_DEPENDS:=		libdaemon
PKG_KDEPENDS:=		ipv6
PKG_BUILDDEP:=		libdaemon check
PKG_URL:=		http://www.litech.org/radvd/
PKG_SITES:=		https://github.com/radvd-project/radvd/releases/download/v$(PKG_VERSION)/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,RADVD,radvd,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIGURE_ARGS+=	--with-configfile=/etc/radvd.conf \
			--with-logfile=/var/log/radvd.log \
			--with-pidfile=/var/run/radvd.pid \
			--without-stack-protector

radvd-install:
	$(INSTALL_DIR) $(IDIR_RADVD)/etc $(IDIR_RADVD)/usr/sbin
	$(INSTALL_DATA) ./files/radvd.conf $(IDIR_RADVD)/etc/
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/radvd $(IDIR_RADVD)/usr/sbin/
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/radvdump $(IDIR_RADVD)/usr/sbin/

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
