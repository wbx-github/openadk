# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		htpdate
PKG_VERSION:=		2.0.2
PKG_RELEASE:=		1
PKG_HASH:=		3f5effa9355db140ef8ace6d17800d48815d1afdcef9d1096510451839dd8de4
PKG_DESCR:=		hypertext time protocol implementation
PKG_SECTION:=		net/ntp
PKG_BUILDDEP:=		openssl
PKG_DEPENDS:=		libopenssl
PKG_URL:=		http://www.vervest.org/htp/
PKG_SITES:=		https://github.com/twekkel/htpdate/archive/refs/tags/

DISTFILES:=		v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,HTPDATE,htpdate,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

ALL_TARGET:=		https
CONFIG_STYLE:=		manual

htpdate-install:
	$(INSTALL_DIR) $(IDIR_HTPDATE)/usr/sbin
	$(INSTALL_BIN) $(WRKBUILD)/htpdate $(IDIR_HTPDATE)/usr/sbin/

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
