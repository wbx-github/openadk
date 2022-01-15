# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libsndfile
PKG_VERSION:=		1.0.28
PKG_RELEASE:=		1
PKG_HASH:=		1ff33929f042fa333aed1e8923aa628c3ee9e1eb85512686c55092d1e5a9dfa9
PKG_DESCR:=		reading and writing files containing sampled sound
PKG_SECTION:=		libs/audio
PKG_URL:=		http://www.mega-nerd.com/libsndfile/
PKG_SITES:=		http://www.mega-nerd.com/libsndfile/files/
PKG_NEEDS:=		c++
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBSNDFILE,libsndfile,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIGURE_ARGS+=	--disable-sqlite

libsndfile-install:
	$(INSTALL_DIR) $(IDIR_LIBSNDFILE)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libsndfile*.so* \
		$(IDIR_LIBSNDFILE)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
