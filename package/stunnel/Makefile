# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		stunnel
PKG_VERSION:=		5.79
PKG_RELEASE:=		1
PKG_HASH:=		8ea0de6e5ea76f38ea987fa831c7fd47f7a1f1e7dd465fd6fa8622edf30d3a45
PKG_DESCR:=		proxy designed to add tls encryption functionality to existing clients and servers
PKG_SECTION:=		net/proxy
PKG_DEPENDS:=		libopenssl
PKG_BUILDDEP:=		openssl
PKG_URL:=		https://www.stunnel.org/index.html
PKG_SITES:=		https://www.stunnel.org/downloads/

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,STUNNEL,stunnel,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

CONFIGURE_ARGS+=	--disable-systemd \
			--disable-libwrap \
			--with-ssl="$(STAGING_TARGET_DIR)/usr"
CONFIGURE_ENV+=		ax_cv_check_cflags___fstack_protector_strong=no

stunnel-install:
	$(INSTALL_DIR) $(IDIR_STUNNEL)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/stunnel \
		$(IDIR_STUNNEL)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
