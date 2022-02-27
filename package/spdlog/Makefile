# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		spdlog
PKG_VERSION:=		1.9.2
PKG_RELEASE:=		1
PKG_HASH:=		6fff9215f5cb81760be4cc16d033526d1080427d236e86d70bb02994f85e3d38
PKG_DESCR:=		very fast, header-only/compiled, C++ logging library
PKG_BUILDDEP:=		fmt
PKG_SECTION:=		libs/misc
PKG_SITES:=		https://github.com/gabime/spdlog/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=             v$(PKG_VERSION).tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,SPDLOG,spdlog,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIG_STYLE:=		cmake
CMAKE_FLAGS+=		-DSPDLOG_BUILD_TESTS=OFF \
			-DSPDLOG_BUILD_EXAMPLE=OFF \
			-DSPDLOG_BUILD_BENCH=OFF \
			-DSPDLOG_FMT_EXTERNAL=ON


spdlog-install:

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
