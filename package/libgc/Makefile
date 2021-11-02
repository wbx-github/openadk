# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libgc
PKG_VERSION:=		8.2.0
PKG_RELEASE:=		1
PKG_HASH:=		2540f7356cb74f6c5b75326c6d38a066edd796361fd7d4ed26e494d9856fed8f
PKG_DESCR:=		garbage collector library
PKG_SECTION:=		libs/misc
PKG_BUILDDEP:=		libatomic_ops
HOST_BUILDDEP:=		libatomic_ops-host libgc-host
PKG_URL:=		http://www.hboehm.info/gc/
PKG_SITES:=		http://www.hboehm.info/gc/gc_source/
PKG_OPTS:=		dev

DISTFILES:=		gc-${PKG_VERSION}.tar.gz
WRKDIST=		${WRKDIR}/gc-${PKG_VERSION}

include $(ADK_TOPDIR)/mk/host.mk
include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call HOST_template,LIBGC,libgc,$(PKG_VERSION)-${PKG_RELEASE}))
$(eval $(call PKG_template,LIBGC,libgc,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

TARGET_CPPFLAGS+=	-DNO_GETCONTEXT

libgc-install:
	$(INSTALL_DIR) $(IDIR_LIBGC)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libgc*.so* \
		$(IDIR_LIBGC)/usr/lib

include ${ADK_TOPDIR}/mk/host-bottom.mk
include ${ADK_TOPDIR}/mk/pkg-bottom.mk
