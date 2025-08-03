# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		fltk
PKG_VERSION:=		1.3.11
PKG_RELEASE:=		1
PKG_HASH:=		92805abc84505e3e7e27aec775ab0754ecb4182fe2d8ff2a9d568ccdcb2811ac
PKG_DESCR:=		fast light toolkit
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		mesa libx11 libxi freeglut libfreetype
PKG_BUILDDEP:=		libX11 libXi mesa freeglut freetype
PKG_NEEDS:=		locale
PKG_URL:=		http://www.fltk.org/
PKG_SITES:=		https://github.com/fltk/fltk/releases/download/release-$(PKG_VERSION)/
PKG_LIBNAME:=		libfltk
PKG_OPTS:=		dev

PKG_ARCH_DEPENDS:=	x86 x86_64 mips sh arm

DISTFILES:=		${PKG_NAME}-$(PKG_VERSION)-source.tar.gz

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBFLTK,libfltk,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIGURE_ARGS+=	--disable-xinerama \
			--disable-print \
			--disable-fluid \
			--disable-test

libfltk-install:
	$(INSTALL_DIR) $(IDIR_LIBFLTK)/usr/lib
	$(CP) ${WRKINST}/usr/lib/libfltk*.so* $(IDIR_LIBFLTK)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
