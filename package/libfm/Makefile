# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libfm
PKG_VERSION:=		1.4.1
PKG_RELEASE:=		1
PKG_HASH:=		5caa820443d558974648583e37b4d956ae67a6e3df23493f99c2d0e26a11c665
PKG_DESCR:=		library needed for pcmanfm
PKG_SECTION:=		x11/lxde
PKG_DEPENDS:=		llibgtk3 pango menu-cache dbus-glib
PKG_BUILDDEP:=		vala-host intltool-host libgtk3 pango menu-cache dbus-glib
PKG_URL:=		https://lxde.org/
PKG_SITES:=		https://github.com/lxde/releases/raw/refs/heads/master/releases/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBFM,libfm,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIGURE_ARGS+=	--with-gtk=3 \
			--enable-udisks

libfm-install:
	$(INSTALL_DIR) $(IDIR_LIBFM)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libfm*.so* \
		$(IDIR_LIBFM)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
