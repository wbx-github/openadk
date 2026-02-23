# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		fltk
PKG_VERSION:=		1.4.4
PKG_RELEASE:=		1
PKG_HASH:=		94b464cce634182c8407adac1be5fc49678986ca93285699b444352af89b4efe
PKG_DESCR:=		fast light toolkit
PKG_SECTION:=		libs/misc
PKG_DEPENDS:=		mesa libx11 libxi freeglut libfreetype
PKG_BUILDDEP:=		libX11 libXi mesa freeglut freetype
PKG_NEEDS:=		locale
PKG_URL:=		http://www.fltk.org/
PKG_SITES:=		https://github.com/fltk/fltk/releases/download/release-$(PKG_VERSION)/
PKG_LIBNAME:=		libfltk
PKG_OPTS:=		dev

PKG_ARCH_DEPENDS:=	aarch64 x86 x86_64 mips sh arm

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
