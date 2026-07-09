# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		cjson
PKG_VERSION:=		1.7.19
PKG_RELEASE:=		1
PKG_HASH:=		7fa616e3046edfa7a28a32d5f9eacfd23f92900fe1f8ccd988c1662f30454562
PKG_DESCR:=		ultralightweight json parser in ansi c
PKG_SECTION:=		libs/data
PKG_BUILDDEP:=		cmake-host
PKG_URL:=		https://github.com/davegamble/cjson
PKG_SITES:=		https://github.com/DaveGamble/cJSON/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=		v$(PKG_VERSION).tar.gz
WRKDIST=		$(WRKDIR)/cJSON-$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,CJSON,cjson,$(PKG_VERSION)-$(PKG_RELEASE),$(PKG_DEPENDS),$(PKG_DESCR),$(PKG_SECTION),$(PKG_OPTS)))

CONFIG_STYLE:=		cmake
CMAKE_FLAGS+=		-DENABLE_CUSTOM_COMPILER_FLAGS=OFF \
			-DENABLE_CJSON_TEST=OFF

cjson-install:
	$(INSTALL_DIR) $(IDIR_CJSON)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libcjson.so* \
		$(IDIR_CJSON)/usr/lib

include $(ADK_TOPDIR)/mk/pkg-bottom.mk
