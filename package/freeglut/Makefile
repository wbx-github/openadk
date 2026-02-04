# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		freeglut
PKG_VERSION:=		3.8.0
PKG_RELEASE:=		1
PKG_HASH:=		674dcaff25010e09e450aec458b8870d9e98c46f99538db457ab659b321d9989
PKG_DESCR:=		opengl utility toolkit libraries
PKG_SECTION:=		libs/video
PKG_DEPENDS:=		libglu
PKG_BUILDDEP:=		glu cmake-host
PKG_NEEDS:=		c++
PKG_URL:=		http://freeglut.sourceforge.net/
PKG_SITES:=		https://github.com/freeglut/freeglut/releases/download/v3.8.0/
PKG_OPTS:=		dev

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_ARCH_DEPENDS:=	arm mips mipsel mips64 mips64el sh x86 x86_64

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,FREEGLUT,freeglut,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIG_STYLE:=		cmake
CMAKE_FLAGS+=		-DFREEGLUT_BUILD_DEMOS=OFF

freeglut-install:
	$(INSTALL_DIR) $(IDIR_FREEGLUT)/usr/lib
	$(CP) ${WRKINST}/usr/lib/libglut.so* $(IDIR_FREEGLUT)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
