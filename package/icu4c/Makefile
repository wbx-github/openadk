# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		icu4c
PKG_VERSION:=		70.1
PKG_RELEASE:=		1
PKG_HASH:=		8d205428c17bf13bb535300669ed28b338a157b1c01ae66d31d0d3e2d47c3fd5
PKG_DESCR:=		unicode and globalization library
PKG_SECTION:=		libs/misc
PKG_BUILDDEP:=		icu4c-host
PKG_NEEDS:=		c++
PKG_URL:=		http://icu-project.org
PKG_SITES:=		https://github.com/unicode-org/icu/releases/download/release-70-1/
PKG_OPTS:=		dev

DISTFILES:=             ${PKG_NAME}-70_1-src.tgz

WRKDIST=		${WRKDIR}/icu/source

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,ICU4C,icu4c,$(PKG_VERSION)-${PKG_RELEASE}))
$(eval $(call PKG_template,ICU4C,icu4c,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

HOST_CFLAGS+=		-static-libstdc++ -fPIC
HOST_CXXFLAGS+=		-static-libstdc++ -fPIC
HOST_STYLE:=		auto
HOST_CONFIGURE_ARGS+=	--enable-extras=no \
			--enable-samples=no \
			--enable-tests=no \
			--enable-dyload=no \
			--enable-shared=no \
			--enable-static
CONFIGURE_ARGS+=	--with-cross-build=${HOST_BUILD_DIR}/w-${PKG_NAME}-${PKG_VERSION}-${PKG_RELEASE}-host/icu/source \
			--enable-extras=no \
			--enable-samples=no \
			--enable-tests=no \

icu4c-hostinstall:

icu4c-install:
	$(INSTALL_DIR) $(IDIR_ICU4C)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libicuuc.so* \
		$(IDIR_ICU4C)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libicudata.so* \
		$(IDIR_ICU4C)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libicui18n.so* \
		$(IDIR_ICU4C)/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
