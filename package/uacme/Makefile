# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		uacme
PKG_VERSION:=		1.7.4
PKG_RELEASE:=		1
PKG_HASH:=		0fd3e35218d575321e70dc3489ec3463d015c56c138e99e5add32ab7e5a48d09
PKG_DESCR:=		acme client written in c
PKG_BUILDDEP:=		curl gnutls
PKG_DEPENDS:=		libcurl libgnutls
PKG_SECTION:=		app/crypto
PKG_SITES:=		https://github.com/ndilieto/uacme/archive/refs/tags/

DISTFILES:=		v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,UACME,uacme,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION)))

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ARGS+=	--disable-docs

uacme-install:
	$(INSTALL_DIR) $(IDIR_UACME)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/uacme \
		$(IDIR_UACME)/usr/bin

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
