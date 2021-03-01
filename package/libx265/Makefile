# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libx265
PKG_VERSION:=		3.2
PKG_HASH:=		364d79bcd56116a9e070fdeb1d9d2aaef1a786b4970163fb56ff0991a183133b
PKG_RELEASE:=		1
PKG_DESCR:=		h265 encoding library
PKG_SECTION:=		libs/video
PKG_BUILDDEP:=		cmake-host
PKG_URL:=		http://x265.org
PKG_SITES:=		http://ftp.videolan.org/pub/videolan/x265/
PKG_OPTS:=		dev

DISTFILES:=		x265_${PKG_VERSION}.tar.gz
WRKDIST=		${WRKDIR}/x265_${PKG_VERSION}
WRKSRC=			${WRKDIST}/source

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBX265,libx265,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIG_STYLE:=		cmake
CMAKE_FLAGS+=		-DENABLE_SHARED=ON -DENABLE_PIC=ON

libx265-install:
	$(INSTALL_DIR) $(IDIR_LIBX265)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libx265*.so* \
		$(IDIR_LIBX265)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
