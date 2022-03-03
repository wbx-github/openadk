# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libgtk3
PKG_VERSION:=		3.24.31
PKG_EXTRAVER:=		3.24
PKG_RELEASE:=		1
PKG_HASH:=		423c3e7fdb4c459ee889e35fd4d71fd2623562541c1041b11c07e5ad1ff10bf9
PKG_DESCR:=		multi-platform toolkit for creating graphical user interfaces
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		glib cairo libxi libepoxy pango at-spi2-core
PKG_DEPENDS+=		at-spi2-atk libxext libxrender libx11
PKG_DEPENDS+=		libxcomposite libxdamage fribidi
PKG_BUILDDEP:=		cairo atk pango libXext renderproto libXrender
PKG_BUILDDEP+=		gdk-pixbuf libXcomposite libXdamage libX11 libXi
PKG_BUILDDEP+=		at-spi2-core at-spi2-atk gdk-pixbuf-host libepoxy
PKG_BUILDDEP+=		fribidi
PKG_NEEDS:=		c++
PKG_URL:=		http://www.gtk.org/
PKG_SITES:=		$(MASTER_SITE_GNOME:=gtk+/$(PKG_EXTRAVER)/)
PKG_LIBNAME:=		libgtk3
PKG_OPTS:=		dev

DISTFILES:=		gtk+-$(PKG_VERSION).tar.xz
WRKDIST=		$(WRKDIR)/gtk+-$(PKG_VERSION)

PKG_CFLINE_LIBGTK3:=	select ADK_PACKAGE_CAIRO_WITH_PDF@
PKG_CFLINE_LIBGTK3+=	select ADK_PACKAGE_CAIRO_WITH_PS@
PKG_CFLINE_LIBGTK3+=	select ADK_PACKAGE_CAIRO_WITH_SVG@

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBGTK3,libgtk3,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

HOST_CFLAGS+=           -I$(STAGING_HOST_DIR)/usr/include/glib-2.0 -I$(STAGING_HOST_DIR)/usr/include/gdk-pixbuf-2.0
HOST_LDFLAGS+=		-lgobject-2.0 -lgmodule-2.0 -pthread -lrt -lglib-2.0 -lgdk_pixbuf-2.0
CONFIGURE_ENV+=		GLIB_COMPILE_RESOURCES=$(STAGING_HOST_DIR)/usr/bin/glib-compile-resources
CONFIGURE_ARGS+=	--disable-gtk-doc-html \
			--disable-gtk-doc \
			--disable-modules \
			--disable-xinerama \
			--disable-cups \
			--disable-papi \
			--enable-introspection=no

libgtk3-install:
	$(INSTALL_DIR) $(IDIR_LIBGTK3)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libgdk-3.so* $(IDIR_LIBGTK3)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libgtk-3.so* $(IDIR_LIBGTK3)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libgailutil-3.so* $(IDIR_LIBGTK3)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
