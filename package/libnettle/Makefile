# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libnettle
PKG_VERSION:=		3.10.1
PKG_RELEASE:=		1
PKG_HASH:=		b0fcdd7fc0cdea6e80dcf1dd85ba794af0d5b4a57e26397eee3bc193272d9132
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
