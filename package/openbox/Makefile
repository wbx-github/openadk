# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		openbox
PKG_VERSION:=		3.6.1
PKG_RELEASE:=		1
PKG_HASH:=		abe75855cc5616554ffd47134ad15291fe37ebbebf1a80b69cbde9d670f0e26d
PKG_DESCR:=		small windowmanager
PKG_SECTION:=		x11/lxde
PKG_URL:=		https://openbox.org/
PKG_SITES:=		https://openbox.org/dist/openbox/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,OPENBOX,openbox,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

openbox-install:
	$(INSTALL_DIR) $(IDIR_OPENBOX)/etc/xdg
	$(CP) $(WRKINST)/etc/xdg/* $(IDIR_OPENBOX)/etc/xdg
	$(INSTALL_DIR) $(IDIR_OPENBOX)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/openbox \
		$(IDIR_OPENBOX)/usr/bin
	$(INSTALL_DIR) $(IDIR_OPENBOX)/usr/lib
	$(CP) $(WRKINST)/usr/lib/*.so* \
		$(IDIR_OPENBOX)/usr/lib
	$(INSTALL_DIR) $(IDIR_OPENBOX)/usr/libexec
	$(CP) $(WRKINST)/usr/libexec/* \
		$(IDIR_OPENBOX)/usr/libexec
	$(INSTALL_DIR) $(IDIR_OPENBOX)/usr/share
	$(CP) $(WRKINST)/usr/share/* \
		$(IDIR_OPENBOX)/usr/share
	rm $(IDIR_OPENBOX)/usr/share/xsessions/*

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
