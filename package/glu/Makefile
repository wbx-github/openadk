# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		glu
PKG_VERSION:=		9.0.2
PKG_RELEASE:=		1
PKG_HASH:=		6e7280ff585c6a1d9dfcdf2fca489251634b3377bfc33c29e4002466a38d02d4
PKG_DESCR:=		opengl utility library
PKG_SECTION:=		libs/video
PKG_BUILDDEP:=		mesa
PKG_URL:=		http://cgit.freedesktop.org/mesa/glu/
PKG_SITES:=		ftp://ftp.freedesktop.org/pub/mesa/glu/
PKG_LIBNAME:=		libglu
PKG_OPTS:=		dev

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBGLU,libglu,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

libglu-install:
	$(INSTALL_DIR) $(IDIR_LIBGLU)/usr/lib
	$(CP) $(WRKINST)/usr/lib/libGLU.so* \
		$(IDIR_LIBGLU)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
