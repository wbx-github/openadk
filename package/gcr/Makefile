# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		gcr
PKG_VERSION:=		3.20.0
PKG_EXTRAVER:=		3.20
PKG_RELEASE:=		2
PKG_HASH:=		90572c626d8a708225560c42b4421f7941315247fa1679d4ef569bde7f4bb379
PKG_DESCR:=		gnome keyring library
PKG_SECTION:=		libs/crypto
PKG_BUILDDEP:=		p11-kit intltool-host libgtk3
PKG_URL:=		https://wiki.gnome.org/action/show/Projects/GnomeKeyring
PKG_SITES:=		http://ftp.acc.umu.se/pub/gnome/sources/gcr/$(PKG_EXTRAVER)/

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,GCR,gcr,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

gcr-install:
	$(INSTALL_DIR) $(IDIR_GCR)/usr/lib
	$(CP) $(WRKINST)/usr/lib/lib*.so* \
		$(IDIR_GCR)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
