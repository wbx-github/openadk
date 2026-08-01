# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libmicrohttpd
PKG_VERSION:=		1.0.9
PKG_RELEASE:=		1
PKG_HASH:=		6e9adc446b08083ec03d40317fb66ca6f2e03e4f6170aef33a6e59bb08db2012
PKG_DESCR:=		library make it easy to run an webserver
PKG_SECTION:=		libs/net
PKG_BUILDDEP:=		gnutls
PKG_DEPENDS:=		gnutls
PKG_URL:=		http://www.gnu.org/software/libmicrohttpd/
PKG_SITES:=		${MASTER_SITE_GNU:=libmicrohttpd/}
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBMICROHTTPD,libmicrohttpd,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

libmicrohttpd-install:
	$(INSTALL_DIR) $(IDIR_LIBMICROHTTPD)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libmicrohttpd*.so* \
		$(IDIR_LIBMICROHTTPD)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
