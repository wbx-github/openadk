# This file is part of the OpenADK project. OpenADK is copyrighted
# material, please see the LICENCE file in the top-level directory.

include $(ADK_TOPDIR)/rules.mk

PKG_NAME:=		libglew
PKG_VERSION:=		2.3.1
PKG_RELEASE:=		1
PKG_HASH:=		b64790f94b926acd7e8f84c5d6000a86cb43967bd1e688b03089079799c9e889
PKG_DESCR:=		opengl extension wrangler library
PKG_SECTION:=		libs/video
PKG_DEPENDS:=		libx11 libxmu libxi libxext mesa
PKG_BUILDDEP:=		libX11 libXmu libXi libXext mesa
PKG_URL:=		http://glew.sourceforge.net/index.html
PKG_SITES:=		https://sourceforge.net/projects/glew/files/glew/$(PKG_VERSION)/
PKG_OPTS:=		dev

PKG_ARCH_DEPENDS:=	!m68k

DISTFILES:=		glew-$(PKG_VERSION).tgz
WRKDIST=		${WRKDIR}/glew-$(PKG_VERSION)

include $(ADK_TOPDIR)/mk/package.mk

$(eval $(call PKG_template,LIBGLEW,libglew,$(PKG_VERSION)-${PKG_RELEASE},${PKG_DEPENDS},${PKG_DESCR},${PKG_SECTION},${PKG_OPTS}))

CONFIG_STYLE:=		manual
XAKE_FLAGS+=		STRIP='' SYSTEM=linux CC="$(TARGET_CC)" LD="$(TARGET_CC)"

libglew-install:
	$(INSTALL_DIR) $(IDIR_LIBGLEW)/usr/lib
	$(CP) $(WRKINST)/usr/lib*/libGLEW.so* \
		$(IDIR_LIBGLEW)/usr/lib

include ${ADK_TOPDIR}/mk/pkg-bottom.mk
