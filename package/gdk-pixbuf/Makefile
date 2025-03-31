# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		gdk-pixbuf
PKG_VERSION:=		2.42.12
PKG_EXTRAVER:=		2.42
PKG_RELEASE:=		1
PKG_HASH:=		b9505b3445b9a7e48ced34760c3bcb73e966df3ac94c95a148cb669ab748e3c7
PKG_DESCR:=		image loading and pixel buffer manipulation library
PKG_SECTION:=		libs/image
PKG_BUILDDEP:=		libjpeg-turbo libtiff glib libpng gdk-pixbuf-host
HOST_BUILDDEP:=		glib-host libffi-host libpng-host libjpeg-turbo-host
PKG_NEEDS:=		c++
PKG_SITES:=		$(MASTER_SITE_GNOME:=gdk-pixbuf/$(PKG_EXTRAVER)/)
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,GDK_PIXBUF,gdk-pixbuf,$(PKG_VERSION)-$(PKG_RELEASE)))
$(eval $(call PKG_template,GDK_PIXBUF,gdk-pixbuf,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

HOST_LDFLAGS+=		-lpng -ljpeg
HOST_STYLE:=		meson
HOST_INSTALL_STYLE:=	meson

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

HOST_MESON_FLAGS:=	-Dgio_sniffing=false \
			-Dtests=false \
			-Dinstalled_tests=false \
			-Dintrospection=disabled \
			-Dman=false \
			--default-library=static
MESON_FLAGS:=		-Dgio_sniffing=false \
			-Dtests=false \
			-Dinstalled_tests=false \
			-Dman=false

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
