# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		btop
PKG_VERSION:=		1.4.7
PKG_RELEASE:=		1
PKG_HASH:=		933de2e4d1b2211a638be463eb6e8616891bfba73aef5d38060bd8319baeefc6
PKG_DESCR:=		resource monitor
PKG_SECTION:=		sys/utils
PKG_BUILDDEP:=		cmake-host
PKG_NEEDS:=		c++
PKG_URL:=		https://github.com/aristocratos/btop/
PKG_SITES:=		https://github.com/aristocratos/btop/archive/refs/tags/

DISTFILES:=             v$(PKG_VERSION).tar.gz
WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,BTOP,btop,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

TARGET_CFLAGS+=		-D_GNU_SOURCE

CONFIG_STYLE:=		cmake
CMAKE_FLAGS+=		-DBTOP_LTO=OFF \
			-DBUILD_TESTING=OFF

btop-install:
	$(INSTALL_DIR) $(IDIR_BTOP)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/btop \
		$(IDIR_BTOP)/usr/bin
	$(INSTALL_DIR) $(IDIR_BTOP)/usr/share/btop
	$(CP) $(WRKINST)/usr/share/btop/themes \
		$(IDIR_BTOP)/usr/share/btop

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
