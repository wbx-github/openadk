# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		transmission
PKG_VERSION:=		4.0.5
PKG_RELEASE:=		1
PKG_HASH:=		fd68ff114a479200043c30c7e69dba4c1932f7af36ca4c5b5d2edcb5866e6357
PKG_DESCR:=		torrent client
PKG_SECTION:=		app/p2p
PKG_DEPENDS:=		libressl libevent libcurl
PKG_BUILDDEP:=		cmake-host libressl libevent curl
PKG_NEEDS:=		threads c++
PKG_URL:=		http://www.transmissionbt.com
PKG_SITES:=		https://github.com/transmission/transmission/releases/download/$(PKG_VERSION)/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,TRANSMISSION,transmission,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		cmake

transmission-install:
	$(INSTALL_DIR) $(IDIR_TRANSMISSION)/usr/share
	$(CP) $(WRKINST)/usr/share/transmission \
		$(IDIR_TRANSMISSION)/usr/share
	$(INSTALL_DIR) $(IDIR_TRANSMISSION)/usr/bin
	$(CP) $(WRKINST)/usr/bin/transmission* \
		$(IDIR_TRANSMISSION)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
