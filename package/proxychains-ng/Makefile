# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		proxychains-ng
PKG_VERSION:=		4.17
PKG_RELEASE:=		1
PKG_HASH:=		1a2dc68fcbcb2546a07a915343c1ffc75845f5d9cc3ea5eb3bf0b62a66c0196f
PKG_DESCR:=		socks proxy
PKG_SECTION:=		net/proxy
PKG_SITES:=		https://github.com/rofl0r/proxychains-ng/archive/refs/tags/

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,PROXYCHAINS_NG,proxychains-ng,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

proxychains-ng-install:
	$(INSTALL_DIR) $(IDIR_PROXYCHAINS_NG)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/proxychains4* \
		$(IDIR_PROXYCHAINS_NG)/usr/bin
	$(INSTALL_DIR) $(IDIR_PROXYCHAINS_NG)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libproxychains4.so \
		$(IDIR_PROXYCHAINS_NG)/usr/lib
	$(INSTALL_DIR) $(IDIR_PROXYCHAINS_NG)/etc
	$(CP) $(WRKBUILD)/src/proxychains.conf \
		$(IDIR_PROXYCHAINS_NG)/etc


include $(ADK_TOPDIR)/mk/pkg-bottom.mk
