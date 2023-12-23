# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libjansson
PKG_VERSION:=		2.14
PKG_RELEASE:=		1
PKG_HASH:=		fba956f27c6ae56ce6dfd52fbf9d20254aad42821f74fa52f83957625294afb9
PKG_DESCR:=		json library
PKG_SECTION:=		libs/data
PKG_URL:=		http://www.digip.org/jansson/
PKG_SITES:=		https://github.com/akheron/jansson/releases/download/v$(PKG_VERSION)/
PKG_OPTS:=		dev

DISTFILES:=             jansson-${PKG_VERSION}.tar.bz2
WRKDIST=		${WRKDIR}/jansson-${PKG_VERSION}

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBJANSSON,libjansson,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

TARGET_LDFLAGS+=	-lm

libjansson-install:
	$(INSTALL_DIR) $(IDIR_LIBJANSSON)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libjansson*.so* \
		$(IDIR_LIBJANSSON)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
