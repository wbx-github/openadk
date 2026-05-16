# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libjson
PKG_VERSION:=		7.6.1
PKG_RELEASE:=		1
PKG_HASH:=		07267a3951038ee2e02d26cc41bf8e275668c38f751240d3e78dc979182e7376
PKG_DESCR:=		json library
PKG_SECTION:=		libs/data
PKG_URL:=		http://sourceforge.net/projects/libjson/
PKG_SITES:=		${MASTER_SITE_SOURCEFORGE:=libjson/}
PKG_OPTS:=		dev

PKG_NOPARALLEL:=	1

DISTFILES:=             ${PKG_NAME}_${PKG_VERSION}.zip
WRKDIST=		${WRKDIR}/${PKG_NAME}

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBJSON,libjson,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

TARGET_CXXFLAGS+=	-std=c++11
MAKE_FILE:=		makefile
FAKE_FLAGS+=		prefix=${WRKINST}/usr
CONFIG_STYLE:=		manual

libjson-install:
	$(INSTALL_DIR) $(IDIR_LIBJSON)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libjson*.so* \
		$(IDIR_LIBJSON)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
