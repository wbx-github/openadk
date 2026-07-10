# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libnfs
PKG_VERSION:=		6.0.2
PKG_RELEASE:=		1
PKG_HASH:=		4e5459cc3e0242447879004e9ad28286d4d27daa42cbdcde423248fad911e747
PKG_DESCR:=		nfs client library
PKG_SECTION:=		libs/net
PKG_URL:=		https://github.com/sahlberg/libnfs
PKG_SITES:=		https://github.com/sahlberg/libnfs/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=             $(PKG_NAME)-$(PKG_VERSION).tar.gz
WRKDIST=             	$(WRKDIR)/$(PKG_NAME)-$(PKG_NAME)-$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBNFS,libnfs,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ARGS+=	--without-libkrb5

libnfs-install:
	$(INSTALL_DIR) $(IDIR_LIBNFS)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libnfs*.so* \
		$(IDIR_LIBNFS)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
