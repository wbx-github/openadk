# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		sofia-sip
PKG_VERSION:=		1.13.17
PKG_RELEASE:=		1
PKG_HASH:=		daca3d961b6aa2974ad5d3be69ed011726c3e4d511b2a0d4cb6d878821a2de7a
PKG_DESCR:=		sip library
PKG_SECTION:=		libs/misc
PKG_SITES:=		https://github.com/freeswitch/sofia-sip/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,SOFIA_SIP,sofia-sip,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

AUTOTOOL_STYLE:=	bootstrap

sofia-sip-install:
	$(INSTALL_DIR) $(IDIR_SOFIA_SIP)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libsofia-sip*.so* \
		$(IDIR_SOFIA_SIP)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
