# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libcdio
PKG_VERSION:=		2.1.0
PKG_RELEASE:=		1
PKG_HASH:=		8550e9589dbd594bfac93b81ecf129b1dc9d0d51e90f9696f1b2f9b2af32712b
PKG_DESCR:=		library for cd-rom and cd image access
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		ncurses
PKG_BUILDDEP:=		ncurses
PKG_URL:=		http://www.gnu.org/software/libcdio
PKG_SITES:=		http://ftp.gnu.org/gnu/libcdio/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.bz2

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBCDIO,libcdio,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

TARGET_LDFLAGS+=	-ltinfo

libcdio-install:
	$(INSTALL_DIR) $(IDIR_LIBCDIO)/usr/lib
	$(CP) $(WRKINST)/usr/lib/lib*.so* \
		$(IDIR_LIBCDIO)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
