# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		xorgproto
PKG_VERSION:=		2021.5
PKG_RELEASE:=		1
PKG_DESCR:=		xorg extension headers
PKG_SECTION:=		dev/header
PKG_HASH:=		be6ddd6590881452fdfa170c1c9ff87209a98d36155332cbf2ccbc431add86ff
PKG_SITES:=		http://www.x.org/releases/individual/proto/
PKG_OPTS:=              dev devonly

DISTFILES:=		$(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,XORGPROTO,xorgproto,$(PKG_VERSION)-$(PKG_RELEASE)))
$(eval $(call PKG_template,XORGPROTO,xorgproto,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

HOST_STYLE:=		auto

post-install:
	$(CP) ${WRKINST}/usr/share/pkgconfig/*.pc \
		${STAGING_TARGET_DIR}/usr/lib/pkgconfig/

include $(ADK_TOPDIR)/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
