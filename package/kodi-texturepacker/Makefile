# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		kodi-texturepacker
PKG_VERSION:=		22.0b1
PKG_RELEASE:=		1
PKG_HASH:=		05cb0d19c1716b1121e7e69d4ac7f9a2d0c7228b2122510a8cb3adc47e609c73
PKG_DESCR:=		kodi texture packer
PKG_SECTION:=		libs/image
HOST_BUILDDEP:=		liblzo-host
PKG_SITES:=		https://github.com/xbmc/xbmc/archive/
PKG_OPTS:=		dev

PKG_CFLINE_KODI_TEXTUREPACKER:=	depends on ADK_HOST_ONLY

DISTFILES:=		${PKG_VERSION}-Piers.tar.gz
WRKDIST=		${WRKDIR}/xbmc-$(PKG_VERSION)-Piers/tools/depends/native/TexturePacker/src
WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,KODI_TEXTUREPACKER,kodi-texturepacker,$(PKG_VERSION)-${PKG_RELEASE}))
$(eval $(call PKG_template,KODI_TEXTUREPACKER,kodi-texturepacker,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

HOST_CXXFLAGS+= \
	-std=c++17 \
	-DTARGET_POSIX \
	-DTARGET_LINUX \
	-D_LINUX \
	-I$(WRKSRC)/xbmc/linux

HOST_CONFIG_STYLE:=	cmake
HOST_CMAKE_FLAGS:=	-DCMAKE_CXX_FLAGS="$(HOST_CXXFLAGS)" \
			-DCMAKE_MODULE_PATH="$(WRKDIR)/xbmc-$(PKG_VERSION)-Piers/cmake/modules:$(WRKDIR)/xbmc-$(PKG_VERSION)-Piers" \
			-DKODI_SOURCE_DIR=$(WRKDIR)/xbmc-$(PKG_VERSION)-Piers

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
