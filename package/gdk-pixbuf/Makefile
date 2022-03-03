# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		gdk-pixbuf
PKG_VERSION:=		2.34.0
PKG_EXTRAVER:=		2.34
PKG_RELEASE:=		1
PKG_HASH:=		d55e5b383ee219bd0e23bf6ed4427d56a7db5379729a6e3e0a0e0eba9a8d8879
PKG_DESCR:=		image loading and pixel buffer manipulation library
PKG_SECTION:=		libs/image
PKG_BUILDDEP:=		libjpeg-turbo libtiff glib libpng
HOST_BUILDDEP:=		libiconv-host glib-host libffi-host
PKG_NEEDS:=		c++
PKG_SITES:=		$(MASTER_SITE_GNOME:=gdk-pixbuf/$(PKG_EXTRAVER)/)
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,GDK_PIXBUF,gdk-pixbuf,$(PKG_VERSION)-$(PKG_RELEASE)))
$(eval $(call PKG_template,GDK_PIXBUF,gdk-pixbuf,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

HOST_STYLE:=		auto
HOST_LDFLAGS+=		-lffi -lz -ldl -lresolv -liconv -lmount
HOST_CONFIGURE_ARGS+=	--disable-glibtest \
			--without-libjpeg \
			--without-libpng \
			--without-libtiff
CONFIGURE_ENV+=		gio_can_sniff=no

gdk-pixbuf-install:
	$(INSTALL_DIR) $(IDIR_GDK_PIXBUF)/usr/lib/gdk-pixbuf-2.0/2.10.0/loaders/
	$(CP) $(WRKINST)/usr/lib/libgdk_pixbuf*so* \
		$(IDIR_GDK_PIXBUF)/usr/lib
	$(CP) $(WRKINST)/usr/lib/gdk-pixbuf-2.0/2.10.0/loaders/libpixbufloader-*.so \
		$(IDIR_GDK_PIXBUF)/usr/lib/gdk-pixbuf-2.0/2.10.0/loaders/
	$(CP) ./files/loaders.cache \
		 $(IDIR_GDK_PIXBUF)/usr/lib/gdk-pixbuf-2.0/2.10.0/loaders.cache

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
