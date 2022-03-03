# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		fribidi
PKG_VERSION:=		1.0.11
PKG_RELEASE:=		1
PKG_HASH:=		30f93e9c63ee627d1a2cedcf59ac34d45bf30240982f99e44c6e015466b4e73d
PKG_DESCR:=		unicode bidirectional algorithm
PKG_SECTION:=		libs/misc
PKG_URL:=		http://www.fribidi.org/
PKG_SITES:=		https://github.com/fribidi/fribidi/releases/download/v1.0.11/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,FRIBIDI,fribidi,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

fribidi-install:
	$(INSTALL_DIR) $(IDIR_FRIBIDI)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libfribidi*.so* \
		$(IDIR_FRIBIDI)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
