# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		fribidi
PKG_VERSION:=		1.0.18
PKG_RELEASE:=		1
PKG_HASH:=		1de5e8073d035388b71d0b2d452b1da1f8caeea8a7702997b401fe1b6250727f
PKG_DESCR:=		unicode bidirectional algorithm
PKG_SECTION:=		libs/misc
PKG_BUILDDEP:=		meson-host
PKG_URL:=		http://www.fribidi.org/
PKG_SITES:=		https://github.com/fribidi/fribidi/releases/download/v$(PKG_VERSION)/
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,FRIBIDI,fribidi,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj

CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

fribidi-install:
	$(INSTALL_DIR) $(IDIR_FRIBIDI)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libfribidi*.so* \
		$(IDIR_FRIBIDI)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
