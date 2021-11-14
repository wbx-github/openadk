# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		xf86-input-mouse
PKG_VERSION:=		1.9.3
PKG_RELEASE:=		1
PKG_HASH:=		71f3aa0a18dfe1ca5cb235ec9210f33571cf5fbbd90ac5b55306a954f67aa5c6
PKG_DESCR:=		x11 driver for mouse
PKG_SECTION:=		x11/drivers
PKG_DEPENDS:=		xorg-server
PKG_BUILDDEP:=		xorg-server
PKG_NEEDS:=		c++
PKG_SITES:=		http://www.x.org/releases/individual/driver/

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

PKG_CFLINE_XF86_INPUT_MOUSE:=	depends on ADK_TARGET_WITH_INPUT || ADK_TARGET_QEMU_WITH_GRAPHIC

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,XF86_INPUT_MOUSE,xf86-input-mouse,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

xf86-input-mouse-install:
	$(INSTALL_DIR) $(IDIR_XF86_INPUT_MOUSE)/usr/lib/xorg/modules/input
	$(CP) $(WRKINST)/usr/lib/xorg/modules/input/mouse_drv.so \
		$(IDIR_XF86_INPUT_MOUSE)/usr/lib/xorg/modules/input/

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
