# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libnettle
PKG_VERSION:=		3.10.2
PKG_RELEASE:=		1
PKG_HASH:=		fe9ff51cb1f2abb5e65a6b8c10a92da0ab5ab6eaf26e7fc2b675c45f1fb519b5
PKG_DESCR:=		crypto library
PKG_SECTION:=		libs/crypto
PKG_DEPENDS:=		libgmp
PKG_BUILDDEP:=		gmp
HOST_BUILDDEP:=		gmp-host
PKG_URL:=		http://www.lysator.liu.se/~nisse/
PKG_SITES:=		http://www.lysator.liu.se/~nisse/archive/
PKG_OPTS:=		dev

DISTFILES:=             nettle-${PKG_VERSION}.tar.gz
WRKDIST=		${WRKDIR}/nettle-${PKG_VERSION}

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,LIBNETTLE,libnettle,${PKG_VERSION}-${PKG_RELEASE}))
$(eval $(call PKG_template,LIBNETTLE,libnettle,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIGURE_ARGS+=	--disable-documentation

libnettle-install:
	$(INSTALL_DIR) $(IDIR_LIBNETTLE)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libnettle*.so* \
		$(IDIR_LIBNETTLE)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libhogweed.so* \
		$(IDIR_LIBNETTLE)/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
