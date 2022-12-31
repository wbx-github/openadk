# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		mesa-demos
PKG_VERSION:=		8.5.0
PKG_RELEASE:=		1
PKG_HASH:=		2472818cea452a34229d03084e7c81f94267d14a39c5287379de0fb1dc02caab
PKG_DESCR:=		opengl demo apps
PKG_SECTION:=		mm/video
PKG_DEPENDS:=		mesa libglew libglu
PKG_BUILDDEP:=		mesa libglew glu
PKG_SITES:=		ftp://ftp.freedesktop.org/pub/mesa/demos/${PKG_VERSION}/

DISTFILES:=		${PKG_NAME}-${PKG_VERSION}.tar.gz

PKG_ARCH_DEPENDS:=      x86 x86_64 mips mipsel mips64 mips64el arm aarch64

PKG_SUBPKGS:=		GLXINFO GLXGEARS
PKGSD_GLXGEARS:=	opengl demo app
PKGSD_GLXINFO:=		command-line tool for diagnosing problems with your 3D acceleration card
PKGSS_GLXINFO:=		libxt libxau libxdmcp libxcb libx11 libxext libglew 
PKGSS_GLXINFO+=		libxxf86vm

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,GLXINFO,glxinfo,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))
$(eval $(call PKG_template,GLXGEARS,glxgears,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION}))

WRKBUILD=               $(WRKDIR)/$(PKG_NAME)-obj
CONFIG_STYLE:=		meson
BUILD_STYLE:=		meson
INSTALL_STYLE:=		meson

glxgears-install:
	$(INSTALL_DIR) $(IDIR_GLXGEARS)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/glxgears \
		$(IDIR_GLXGEARS)/usr/bin

glxinfo-install:
	$(INSTALL_DIR) $(IDIR_GLXINFO)/usr/bin
	$(INSTALL_BIN) $(WRKINST)/usr/bin/glxinfo \
		$(IDIR_GLXINFO)/usr/bin

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
