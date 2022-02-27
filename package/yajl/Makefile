# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		yajl
PKG_VERSION:=		2.1.0
PKG_RELEASE:=		1
PKG_HASH:=		3fb73364a5a30efe615046d07e6db9d09fd2b41c763c5f7d3bfb121cd5c5ac5a
PKG_DESCR:=		small event-driven json parser
PKG_SECTION:=		libs/data
PKG_BUILDDEP:=		cmake-host ruby-host
PKG_URL:=		http://lloyd.github.com/yajl/
PKG_SITES:=		https://github.com/lloyd/yajl/archive/refs/tags/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,YAJL,yajl,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIG_STYLE:=		cmake

yajl-install:
	$(INSTALL_DIR) $(IDIR_YAJL)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libyajl*.so* \
		$(IDIR_YAJL)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
