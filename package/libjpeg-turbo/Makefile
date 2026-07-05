# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libjpeg-turbo
PKG_VERSION:=		3.2.0
PKG_RELEASE:=		1
PKG_HASH:=		980dd81f425082aa6d7c9e47fef27554ce7a9ffc8e2f6e863b97d263c5c50858
PKG_DESCR:=		jpeg image library
PKG_SECTION:=		libs/image
PKG_BUILDDEP:=		cmake-host yasm-host
HOST_BUILDDEP:=		cmake-host yasm-host
PKG_URL:=		http://libjpeg-turbo.org/
PKG_SITES:=		https://github.com/libjpeg-turbo/libjpeg-turbo/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,LIBJPEG_TURBO,libjpeg-turbo,$(PKG_VERSION)-${PKG_RELEASE}))
$(eval $(call PKG_template,LIBJPEG_TURBO,libjpeg-turbo,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

HOST_CONFIG_STYLE:=	cmake
CONFIG_STYLE:=		cmake

libjpeg-turbo-install:
	$(INSTALL_DIR) $(IDIR_LIBJPEG_TURBO)/usr/lib
	$(CP) $(WRKINST)/usr/lib/lib{turbo,}jpeg*.so* \
		$(IDIR_LIBJPEG_TURBO)/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
