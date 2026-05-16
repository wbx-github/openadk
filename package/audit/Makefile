# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		audit
PKG_VERSION:=		4.0.2
PKG_RELEASE:=		1
PKG_HASH:=		d5d1b5d50ee4a2d0d17875bc6ae6bd6a7d5b34d9557ea847a39faec531faaa0a
PKG_DESCR:=		audit library
PKG_SECTION:=		libs/misc
PKG_URL:=		https://people.redhat.com/sgrubb/audit
PKG_SITES:=		https://people.redhat.com/sgrubb/audit/
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,AUDIT,audit,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIGURE_ARGS+=	--without-python \
			--without-python3 \
			--without-libcap-ng \
			--disable-zos-remote

audit-install:
	$(INSTALL_DIR) $(IDIR_AUDIT)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libaudit*.so* \
		$(IDIR_AUDIT)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
