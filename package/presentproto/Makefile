# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		presentproto
PKG_VERSION:=		1.1
PKG_RELEASE:=		1
PKG_HASH:=		114252e97afb4dfae8b31e6b0d5e24e4babda26b364e2be57abc2f3c30248b87
PKG_DESCR:=		present protocol headers
PKG_SECTION:=		dev/header
PKG_SITES:=		http://www.x.org/releases/individual/proto/
PKG_OPTS:=              dev devonly

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,PRESENTPROTO,presentproto,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
