# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		tinyxml
PKG_VERSION:=		2.6.2
PKG_RELEASE:=		1
PKG_HASH:=		8164c9ad48b9028667768a584d62f7760cfbfb90d0dd6214ad174403058da10c
PKG_DESCR:=		simple, small, minimal, c++ xml parser
PKG_SECTION:=		libs/data
PKG_SITES:=		http://mirrors.xbmc.org/build-deps/sources/
PKG_OPTS:=		dev

DISTFILES:=             ${PKG_NAME}-2.6.2_2.tar.gz
WRKDIST=		${WRKDIR}/tinyxml-2.6.2_2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,TINYXML,tinyxml,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

TARGET_CXXFLAGS+=	-fPIC

AUTOTOOL_STYLE:=	autoreconf

tinyxml-install:
	$(INSTALL_DIR) $(IDIR_TINYXML)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libtinyxml.so* \
		$(IDIR_TINYXML)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
