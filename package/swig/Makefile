# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		swig
PKG_VERSION:=		4.4.1
PKG_RELEASE:=		1
PKG_HASH:=		40162a706c56f7592d08fd52ef5511cb7ac191f3593cf07306a0a554c6281fcf
PKG_DESCR:=		swig utility
PKG_SECTION:=		dev/tools
PKG_URL:=		http://www.swig.org/
PKG_SITES:=		https://sourceforge.net/projects/swig/files/swig/$(PKG_NAME)-$(PKG_VERSION)/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_CFLINE_SWIG:=	depends on ADK_HOST_ONLY

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,SWIG,swig,$(PKG_VERSION)-${PKG_RELEASE}))

HOST_ALL_TARGET:=	swig
HOST_CONFIGURE_ARGS+=	--without-pcre

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
