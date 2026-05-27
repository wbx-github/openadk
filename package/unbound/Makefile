# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		unbound
PKG_VERSION:=		1.25.1
PKG_RELEASE:=		1
PKG_HASH:=		0fe8b6277b0959cfd17562debac0aa5f71e0b02dc4ffa9c60271c583edab586f
PKG_DESCR:=		a validating, recursive, caching DNS resolver
PKG_SECTION:=		net/dns
PKG_BUILDDEP:=		openssl
PKG_DEPENDS:=		libopenssl
PKG_URL:=		https://www.nlnetlabs.nl/projects/unbound/
PKG_SITES:=		https://www.nlnetlabs.nl/downloads/unbound/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,UNBOUND,unbound,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

unbound-install:
	$(INSTALL_DIR) $(IDIR_UNBOUND)/etc/unbound
	$(CP) $(WRKINST)/etc/unbound/unbound.conf \
		$(IDIR_UNBOUND)/etc/unbound
	$(INSTALL_DIR) $(IDIR_UNBOUND)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libunbound.so.* \
		$(IDIR_UNBOUND)/usr/lib
	$(INSTALL_DIR) $(IDIR_UNBOUND)/usr/sbin
	$(CP) $(WRKINST)/usr/sbin/unbound* \
		$(IDIR_UNBOUND)/usr/sbin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
