# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libdnet
PKG_VERSION:=		1.11
PKG_RELEASE:=		3
PKG_HASH:=		0eb78415c8f2564c2f1e8ad36e98473348d9c94852f796a226360c716cc7ca53
PKG_DESCR:=		low-level networking library
PKG_SECTION:=		libs/net
PKG_URL:=		http://libdnet.sourceforge.net/
PKG_SITES:=		https://sourceforge.net/projects/libdnet/files/libdnet/libdnet-1.11/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBDNET,libdnet,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ENV+=		ac_cv_dnet_bsd_bpf=no
CONFIGURE_ARGS+=	--without-check

post-patch:
	mv $(WRKBUILD)/config/acinclude.m4 $(WRKBUILD)

libdnet-install:
	$(INSTALL_DIR) $(IDIR_LIBDNET)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libdnet.so* $(IDIR_LIBDNET)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
