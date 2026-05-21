# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		check
PKG_VERSION:=		0.10.0
PKG_RELEASE:=		1
PKG_HASH:=		f5f50766aa6f8fe5a2df752666ca01a950add45079aa06416b83765b1cf71052
PKG_DESCR:=		unit testing framework for c
PKG_SECTION:=		libs/misc
PKG_URL:=		http://check.sourceforge.net/
PKG_SITES:=		https://sourceforge.net/projects/check/files/check/$(PKG_VERSION)/
PKG_LIBNAME:=		libcheck
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBCHECK,libcheck,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

libcheck-install:
	$(INSTALL_DIR) $(IDIR_LIBCHECK)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libcheck*.so* \
		$(IDIR_LIBCHECK)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
