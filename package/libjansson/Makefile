# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libjansson
PKG_VERSION:=		2.15.1
PKG_RELEASE:=		1
PKG_HASH:=		f9aa4b3ec8496fee69db94f06f3d76fd4a26b012ee9bf1e917078c2cd2841881
PKG_DESCR:=		json library
PKG_SECTION:=		libs/data
PKG_URL:=		http://www.digip.org/jansson/
PKG_SITES:=		https://github.com/akheron/jansson/releases/download/v$(PKG_VERSION)/
PKG_OPTS:=		dev

DISTFILES:=             jansson-${PKG_VERSION}.tar.bz2
WRKDIST=		${WRKDIR}/jansson-${PKG_VERSION}

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBJANSSON,libjansson,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

libjansson-install:
	$(INSTALL_DIR) $(IDIR_LIBJANSSON)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libjansson*.so* \
		$(IDIR_LIBJANSSON)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
