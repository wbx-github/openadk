# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libinih
PKG_VERSION:=		r58
PKG_RELEASE:=		1
PKG_HASH:=		e79216260d5dffe809bda840be48ab0eec7737b2bb9f02d2275c1b46344ea7b7
PKG_DESCR:=		ini parser library
PKG_SECTION:=		libs/misc
PKG_BUILDDEP:=		meson-host
PKG_URL:=		https://github.com/benhoyt/inih
PKG_SITES:=		https://github.com/benhoyt/inih/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_VERSION).tar.gz

WRKDIST=		${WRKDIR}/inih-${PKG_VERSION}

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBINIH,libinih,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

libinih-install:
	$(INSTALL_DIR) $(IDIR_LIBINIH)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libinih*.so* \
		$(IDIR_LIBINIH)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
