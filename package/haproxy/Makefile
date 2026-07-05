# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		haproxy
PKG_VERSION:=		3.4.2
PKG_RELEASE:=		1
PKG_HASH:=		b1330dbb0d6e6bc4a72c4708a6a9e585579cd1156dfe5763c26305105bc12907
PKG_DESCR:=		the reliable, high performance tcp/http load balancer
PKG_SECTION:=		net/proxy
PKG_BUILDDEP:=		pcre2 openssl
PKG_DEPENDS:=		pcre2 libopenssl
PKG_URL:=		https://www.haproxy.org/
PKG_SITES:=		https://www.haproxy.org/download/3.4/src/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,HAPROXY,haproxy,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIG_STYLE:=		manual
XAKE_FLAGS:=		PREFIX=/usr V=1 \
			LD=$(TARGET_CC) \
			CC=$(TARGET_CC) \
			TARGET=custom \
			USE_OPENSSL=1 \
			USE_PCRE2=1

haproxy-install:
	$(INSTALL_DIR) $(IDIR_HAPROXY)/usr/sbin
	$(INSTALL_BIN) $(WRKINST)/usr/sbin/haproxy \
		$(IDIR_HAPROXY)/usr/sbin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
