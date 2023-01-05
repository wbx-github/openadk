# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		glib
PKG_VERSION:=		2.72.3
PKG_RELEASE:=		1
PKG_EXTRAVER:=		2.72
PKG_HASH:=		4a39a2f624b8512d500d5840173eda7fa85f51c109052eae806acece85d345f0
PKG_DESCR:=		low-level core library that forms the basis of gtk+
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		libpcre zlib libffi
PKG_BUILDDEP:=		glib-host util-linux libffi zlib dbus pcre
HOST_BUILDDEP:=		pkgconf-host libiconv-host libffi-host python3-host gettext-host util-linux-host
HOST_BUILDDEP+=		pcre-host meson-host
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

TARGET_CFLAGS+=		-Wno-error=format-nonliteral

HOST_CONFIG_STYLE:=	manual
HOST_STYLE:=		manual
CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

MESON_FLAGS:=		-Dtests=false -Dxattr=false -Doss_fuzz=disabled

host-configure:
	(cd $(HOSTWRKBUILD) && PATH='$(HOST_PATH)' meson setup --prefix $(STAGING_HOST_DIR)/usr _build)

host-build:
	(cd $(HOSTWRKBUILD) && PATH='$(HOST_PATH)' meson compile -C _build)

glib-hostinstall:
	(cd $(HOSTWRKBUILD) && PATH='$(HOST_PATH)' meson install -C _build)

do-configure:
	(cd $(WRKBUILD) && PATH='$(HOST_PATH)' meson setup --prefix /usr \
		--libdir lib --cross-file $(STAGING_HOST_DIR)/etc/meson/cross-compilation.conf -Dtests=false _build)

do-build:
	(cd $(WRKBUILD) && PATH='$(HOST_PATH)' meson compile -C _build)

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
