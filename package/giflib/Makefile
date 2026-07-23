# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		giflib
PKG_VERSION:=		6.1.3
PKG_RELEASE:=		1
PKG_HASH:=		b65b66b99f0424b93525f987386f22fc5efb9da2bfc92ad4a532249aaffbab0e
PKG_DESCR:=		gif graphics library
PKG_SECTION:=		libs/image
PKG_URL:=		http://sourceforge.net/projects/giflib/
PKG_SITES:=		https://sourceforge.net/projects/giflib/files/giflib-6.x/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,GIFLIB,giflib,$(PKG_VERSION)-${PKG_RELEASE}))
$(eval $(call PKG_template,GIFLIB,giflib,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

HOST_XAKE_FLAGS:=	PREFIX="$(STAGING_HOST_DIR)/usr"
XAKE_FLAGS:=		PREFIX="/usr"
HOST_CONFIG_STYLE:=	manual
CONFIG_STYLE:=		manual

giflib-install:
	$(INSTALL_DIR) $(IDIR_GIFLIB)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libgif.so* \
		$(IDIR_GIFLIB)/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
