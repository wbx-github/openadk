# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		polkit
PKG_VERSION:=		127
PKG_RELEASE:=		1
PKG_HASH:=		9b7bc16f086479dcc626c575976568ba4a85d34297a750d8ab3d2e57f6d8b988
PKG_DESCR:=		policy kit daemon
PKG_DEPENDS:=		duktape consolekit2 libcap dbus pam
PKG_BUILDDEP:=		duktape consolekit2 libcap pam
PKG_SECTION:=		x11/apps
PKG_SITES:=		https://github.com/polkit-org/polkit/archive/refs/tags/

DISTFILES:=             $(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,POLKIT,polkit,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

MESON_FLAGS:=		-Dsession_tracking=ConsoleKit \
			-Dauthfw=pam \
			-Dintrospection=false

polkit-install:
	$(INSTALL_DIR) $(IDIR_POLKIT)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libpolkit*.so* \
		$(IDIR_POLKIT)/usr/lib
	$(INSTALL_DIR) $(IDIR_POLKIT)/usr/lib/polkit-1
	$(CP) $(WRKINST)/usr/lib/polkit-1/* \
		$(IDIR_POLKIT)/usr/lib/polkit-1
	$(INSTALL_DIR) $(IDIR_POLKIT)/usr/share/polkit-1
	$(CP) $(WRKINST)/usr/share/polkit-1/* \
		$(IDIR_POLKIT)/usr/share/polkit-1
	$(INSTALL_DIR) $(IDIR_POLKIT)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/pk* \
		$(IDIR_POLKIT)/usr/bin
	$(INSTALL_DIR) $(IDIR_POLKIT)/usr/share/dbus-1
	$(CP) $(WRKINST)/usr/share/dbus-1/* \
		$(IDIR_POLKIT)/usr/share/dbus-1

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
