# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		xinit
PKG_VERSION:=		1.4.4
PKG_RELEASE:=		1
PKG_HASH:=		45cca1b0f3a963105f43cecc24e9cc4db0d14faa87bd9860b9ec563e8c73fc47
PKG_DESCR:=		x window system initializer
PKG_SECTION:=		x11/utils
PKG_DEPENDS:=		xorg-server mcookie xauth xset
PKG_BUILDDEP:=		xorg-server
PKG_NEEDS:=		c++
PKG_URL:=		http://xorg.freedesktop.org/
PKG_SITES:=		http://xorg.freedesktop.org/archive/individual/app/

PKG_CFLINE_XINIT:=	select BUSYBOX_HEXDUMP

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,XINIT,xinit,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

TARGET_CPPFLAGS+=	-D_POSIX_SOURCE
CONFIGURE_ARGS:=	--without-launchd
XAKE_FLAGS+=		RAWCPP="$(TARGET_CROSS)cpp"

xinit-install:
	$(INSTALL_DIR) $(IDIR_XINIT)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/startx \
		$(IDIR_XINIT)/usr/bin/
	$(INSTALL_BIN) $(WRKINST)/usr/bin/xinit \
		$(IDIR_XINIT)/usr/bin/
	$(INSTALL_DIR) $(IDIR_XINIT)/etc/X11/xinit
	$(INSTALL_DATA) $(WRKINST)/etc/X11/xinit/xinitrc \
		$(IDIR_XINIT)/etc/X11/xinit/

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
