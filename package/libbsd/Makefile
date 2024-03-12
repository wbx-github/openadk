# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libbsd
PKG_VERSION:=		0.11.7
PKG_RELEASE:=		1
PKG_HASH:=		9baa186059ebbf25c06308e9f991fda31f7183c0f24931826d83aa6abd8a0261
PKG_DESCR:=		bsd helper functions
PKG_SECTION:=		libs/misc
PKG_BUILDDEP:=		libmd
PKG_DEPENDS:=		libmd
PKG_URL:=		https://libbsd.freedesktop.org/
PKG_SITES:=		https://libbsd.freedesktop.org/releases/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBBSD,libbsd,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

libbsd-install:
	$(INSTALL_DIR) $(IDIR_LIBBSD)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libbsd*.so* \
		$(IDIR_LIBBSD)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
