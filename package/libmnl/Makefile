# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libmnl
PKG_VERSION:=		1.0.5
PKG_RELEASE:=		1
PKG_HASH:=		274b9b919ef3152bfb3da3a13c950dd60d6e2bcd54230ffeca298d03b40d0525
PKG_DESCR:=		minimalistic user-space library oriented to netlink developers
PKG_SECTION:=		libs/net
PKG_URL:=		http://www.netfilter.org/projects/libmnl/
PKG_SITES:=		http://www.netfilter.org/projects/libmnl/files/
PKG_OPTS:=		dev

DISTFILES:=             ${PKG_NAME}-${PKG_VERSION}.tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBMNL,libmnl,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

libmnl-install:
	$(INSTALL_DIR) $(IDIR_LIBMNL)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libmnl.so* $(IDIR_LIBMNL)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
