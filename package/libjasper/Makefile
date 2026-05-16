# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libjasper
PKG_VERSION:=		4.2.9
PKG_RELEASE:=		1
PKG_HASH:=		f71cf643937a5fcaedcfeb30a22ba406912948ad4413148214df280afc425454
PKG_DESCR:=		implementation of the codec specified in the jpeg-2000 standard
PKG_SECTION:=		libs/image
PKG_BUILDDEP:=		cmake-host
PKG_SITES:=		https://github.com/jasper-software/jasper/releases/download/version-4.2.9/
PKG_NEEDS:=		c++
PKG_OPTS:=		dev

DISTFILES:=		jasper-$(PKG_VERSION).tar.gz
WRKDIST=		${WRKDIR}/jasper-$(PKG_VERSION)
WRKBUILD=		$(WRKDIR)/$(PKG_NAME)-obj

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBJASPER,libjasper,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIG_STYLE:=		cmake
JASPER_STDC_VERSION=	"`echo __STDC_VERSION__ | $(TARGET_CROSS)cpp -E -P -`"
CMAKE_FLAGS+=		-DJAS_STDC_VERSION=$(JASPER_STDC_VERSION) \
			-DJAS_ENABLE_DOC=OFF \

libjasper-install:
	$(INSTALL_DIR) $(IDIR_LIBJASPER)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libjasper*.so* \
		$(IDIR_LIBJASPER)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
