# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libmodplug
PKG_VERSION:=		0.8.9.0
PKG_RELEASE:=		1
PKG_HASH:=		457ca5a6c179656d66c01505c0d95fafaead4329b9dbaa0f997d00a3508ad9de
PKG_DESCR:=		mod player library
PKG_SECTION:=		libs/audio
PKG_URL:=		http://modplug-xmms.sourceforge.net
PKG_SITES:=		https://sourceforge.net/projects/modplug-xmms/files/libmodplug/$(PKG_VERSION)/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBMODPLUG,libmodplug,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

libmodplug-install:
	$(INSTALL_DIR) $(IDIR_LIBMODPLUG)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libmodplug*.so* \
		$(IDIR_LIBMODPLUG)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
