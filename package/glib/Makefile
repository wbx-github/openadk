# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		glib
PKG_VERSION:=		2.78.4
PKG_RELEASE:=		1
PKG_EXTRAVER:=		2.78
PKG_HASH:=		24b8e0672dca120cc32d394bccb85844e732e04fe75d18bb0573b2dbc7548f63
PKG_DESCR:=		low-level core library that forms the basis of gtk+
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		pcre2 zlib libffi libiconv
PKG_BUILDDEP:=		glib-host util-linux libffi zlib dbus pcre2 libiconv
HOST_BUILDDEP:=		pkgconf-host libiconv-host libffi-host python3-host gettext-host util-linux-host
HOST_BUILDDEP+=		pcre2-host meson-host zlib-host
PKG_NEEDS:=		threads intl iconv
PKG_URL:=		http://www.gtk.org/
PKG_SITES:=		http://ftp.gnome.org/pub/GNOME/sources/glib/$(PKG_EXTRAVER)/
PKG_OPTS:=		dev noscripts

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,GLIB,glib,$(PKG_VERSION)-$(PKG_RELEASE)))
$(eval $(call PKG_template,GLIB,glib,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

HOSTWRKBUILD=           $(WRKSRC)
WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

HOST_STYLE:=		meson
HOST_INSTALL_STYLE:=	meson

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

HOST_MESON_FLAGS:=	--default-library static -Dtests=false -Dxattr=false -Doss_fuzz=disabled
MESON_FLAGS:=		-Dtests=false -Dxattr=false -Doss_fuzz=disabled

hostpost-install:
	$(CP) $(HOSTWRKBUILD)/../glib-obj/meson-private/glib-2.0.pc \
		$(STAGING_HOST_DIR)/usr/lib/pkgconfig
	$(INSTALL_BIN) $(HOSTWRKBUILD)/../glib-obj/gobject/glib-mkenums \
		$(STAGING_HOST_DIR)/usr/bin
	$(INSTALL_BIN) $(HOSTWRKBUILD)/../glib-obj/gobject/glib-genmarshal \
		$(STAGING_HOST_DIR)/usr/bin

glib-install:
	$(INSTALL_DIR) $(IDIR_GLIB)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libgio*.so* $(IDIR_GLIB)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libglib*.so* $(IDIR_GLIB)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libgobject*.so* $(IDIR_GLIB)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libgmodule*.so* $(IDIR_GLIB)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libgthread*.so* $(IDIR_GLIB)/usr/lib
	# workaround for dev subpackage
	$(INSTALL_DIR) $(IDIR_GLIB_DEV)/usr/include
	$(INSTALL_DIR) $(IDIR_GLIB_DEV)/usr/lib/glib-2.0/include
	$(CP) $(WRKINST)/usr/lib/glib-2.0/include/glibconfig.h \
		$(IDIR_GLIB_DEV)/usr/lib/glib-2.0/include
	$(INSTALL_DIR) $(IDIR_GLIB_DEV)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/glib-genmarshal \
		$(IDIR_GLIB_DEV)/usr/bin

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
