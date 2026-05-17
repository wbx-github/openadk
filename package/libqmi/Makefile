# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libqmi
PKG_VERSION:=		1.30.8
PKG_RELEASE:=		1
PKG_HASH:=		862482ce9e3ad0bd65d264334ee311cdb94b9df2863b5b7136309b41b8ac1990
PKG_DESCR:=		qmi modem protocol helper library
PKG_SECTION:=		libs/net
PKG_DEPENDS:=		glib
PKG_BUILDDEP:=		glib
PKG_SITES:=		https://www.freedesktop.org/software/libqmi/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBQMI,libqmi,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIGURE_ARGS+=	--without-udev

libqmi-install:
	$(INSTALL_DIR) $(IDIR_LIBQMI)/usr/{bin,lib}
	$(INSTALL_BIN) $(WRKINST)/usr/bin/qmi{-network,cli} \
		$(IDIR_LIBQMI)/usr/bin
	$(CP) $(WRKINST)/usr/lib/libqmi-glib.so* $(IDIR_LIBQMI)/usr/lib/

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
