# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libptytty
PKG_VERSION:=		2.0
PKG_RELEASE:=		1
PKG_HASH:=		8033ed3aadf28759660d4f11f2d7b030acf2a6890cb0f7926fb0cfa6739d31f7
PKG_DESCR:=		pty library
PKG_SECTION:=		libs/misc
PKG_SITES:=		http://dist.schmorp.de/libptytty/
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBPTYTTY,libptytty,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIG_STYLE:=		cmake
CMAKE_FLAGS+=		-DTTY_GID_SUPPORT_EXITCODE=0 \
			-DTTY_GID_SUPPORT_EXITCODE__TRYRUN_OUTPUT=0

libptytty-install:
	$(INSTALL_DIR) $(IDIR_LIBPTYTTY)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libptytty*.so* \
		$(IDIR_LIBPTYTTY)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
