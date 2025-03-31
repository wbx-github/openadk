# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include ${ADK_TOPDIR}/rules.mk

PKG_NAME:=		libgtk2
PKG_VERSION:=		2.24.33
PKG_EXTRAVER:=		2.24
PKG_RELEASE:=		1
PKG_HASH:=		ac2ac757f5942d318a311a54b0c80b5ef295f299c2a73c632f6bfb1ff49cc6da
PKG_DESCR:=		multi-platform toolkit for creating graphical user interfaces
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		glib cairo
PKG_BUILDDEP:=		glib cairo pango libXext renderproto libXrender
PKG_BUILDDEP+=		gdk-pixbuf libXcomposite libXdamage libX11
PKG_NEEDS:=		c++
PKG_URL:=		http://www.gtk.org/
PKG_SITES:=		http://ftp.gnome.org/pub/gnome/sources/gtk+/$(PKG_EXTRAVER)/
PKG_LIBNAME:=		libgtk2
PKG_OPTS:=		dev

DISTFILES:=		gtk+-$(PKG_VERSION).tar.xz
WRKDIST=		$(WRKDIR)/gtk+-$(PKG_VERSION)

PKG_CFLINE_LIBGTK2:=	select ADK_PACKAGE_CAIRO_WITH_PDF@
PKG_CFLINE_LIBGTK2+=	select ADK_PACKAGE_CAIRO_WITH_PS@
PKG_CFLINE_LIBGTK2+=	select ADK_PACKAGE_CAIRO_WITH_SVG@

include ${ADK_TOPDIR}/mk/package.mk

$(eval $(call PKG_template,LIBGTK2,libgtk2,${PKG_VERSION}-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

TARGET_LDFLAGS+=	-lm
CONFIGURE_ARGS+=	--disable-gtk-doc-html \
			--disable-modules \
			--disable-xinerama \
			--without-xinput \
			--disable-gtk-doc \
			--disable-cups \
			--disable-papi \
			--disable-introspection
CONFIGURE_ENV+=		gio_can_sniff=no \
			ac_cv_path_GTK_UPDATE_ICON_CACHE=""

libgtk2-install:
	${INSTALL_DIR} ${IDIR_LIBGTK2}/usr/lib
	${CP} ${WRKINST}/usr/lib/libgdk-x11*so* ${IDIR_LIBGTK2}/usr/lib
	${CP} ${WRKINST}/usr/lib/libgtk-x11*so* ${IDIR_LIBGTK2}/usr/lib
	${CP} ${WRKINST}/usr/lib/libgailutil*so* ${IDIR_LIBGTK2}/usr/lib
	# workaround dev subpackage
	${INSTALL_DIR} ${IDIR_LIBGTK2_DEV}/usr/lib/gtk-2.0/include
	${CP} ${WRKINST}/usr/lib/gtk-2.0/include/* \
		${IDIR_LIBGTK2_DEV}/usr/lib/gtk-2.0/include

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
