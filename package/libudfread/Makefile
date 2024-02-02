# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libudfread
PKG_VERSION:=		1.1.2
PKG_RELEASE:=		1
PKG_HASH:=		2bf16726ac98d093156195bb049a663e07d3323e079c26912546f4e05c77bac5
PKG_DESCR:=		udf library
PKG_SECTION:=		libs/misc
PKG_SITES:=		http://mirrors.kodi.tv/build-deps/sources/
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBUDFREAD,libudfread,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

AUTOTOOL_STYLE:=	bootstrap

libudfread-install:
	$(INSTALL_DIR) $(IDIR_LIBUDFREAD)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libudfread*.so* \
		$(IDIR_LIBUDFREAD)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
