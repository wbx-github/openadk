# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		xdotool
PKG_VERSION:=		4.20260303.1
PKG_RELEASE:=		1
PKG_HASH:=		c1f971a384da588eb99ca0755fc4300316d49c1e612537e3f1de52215e104fa3
PKG_DESCR:=		tool lets you simulate keyboard input and mouse activity, move and resize windows
PKG_SECTION:=		x11/misc
PKG_DEPENDS:=		libxtst libxinerama libxi
PKG_BUILDDEP:=		libXtst libXinerama libXi
PKG_URL:=		https://www.semicomplete.com/projects/xdotool/
PKG_SITES:=		https://github.com/jordansissel/xdotool/archive/refs/tags/

DISTFILES:=		v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,XDOTOOL,xdotool,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		manual
XAKE_FLAGS+=		PREFIX=/usr

xdotool-install:
	$(INSTALL_DIR) $(IDIR_XDOTOOL)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libxdo.so* \
		$(IDIR_XDOTOOL)/usr/lib
	$(INSTALL_DIR) $(IDIR_XDOTOOL)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/xdotool \
		$(IDIR_XDOTOOL)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
