# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		taglib
PKG_VERSION:=		1.13.1
PKG_RELEASE:=		1
PKG_HASH:=		c8da2b10f1bfec2cd7dbfcd33f4a2338db0765d851a50583d410bacf055cfd0b
PKG_DESCR:=		audio meta-data library
PKG_SECTION:=		libs/audio
PKG_DEPENDS:=		zlib
PKG_BUILDDEP:=		cmake-host zlib
PKG_URL:=		http://taglib.github.com/
PKG_SITES:=		http://taglib.github.io/releases/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,TAGLIB,taglib,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIG_STYLE:=		manual

do-configure:
	(cd ${WRKBUILD} && PATH='${HOST_PATH}' \
		cmake -DZLIB_ROOT=$(STAGING_TARGET_DIR)/usr \
			-DCMAKE_INSTALL_PREFIX:PATH=/usr \
			-DCMAKE_SYSTEM_NAME=Linux .)

taglib-install:
	$(INSTALL_DIR) $(IDIR_TAGLIB)/usr/lib
	-$(CP) $(WRKINST)/usr/lib/libtag*.so* \
		$(IDIR_TAGLIB)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
