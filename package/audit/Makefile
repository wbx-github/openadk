# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		audit
PKG_VERSION:=		2.6.7
PKG_RELEASE:=		1
PKG_HASH:=		8923917332daa7833bbc0c1d9eb012167093fbad000da4a9630fb3356aff8cdc
PKG_DESCR:=		audit library
PKG_SECTION:=		libs/misc
PKG_URL:=		http://people.redhat.com/sgrubb/audit
PKG_SITES:=		http://people.redhat.com/sgrubb/audit/
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
