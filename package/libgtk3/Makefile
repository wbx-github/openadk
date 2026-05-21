# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libgtk3
PKG_VERSION:=		3.24.52
PKG_EXTRAVER:=		3.24
PKG_RELEASE:=		1
PKG_HASH:=		80931fa472a77b9a164f6740e3c0b444fac6770054632d35a7ff9d679e5e7b9f
PKG_DESCR:=		multi-platform toolkit for creating graphical user interfaces
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		glib cairo libxi libepoxy pango at-spi2-core
PKG_DEPENDS+=		libxext libxrender libx11
PKG_DEPENDS+=		libxcomposite libxdamage fribidi libxkbcommon
PKG_BUILDDEP:=		cairo pango libXext renderproto libXrender
PKG_BUILDDEP+=		gdk-pixbuf libXcomposite libXdamage libX11 libXi
PKG_BUILDDEP+=		at-spi2-core gdk-pixbuf-host libepoxy
PKG_BUILDDEP+=		fribidi libxkbcommon
PKG_NEEDS:=		c++
PKG_URL:=		http://www.gtk.org/
PKG_SITES:=		https://download.gnome.org/sources/gtk/$(PKG_EXTRAVER)/
PKG_LIBNAME:=		libgtk3
PKG_OPTS:=		dev

DISTFILES:=		gtk-$(PKG_VERSION).tar.xz
WRKDIST=		$(WRKDIR)/gtk-$(PKG_VERSION)

PKG_CFLINE_LIBGTK3:=	select ADK_PACKAGE_CAIRO_WITH_PDF@
PKG_CFLINE_LIBGTK3+=	select ADK_PACKAGE_CAIRO_WITH_PS@
PKG_CFLINE_LIBGTK3+=	select ADK_PACKAGE_CAIRO_WITH_SVG@

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBGTK3,libgtk3,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

MESON_FLAGS+=		-Dwayland_backend=false \
			-Dintrospection=false

libgtk3-install:
	$(INSTALL_DIR) $(IDIR_LIBGTK3)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libgdk-3.so* $(IDIR_LIBGTK3)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libgtk-3.so* $(IDIR_LIBGTK3)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libgailutil-3.so* $(IDIR_LIBGTK3)/usr/lib
	$(INSTALL_DIR) $(IDIR_LIBGTK3)/usr/share/themes/Adwaita/gtk-3.0
	$(CP) $(WRKSRC)/gtk/theme/Adwaita/* \
		$(IDIR_LIBGTK3)/usr/share/themes/Adwaita/gtk-3.0

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
