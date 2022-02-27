# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		flatbuffers
PKG_VERSION:=		2.0.6
PKG_RELEASE:=		1
PKG_HASH:=		e2dc24985a85b278dd06313481a9ca051d048f9474e0f199e372fea3ea4248c9
PKG_DESCR:=		cross platform serialization library
PKG_SECTION:=		libs/misc
PKG_BUILDDEP:=		flatbuffers-host
PKG_URL:=		https://github.com/google/flatbuffers
PKG_SITES:=		https://github.com/google/flatbuffers/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,FLATBUFFERS,flatbuffers,$(PKG_VERSION)-${PKG_RELEASE}))
$(eval $(call PKG_template,FLATBUFFERS,flatbuffers,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

HOST_CONFIG_STYLE:=	cmake
CONFIG_STYLE:=          cmake

CMAKE_FLAGS+=		-DFLATBUFFERS_BUILD_TESTS=OFF \
			-DFLATBUFFERS_BUILD_FLATC=OFF \
			-DFLATBUFFERS_BUILD_FLATHASH=OFF

HOST_CMAKE_FLAGS+=	-DFLATBUFFERS_BUILD_TESTS=OFF \
			-DFLATBUFFERS_BUILD_FLATC=ON \
			-DFLATBUFFERS_BUILD_FLATHASH=ON

flatbuffers-install:

include ${ADK_TOPDIR}/mk/host-bottom.mk
include $(ADK_TOPDIR)/mk/pkg-bottom.mk
