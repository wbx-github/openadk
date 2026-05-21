# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		faac
PKG_VERSION:=		1.30
PKG_RELEASE:=		1
PKG_HASH:=		adc387ce588cca16d98c03b6ec1e58f0ffd9fc6eadb00e254157d6b16203b2d2
PKG_DESCR:=		aac encoder library
PKG_SECTION:=		libs/audio
PKG_URL:=		http://www.audiocoding.com/faac.html
PKG_SITES:=		https://sourceforge.net/projects/faac/files/faac-src/faac-$(PKG_VERSION)/
PKG_LIBNAME:=		libfaac
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-1_30.tar.gz
WRKDIST=		$(WRKDIR)/$(PKG_NAME)-1_30

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBFAAC,libfaac,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

AUTOTOOL_STYLE:=	autoreconf
CONFIGURE_ARGS+=	--without-mp4v2

libfaac-install:
	$(INSTALL_DIR) $(IDIR_LIBFAAC)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libfaac*.so* \
		$(IDIR_LIBFAAC)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
